#pragma once

#include <SDL.h>

#include "LinAlg.h"

// base interface of scene, object, surface, camera, etc.
// serializable, deserializable

namespace mdv {

    class Color {
     public:
        Color( double _red, double _green, double _blue )
        : red_( _red ), green_( _green ), blue_( _blue ) {}

        void redIs( double _red ) { red_ = _red; }
        void greenIs( double _green ) { green_ = _green; }
        void blueIs( double _blue ) { blue_ = _blue; }

        double red() const { return red_; }
        double green() const { return green_; }
        double blue() const { return blue_; }
        Uint32 pixel() const;
     protected:
        double red_, green_, blue_;
    };

    // universe forward declaration
    class Universe;

    // all parts of scenes should implement this interface
    class Savable {
     public:
        virtual std::string serialize() const = 0;
        virtual void deserialize( const std::string & ) = 0;
    };

    // light object base class
    class Luminator {
     public:
         virtual Color light( const LinAlg::Vector & _position, const LinAlg::Vector & _normal,
                              const Universe * _universe ) const = 0;
    };
    
    // visible object base class
    class Renderable {
     public:
        // calculate distance along the ray from the position. "No intersection" signified by NaN
        virtual double distance( const LinAlg::Vector & _position, const LinAlg::Vector & _ray ) const = 0;
        // calculate color when viewed from position along ray/normal
        virtual Color color( const LinAlg::Vector & _position, const LinAlg::Vector & _ray,
                             int _TTL, const Universe * _universe ) const = 0;
    };

}