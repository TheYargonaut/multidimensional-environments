#include "DemoLight.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace mdv {

    Color PointSource::light( const LinAlg::Vector & _position,
                              const LinAlg::Vector & _normal,
                              const Universe * _universe ) const {
        // get distance
        LinAlg::Vector diff = position_ - _position ;
        double dist = sqrt( diff % diff );
        diff.valueMul( 1/dist ); // normalize

        // check shadow
        if( _universe ) {
            double block = _universe->distance( _position, diff );
            if( !isnan( block ) && ( block < dist ) ) {
                return Color( 0.0, 0.0, 0.0 );
            }
        }

        // intensity
        double factor = 1.0 / ( 4.0 * M_PI * dist * dist );

        // dot product
        if( _normal.n() ) {
            factor *= _normal % diff;
        }

        // reduce by dimness factor
        return Color( color_.red() * factor,
                      color_.green() * factor,
                      color_.blue() * factor );
    }

}