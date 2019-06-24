#include "View.h"
#include "Multithread.h"

#include <SDL.h>
#include <iostream>
#include <list>
#include <process.h>
#include <windows.h>

namespace mdv {

    void SimpleView::drawFrame( AttrWindow::Window * _window ) const {
        int height = _window->height(), width = _window->width();

        double scale = 2.0 / ( height + width );

        LinAlg::Vector normal = orientation_.basisVector( 0 );
        LinAlg::Vector right = orientation_.basisVector( 1 );
        right.valueMul( -scale );
        LinAlg::Vector down = orientation_.basisVector( 2 );
        down.valueMul( -scale );

        // start at upper left
        LinAlg::Vector rowAnchor = LinAlg::mul( right, -width / 2.0 );
        rowAnchor.valueInc( LinAlg::mul( down, -height / 2.0 ) );
        rowAnchor.valueInc( position_ );

        // straight vectors along the 1st basis axis with parallelism
        std::list< thread::Handle > handle;
        for( int i = 0; i < height; i++ ) {
            LinAlg::Vector runner = LinAlg::mul( rowAnchor, 1.0 );

            handle.push_back( 
                thread::start( [ &normal, &right, width, _window, this, i, runner ]() mutable {
                    for( int j = 0; j < width; j++ ) {
                        Color color = universe_->color( runner, normal );
                        _window->pixelIs( j, i, color.pixel() );
                        runner.valueInc( right );
                    } } ) ); 

            rowAnchor.valueInc( down );
        }

        for( auto const & h : handle ) {
            thread::join( h );
        }
    }

    void PerspectiveView::drawFrame( AttrWindow::Window * _window ) const {
        int height = _window->height(), width = _window->width();

        double scale = 2.0 / ( height + width );

        LinAlg::Vector normal = orientation_.basisVector( 0 );
        LinAlg::Vector right = orientation_.basisVector( 1 );
        right.valueMul( -scale );
        LinAlg::Vector down = orientation_.basisVector( 2 );
        down.valueMul( -scale );

        for( int i = 0; i < height; i++ ) {
            for( int j = 0; j < width; j++ ) {
                
            }
        }
    }

    void PeripheralView::drawFrame( AttrWindow::Window * _window ) const {
        int height = _window->height(), width = _window->width();

        for( int i = 0; i < height; i++ ) {
            for( int j = 0; j < width; j++ ) {
                
            }
        }
    }

}