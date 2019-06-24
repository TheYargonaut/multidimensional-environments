# pragma once
// AOP interface to the window

#include <SDL.h>
#include <functional>
#include <list>
#include <map>

namespace AttrWindow {

    class Window {
     public:
        virtual int width() const = 0;
        virtual int height() const = 0;
        virtual Uint32 pixel( int, int ) const = 0;
        virtual void pixelIs( int, int, Uint32 ) = 0;
    };

    typedef std::function< void( Window* ) > Callback;
    typedef std::function< void( Window*, const SDL_Event & ) > GeneralCallback;

    const int DEFAULT_WIDTH = 640;
    const int DEFAULT_HEIGHT = 480;

    class SdlWindow : Window {
     public:
        SdlWindow( int _width=DEFAULT_WIDTH, int _height=DEFAULT_HEIGHT );
        SdlWindow( const SdlWindow & ) = delete;
        ~SdlWindow();

        // mutators
        void widthIs( int _width );
        void heightIs( int _height );
        void dimIs( int _width, int _height );
        void pixelIs( int x, int y, Uint32 color );

        // accessors
        int width() const { return width_; }
        int height() const { return height_; }
        Uint32 pixel( int x, int j ) const;

        // call only on specified event
        void enqEventCallback( Callback _callback, SDL_Event );
        // call on every event
        void enqGeneralCallback( GeneralCallback _callback );
        // call every frame
        void enqFrameCallback( Callback _callback );

        // start main loop
        void run();

     protected:
        int width_;
        int height_;
        SDL_Window* window_;
        SDL_Surface* windowSurface_;
        SDL_Surface* surface_;
        std::map< SDL_Event, std::list< Callback > > eventCallback_;
        std::list< GeneralCallback > generalCallback_;
        std::list< Callback > frameCallback_;
    };

}