#pragma once

#include "Base.h"

#include <map>

// track surfaces, lights, and rendering

namespace mdv {

    class Universe {
     public:
        Universe( size_t _n, Color _background=Color( 0, 0, 0 ) ) 
        : n_( _n ), background_( _background ) {}

        Color background() const { return background_; }

        Renderable * surface( std::string _key );
        void surfaceIs( std::string _key, Renderable * _surface );
        void surfaceDel( std::string _key );
        void surfaceDelAll();

        Luminator * luminator( std::string _key );
        void luminatorIs( std::string _key, Luminator * _luminator );
        void luminatorDel( std::string _key );
        void luminatorDellAll();

        Color light( const LinAlg::Vector & _position,  const LinAlg::Vector & _normal ) const;
        double distance( const LinAlg::Vector & _position, const LinAlg::Vector & _ray ) const;
        Color color( const LinAlg::Vector & _position, const LinAlg::Vector & _ray, int TTL = 0 ) const;
        
     protected:
        size_t n_;
        Color background_;
        std::map< std::string, Renderable* > surface_;
        std::map< std::string, Luminator* > luminator_;
    };

}