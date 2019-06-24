#pragma once

#include "LinAlg.h"

// abstract class providing motion control (rotation, translation, scaling)

namespace mdv{
    
    // extend to use movement in space
    class Motive {
     public:
        Motive( size_t _n ) : n_( _n ), position_( _n ), 
           orientation_( _n ) {}
         
        void positionIs( const LinAlg::Vector & _position ) { position_ = _position; }
        void orientationIs( const LinAlg::Basis & _orientation ) { orientation_ = _orientation; }

        void rotate( size_t _u, size_t _v, double _rads );
        void translate( size_t _direction, double _distance );

        LinAlg::Vector position() { return position_; }
        LinAlg::Basis orientation() { return orientation_; }

     protected:
        size_t n_;
        LinAlg::Vector position_;
        LinAlg::Basis orientation_;
    };
    
}