#include "AttrWindow.h"
#include "Fps.h"
#include "Base.h"
#include "Universe.h"
#include "View.h"
#include "LinAlg.h"
#include "Multithread.h"
#include "objects/DemoObj.h"
#include "objects/DemoLight.h"

#include <SDL.h>
#include <functional>
#include <algorithm>
#include <iostream>
#include <process.h>
#include <windows.h>
#include <string>

class WipeGradient {
 public:
    WipeGradient() : start_( 0 ) {}
    void drawFrame( AttrWindow::Window * _window );
 protected:
    Uint8 start_ = 0;
};

void WipeGradient::drawFrame( AttrWindow::Window * _window ) {
    for( int i = 0; i < _window->height(); ++i ) {
        Uint8 pixRed = start_;
        for( int j = 0; j < _window->width(); ++j ) {
            _window->pixelIs( j, i, pixRed++ << 16 );
        }
    }
    --start_;
}

const size_t N = 4; // dimensionality for testing
const double speed = 0.1; // movement distance
constexpr double rotSpeed = 3.14159 / 8; // angular velocity

int main( int argc, char* argv[] )
{
    // create window
	AttrWindow::SdlWindow window{};

    // Moving gradient test
    // WipeGradient wg{};
    // window.enqFrameCallback( std::bind( &WipeGradient::drawFrame, &wg, std::placeholders::_1 ) );
    
    // monitor framerate
    // FpsPrinter fp{};
    // window.enqFrameCallback( std::bind( &FpsPrinter::checkpoint, &fp, std::placeholders::_1 ) );

    // cap framerate at 60
    // FpsCapper fc{ 60 };
    // window.enqFrameCallback( std::bind( &FpsCapper::checkpoint, &fc, std::placeholders::_1 ) );

    // monitor input events
    // window.enqGeneralCallback( []( AttrWindow::Window* ignore, const SDL_Event & event ) {
    //     // print specific event based on type
    //     // use keycode, not scancode; scancode is layout-independent
    //     switch( event.type ){
    //      case SDL_KEYDOWN:
    //         std::cout << "key down: " << SDL_GetKeyName( event.key.keysym.sym ) << std::endl;
    //         break;
    //      case SDL_KEYUP:
    //         std::cout << "key up: " << SDL_GetKeyName( event.key.keysym.sym ) << std::endl;
    //         break;
    //      default:
    //         std::cout << event.type << std::endl;
    //     }
    // } );

    // build universe and view
    mdv::Universe universe{ N };
    // mdv::PointSource bulb_0( { 1, 1, 1 }, mdv::Color( 20.0, 20.0, 20.0 ) );
    // mdv::PointSource bulb_1( { 0.25, -1, 1 }, mdv::Color( 100.0, 100.0, 100.0 ) );
    mdv::HyperSphere sphere_0( 0.25, { 1, 0, 0, 0 }, mdv::Color( 1.0, 0.0, 0.0 ) );
    mdv::HyperSphere sphere_1( 0.25, { 0, 1, 0, 0 }, mdv::Color( 0.0, 1.0, 0.0 ) );
    mdv::HyperSphere sphere_2( 0.25, { 0, 0, 1, 0 }, mdv::Color( 0.0, 0.0, 1.0 ) );
    mdv::HyperSphere sphere_3( 0.25, { 0, 0, 0, 1 }, mdv::Color( 0.0, 0.0, 1.0 ) );
    // universe.luminatorIs( "Bare Bulb 0", &bulb_0 );
    // universe.luminatorIs( "Bare Bulb 1", &bulb_1 );
    universe.surfaceIs( "Sphere 0", &sphere_0 );
    universe.surfaceIs( "Sphere 1", &sphere_1 );
    universe.surfaceIs( "Sphere 2", &sphere_2 );
    universe.surfaceIs( "Sphere 3", &sphere_2 );
    mdv::SimpleView camera{ N, &universe };
    window.enqFrameCallback( std::bind( &mdv::SimpleView::drawFrame, &camera, std::placeholders::_1 ) );

    // control the camera
    size_t rotAxisA = 0;
    size_t rotAxisB = 1;
    size_t recentAxisA = 0;
    size_t recentAxisB = 1;
    window.enqGeneralCallback( [ & ]( AttrWindow::Window* ignore, const SDL_Event & event ) mutable {
        // print specific event based on type
        // use keycode, not scancode; scancode is layout-independent
        if ( event.type != SDL_KEYDOWN ) { return; }
        size_t key = event.key.keysym.sym;
        if ( key > 47 && key < 58 ) {
            key -= 48;
            if( key < N && key != recentAxisA ) {
                recentAxisB = recentAxisA;
                recentAxisA = key;

                rotAxisA = std::min( recentAxisA, recentAxisB );
                rotAxisB = std::max( recentAxisA, recentAxisB );
            }
            return;
        }
        switch( key ) {
         case SDLK_UP:
            camera.translate( 0, speed );
            break;
         case SDLK_DOWN:
            camera.translate( 0, -speed );
            break;
         case SDLK_RIGHT:
            camera.rotate( rotAxisA, rotAxisB, rotSpeed );
            break;
         case SDLK_LEFT:
            camera.rotate( rotAxisB, rotAxisA, rotSpeed );
            break;
        }
    } );

    window.run();

    /* rotation test
    LinAlg::Basis test{ 3 };
    LinAlg::Basis rt = test.rotate( 0, 1, 0.314 );
    rt.transpose();

    LinAlg::Basis r = test % rt;
    std::cout << r.stringValue() << std::endl;

    rt = r.rotate( 0, 1, 0.314 );
    rt.transpose();
    r = r % rt;
    std::cout << r.stringValue() << std::endl;

    rt = r.rotate( 0, 1, 0.314 );
    rt.transpose();
    r = r % rt;
    std::cout << r.stringValue() << std::endl;

    rt = r.rotate( 0, 1, 0.314 );
    rt.transpose();
    r = r % rt;
    std::cout << r.stringValue() << std::endl;
    */
    
    return 0;
}