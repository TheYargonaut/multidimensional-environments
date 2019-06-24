#pragma once

#include "LinAlg.h"
#include "Base.h"
#include "Universe.h"
#include "AttrWindow.h"
#include "Motive.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace mdv {
    
    // view-camera base class
    class View : public Motive {
     public:
        View( size_t _n, Universe * _universe ) 
        : Motive( _n ), universe_( _universe ) {}

        virtual void drawFrame( AttrWindow::Window * _window ) const = 0;
     protected:
        Universe * universe_;
    };

    // Basic view-camera: one vector per pixel, straight forward
    class SimpleView : public View {
     public:
        SimpleView( size_t _n, Universe * _universe ) 
        : View( _n, _universe ) {}
        void drawFrame( AttrWindow::Window * _window ) const;
    };

    // Vectors splay out toward edges up to maximum for perpective view
    class PerspectiveView : public View {
     public:
        PerspectiveView( size_t _n, Universe * _universe, double _fov=M_PI/2 ) 
        : View( _n, _universe ), fov_( _fov ) {}
        void drawFrame( AttrWindow::Window * _window ) const;
     protected:
        double fov_;
    };

    // Sparse vectors toward edges (weighted knn or something)
    class PeripheralView : public View {
     public:
        PeripheralView( size_t _n, Universe * _universe ) 
        : View( _n, _universe ) {}
        void drawFrame( AttrWindow::Window * _window ) const;
    };

}