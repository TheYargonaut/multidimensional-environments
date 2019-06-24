#include "DemoObj.h"

#include <cmath>
#include <limits>

#include <iostream>

namespace mdv {

    // calculate distance along the ray from the position. "No intersection" signified by NaN
    double HyperSphere::distance( const LinAlg::Vector & _position, const LinAlg::Vector & _ray ) const {
        
        LinAlg::Vector v = _position - position_;
        double v_dot_d = dot( v, _ray );
        double v_sqrd = dot( v, v );

        // std::cout << v_dot_d << std::endl;

        // check for solution
        double internal = v_dot_d * v_dot_d - v_sqrd + radius_ * radius_;
        if( internal < 0.0 ) {
            return std::numeric_limits< double >::quiet_NaN();
        }
        double sqrtInternal = sqrt( internal );
        double d0 = sqrtInternal - v_dot_d;
        double d1 = -sqrtInternal - v_dot_d;

        // return lowest non-negative solution
        if( d0 >= 0.0 ) {
            if( d0 < d1 || d1 < 0.0 ) {
                return d0;
            }
            return d1;
        }
        return std::numeric_limits< double >::quiet_NaN();
    }

    // calculate color when viewed from position along ray/normal
    Color HyperSphere::color( const LinAlg::Vector & _position,
                    const LinAlg::Vector & _ray,
                    int _TTL,
                    const Universe * _universe ) const {
        
        // point of intersection
        double dist = distance( _position, _ray );
        if( isnan( dist ) ) {
            if( _universe ) {
                return _universe->background();
            }
            return Color( 0, 0, 0 );
        }

        // light
        return color_;
        if( !_universe ) { return color_; }
        LinAlg::Vector intersect = _position + _ray * ( dist - 1E-10 ); // get off surface
        Color light = _universe->light( intersect, intersect - position_ );
        light.redIs( color_.red() * light.red() );
        light.blueIs( color_.blue() * light.blue() );
        light.greenIs( color_.green() * light.green() );
        return light;
    }

    // TODO
    // calculate distance along the ray from the position. "No intersection" signified by NaN
    double HyperCube::distance( const LinAlg::Vector & _position, const LinAlg::Vector & _ray ) const {
        return 0.0;
    }

    // TODO
    // calculate color when viewed from position along ray/normal
    Color HyperCube::color( const LinAlg::Vector & _position,
                             const LinAlg::Vector & _ray,
                             int _TTL,
                             const Universe * universe_ ) const {
        return Color( 0, 0, 0 );
    }
}