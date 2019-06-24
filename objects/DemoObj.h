#pragma once

#include "../Base.h"
#include "../Universe.h"
#include "../LinAlg.h"

// some basic objects for testing out the rendering
namespace mdv {

    class HyperSphere : public Renderable {
     public:
        HyperSphere( double _radius, LinAlg::Vector _position, Color _color )
        : n_( _position.n() ), radius_( _radius ), position_( _position ), color_( _color ) {}
        
        // calculate distance along the ray from the position. "No intersection" signified by NaN
        double distance( const LinAlg::Vector & _position, const LinAlg::Vector & _ray ) const;
        // calculate color when viewed from position along ray/normal
        Color color( const LinAlg::Vector & _position,
                     const LinAlg::Vector & _ray,
                     int _TTL,
                     const Universe * _universe ) const;
     protected:
        size_t n_;
        double radius_;
        LinAlg::Vector position_;
        Color color_;
    };

    class HyperCube : public Renderable {
     public:
        HyperCube( double _sideLen, LinAlg::Vector _position, Color _color )
        : n_( _position.n() ), sideLen_( _sideLen ), position_( _position ), color_( _color ) {}
        
        // calculate distance along the ray from the position. "No intersection" signified by NaN
        double distance( const LinAlg::Vector & _position, const LinAlg::Vector & _ray ) const;
        // calculate color when viewed from position along ray/normal
        Color color( const LinAlg::Vector & _position,
                      const LinAlg::Vector & _ray,
                      int _TTL,
                      const Universe * _universe ) const;
     protected:
        size_t n_;
        double sideLen_;
        LinAlg::Vector position_;
        Color color_;
    };

}