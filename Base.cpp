#include "Base.h"

#include <cmath>

namespace mdv{

    #define COLOR_IN( F, S ) ( ( Uint32 )( 0xFF * F + 0.5 ) << S )

    double rectify( double hue ) {
        return tanh( 2 * std::max( 0.0, hue ) );
    }

    Uint32 Color::pixel() const {
        return ( COLOR_IN( rectify( red_ ), 16 ) |
                 COLOR_IN( rectify( green_ ), 8 ) |
                 COLOR_IN( rectify( blue_ ), 0 )
        );
    }

}