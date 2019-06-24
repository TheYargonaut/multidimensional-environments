#pragma once

#include "../Base.h"
#include "../Universe.h"
#include "../LinAlg.h"

namespace mdv {

    class PointSource : public Luminator {
     public:
        PointSource( const LinAlg::Vector & _position, const Color & _color )
        : position_( _position ), color_ ( _color ) {}

        Color light( const LinAlg::Vector & _position, const LinAlg::Vector & _normal,
                     const Universe * _universe ) const;
     protected:
        LinAlg::Vector position_;
        Color color_;
    };

    // sun
}