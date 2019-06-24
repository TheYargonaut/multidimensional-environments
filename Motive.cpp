#include "Motive.h"

#include <iostream>

namespace mdv {

    void Motive::rotate( size_t _u, size_t _v, double _rads ) {
        LinAlg::Basis rotMat = orientation_.rotate( _u, _v, _rads );
        orientation_ = orientation_ % rotMat;

        // debug tracing
        std::cout << "u: " << _u << "; v: " << _v << "; r: " << _rads << std::endl;
        std::cout << "rotMat: " << rotMat.stringValue() << std::endl;
        std::cout << "new orient: " << orientation_.stringValue() << std::endl;
    }

    void Motive::translate( size_t _direction, double _distance ) {
        auto translation = orientation_.basisVector( _direction );
        translation.valueMul( _distance );
        position_.valueInc( translation );
    }

}