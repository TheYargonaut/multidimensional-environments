#include <SDL.h>
#include <exception>
#include <string>

#include "AttrWindow.h"

// --------------------------------------------------------------------------------------------------------------------
// supporting function forward declarations

void PutPixel32_nolock(SDL_Surface * surface, int x, int y, Uint32 color);

// --------------------------------------------------------------------------------------------------------------------

using namespace AttrWindow;

SdlWindow::SdlWindow( int _width, int _height ) 
: width_( _width ), height_( _height ), window_( NULL ), surface_( NULL ) {
    // Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        throw std::runtime_error( "SDL could not initialize! SDL_Error: " + std::string( SDL_GetError() ) );
	}
    // Create window
    window_ = SDL_CreateWindow( "MDV", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN );
    if( window_ == NULL ) {
        throw std::runtime_error( "Window could not be created! SDL_Error: " + std::string( SDL_GetError() ) );
    }
    // Get window surface
    windowSurface_ = SDL_GetWindowSurface( window_ );
    // Construct working surface for double-buffer
    auto tempSurface = SDL_LoadBMP( "background.bmp" ); // Put a logo here. Or blank rectangle, but that's less fun
    if( tempSurface == NULL ) {
        throw std::runtime_error( "Surface could not be created! SDL_Error: " + std::string( SDL_GetError() ) );
    }
    // optimize
    surface_ = SDL_ConvertSurface( tempSurface, windowSurface_->format, 0 );
    if( surface_ == NULL ) {
        throw std::runtime_error( "Unable to optimize image! SDL Error: " + std::string( SDL_GetError() ) );
    }
    SDL_FreeSurface( tempSurface );
    // prepare for editing
    if( SDL_MUSTLOCK( surface_ ) ) { SDL_UnlockSurface( surface_ ); }
}

SdlWindow::~SdlWindow() {
	//Deallocate surface
	SDL_FreeSurface( surface_ );
	surface_ = NULL;
	//Destroy window
	SDL_DestroyWindow( window_ );
	window_ = NULL;
    windowSurface_ = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

void SdlWindow::widthIs( int _width ) {

}

void SdlWindow::heightIs( int _height ) {

}

void SdlWindow::dimIs( int _width, int _height ) {

}

void SdlWindow::pixelIs( int _x, int _y, Uint32 _color ) {
    PutPixel32_nolock( surface_, _x, _y, _color );
}

Uint32 SdlWindow::pixel( int x, int j ) const {
    return 0;
}

void SdlWindow::enqEventCallback( Callback _callback, SDL_Event ) {
    
}
void SdlWindow::enqGeneralCallback( GeneralCallback _callback ) {
    generalCallback_.push_back( _callback );
}

void SdlWindow::enqFrameCallback( Callback _callback ) {
    frameCallback_.push_back( _callback );
}

void SdlWindow::run() {
    SDL_Event e;
    bool active = true;

    while( active ) {

        // lock surface from editing
        if( SDL_MUSTLOCK( surface_ ) ) { SDL_LockSurface( surface_ ); }

        // show
        SDL_BlitSurface( surface_, NULL, windowSurface_, NULL );
        SDL_UpdateWindowSurface( window_ );

        // prepare surface for editing
        if( SDL_MUSTLOCK( surface_ ) ) { SDL_UnlockSurface( surface_ ); }

        //Handle queued events
        while( SDL_PollEvent( &e ) != 0 )
        {
            // display type as integer (obviously an enum)
            // std::cout << e.type << std::endl;

            // individual event reactions

            // general event reactions
            for( auto react : generalCallback_ ) {
                react( this, e );
            }
            
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                active = false;
            }
        }

        // per-frame notifiees
        for( auto react : frameCallback_ ) {
            react( this );
        }

    }

}

// --------------------------------------------------------------------------------------------------------------------
// supporting functions

void PutPixel32_nolock(SDL_Surface * surface, int x, int y, Uint32 color)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint32));
    *((Uint32*)pixel) = color;
}