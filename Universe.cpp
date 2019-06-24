#include <limits>
#include <cmath>

#include "Universe.h"

namespace mdv {

    Renderable * Universe::surface( std::string _key ) {
        auto place = surface_.find( _key );
        if( place == surface_.end() ) {
            return NULL;
        }
        return place->second;
    }
    void Universe::surfaceIs( std::string _key, Renderable * _surface ) {
        surface_[ _key ] = _surface;
    }
    void Universe::surfaceDel( std::string _key ) {
        surface_.erase( _key );
    }
    void Universe::surfaceDelAll() {
        surface_.clear();
    }

    Luminator * Universe::luminator( std::string _key ){
        auto place = luminator_.find( _key );
        if( place == luminator_.end() ) {
            return NULL;
        }
        return place->second;
    }
    void Universe::luminatorIs( std::string _key, Luminator * _luminator ) {
        luminator_[ _key ] = _luminator;
    }
    void Universe::luminatorDel( std::string _key ) {
        luminator_.erase( _key );
    }
    void Universe::luminatorDellAll() {
        luminator_.clear();
    }

    // Distance to closest surface
    double Universe::distance( const LinAlg::Vector & position, const LinAlg::Vector & ray ) const {
        double minDist = std::numeric_limits< double >::quiet_NaN();
        for( const auto & s : surface_ ) {
            double dist = s.second->distance( position, ray );
            if( std::isnan( dist ) ) { continue; }
            if( std::isnan( minDist ) || dist < minDist ) {
                minDist = dist;
            }
        }
        return minDist;
    }

    // get light at position with normal. Zero-dimensional normal means return raw value
    Color Universe::light( const LinAlg::Vector & _position, const LinAlg::Vector & _normal ) const {
        double red_comp = 1.0, green_comp = 1.0, blue_comp = 1.0;
        for( const auto & l : luminator_ ) {
            Color c = l.second->light( _position, _normal, this );
            red_comp *= 1 - c.red();
            green_comp *= 1 - c.green();
            blue_comp *= 1 - c.blue();
        }
        // std::cout << ( 1 - red_comp ) << "," << ( 1 - green_comp ) << "," << std::endl;
        return Color( 1 - red_comp, 1 - green_comp, 1 - blue_comp );
    }

    // Get color when viewed from a position along a ray
    Color Universe::color( const LinAlg::Vector & position, const LinAlg::Vector & ray, int TTL ) const {
        double minDist = std::numeric_limits< double >::quiet_NaN();
        Renderable const * closest = NULL;
        for( const auto & s : surface_ ) {
            double dist = s.second->distance( position, ray );
            if( std::isnan( dist ) ) { continue; }
            if( std::isnan( minDist ) || dist < minDist ) {
                minDist = dist;
                closest = s.second;
            }
        }
        if( std::isnan( minDist ) ) { return background_; }
        return closest->color( position, ray, TTL, this );
    }

}