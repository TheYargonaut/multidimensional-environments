#include <cmath>
#include <cassert>

#include <iostream>

#include "LinAlg.h"

namespace LinAlg {

    Vector::Vector( size_t _n, bool init ) : n_( _n ) {
        value_.setlength( n_ );
        if ( !init ) { return; }
        for( unsigned int index = 0; index < n_; index++ ) {
            value_[ index ] = 0.0;
        }
    }
    Vector::Vector( std::initializer_list< double > _value ) {
        n_ = _value.size();
        value_.setlength( n_ );
        unsigned int index = 0;
        for( const auto & v : _value ) {
            value_[ index++ ] = v;
        }
    }

    void Vector::valueIs( const Vector & _value ) {
        assert( n_ == _value.n_ );
        alglib::vmove( &value_[0], &_value.value()[0][0], n_ );
    }
    void Vector::valueIs( size_t index, double _value ) {
        value_[ index ] = _value;
    }
    void Vector::valueInc( const Vector & _a ) {
        assert( n_ == _a.n_ );
        for( size_t i = 0; i < n_; i++ ) {
            value_[ i ] += _a.value( i );
        }
    }
    void Vector::valueInc( size_t index, double _a ) {
        assert( index < n_ );
        value_[ index ] += _a;
    }
    void Vector::valueDec( const Vector & _a ) {
        assert( n_ == _a.n_ );
        for( size_t i = 0; i < n_; i++ ) {
            value_[ i ] -= _a.value( i );
        }
    }
    void Vector::valueDec( size_t index, double _a ) {
        assert( index < n_ );
        value_[ index ] -= _a;
    }
    void Vector::valueMul( const Vector & _a ) {
        assert( n_ == _a.n_ );
        for( size_t i = 0; i < n_; i++ ) {
            value_[ i ] *= _a.value( i );
        }
    }
    void Vector::valueMul( size_t index, double _a ) {
        assert( index < n_ );
        value_[ index ] *= _a;
    }
    void Vector::valueMul( double _a ){
        for( size_t i = 0; i < n_; i++ ) {
            value_[ i ] *= _a;
        }
    }

    double Vector::value( size_t index ) const {
        return value_[ index ];
    }

    Basis::Basis( size_t _n, bool init ) : n_( _n ) {
        value_.setlength( n_, n_ );
        if ( !init ) { return; }
        for( unsigned int row = 0; row < n_; row++ ) {
            for( unsigned int col = 0; col < n_; col++ ) {
                value_[ row ][ col ] = ( row == col )? 1.0 : 0.0;
            }
        }
    }


    void Basis::valueIs( size_t row, size_t col, double _value ) {
        value_[ row ][ col ] = _value;
    }

    void Basis::transpose() {
        alglib::real_2d_array tmp;
        tmp.setlength( n_, n_ );
        alglib::rmatrixtranspose( n_, n_, value_, 0, 0, tmp, 0, 0 );
        value_ = tmp;
    }

    void Basis::orthonormalize() {

    }

    Basis Basis::rotate( size_t u, size_t v, const double & rads ) {
        double sa = sin( rads );
        double ca = cos( rads ) - 1.0;

        // https://stackoverflow.com/questions/50337642/how-to-calculate-a-rotation-matrix-in-n-dimensions-given-the-point-to-rotate-an
        // make large identity matrix (declare as basis)
        Basis rotmat{ n_, true }; // big identity matrix
        // make 2*n basis matrix
        alglib::real_2d_array plane;
        plane.setlength( n_, 2 );
        alglib::vmove( &plane[ 0 ][ 0 ], plane.getstride(), &value_[ u ][ 0 ], 1, n_ );
        alglib::vmove( &plane[ 0 ][ 1 ], plane.getstride(), &value_[ v ][ 0 ], 1, n_ );
        // make 2d rotation matrix minus 2d identity matrix
        alglib::real_2d_array rot;
        rot.setlength( 2, 2 );
        rot[ 0 ][ 0 ] = ca;
        rot[ 0 ][ 1 ] = -sa;
        rot[ 1 ][ 0 ] = sa;
        rot[ 1 ][ 1 ] = ca;
        // multiply natively and stick in basis (or directly subtract)
        alglib::real_2d_array tmp;
        tmp.setlength( n_, 2 );
        alglib::rmatrixgemm( n_, 2, 2, 1,
                            plane, 0, 0, 0,
                            rot, 0, 0, 0,
                            0, tmp, 0, 0 );
        alglib::rmatrixgemm( n_, n_, 2, 1,
                            tmp, 0, 0, 0,
                            plane, 0, 0, 1,
                            1, *rotmat.value(), 0, 0 );
        return rotmat;
    }

    double Basis::value( size_t row, size_t col ) const {
        return value_[ row ][ col ];
    }
    
    Vector Basis::basisVector( size_t row ) const {
        Vector out( n_, false );
        for( size_t i = 0; i < n_; i++ ) {
            out.valueIs( i, value_[ row ][ i ] );
        }
        return out;
    }

    // matrix multiplication
    Basis dot( const Basis & _a, const Basis & _b ) {
        assert( _a.n() == _b.n() );
        size_t n_ = _a.n();
        Basis out{ n_, false };
        alglib::rmatrixgemm( n_, n_, n_, 1,
                            *_a.value(), 0, 0, 0,
                            *_b.value(), 0, 0, 0,
                            0, *out.value(), 0, 0 );
        return out;
    }
    Basis operator%( const Basis & _a, const Basis & _b ) { return dot( _a, _b ); }

    // matrix multiplication
    Vector dot( const Basis & _a, const Vector & _b ) {
        assert( _a.n() == _b.n() );
        size_t n_ = _a.n();
        Vector out( n_, false );
        alglib::rmatrixgemv( n_, n_, 1, *_a.value(), 0, 0, 0, 
                                    *_b.value(), 0, 0, *out.value(), 0 );
        return out;
    }
    Vector operator%( const Basis & _a, const Vector & _b ) { return dot( _a, _b ); }
    // matrix multiplication
    Vector dot( const Vector & _a, const Basis & _b ) {
        assert( _a.n() == _b.n() );
        size_t n_ = _a.n();
        Vector out( n_, false );
        alglib::rmatrixgemv( n_, n_, 1, *_b.value(), 0, 0, 1, 
                                    *_a.value(), 0, 0, *out.value(), 0 );
        return out;
    }
    Vector operator%( const Vector & _a, const Basis & _b ) { return dot( _a, _b ); }

    Vector add( const Vector & _a, const Vector & _b ) {
        assert( _a.n() == _b.n() );
        size_t n_ = _a.n();
        Vector out( n_, false );
        alglib::vmove( &out.value()[0][0], &_a.value()[0][0], n_ );
        out.valueInc( _b );
        return out;
    }
    Vector operator+( const Vector & _a, const Vector & _b ) { return add( _a, _b ); }
    Vector sub( const Vector & _a, const Vector & _b ) {
        assert( _a.n() == _b.n() );
        size_t n_ = _a.n();
        Vector out( n_, false );
        alglib::vmove( &out.value()[0][0], &_a.value()[0][0], n_ );
        out.valueDec( _b );
        return out;
    }
    Vector operator-( const Vector & _a, const Vector & _b ) { return sub( _a, _b ); }
    Vector mul( const Vector & _a, double _b ) {
        size_t n_ = _a.n();
        Vector out( n_, false );
        alglib::vmove( &out.value()[0][0], &_a.value()[0][0], n_, _b );
        return out;
    }
    Vector operator*( const Vector & _a, double _b ) { return mul( _a, _b ); }
    // inner product
    double dot( const Vector & _a, const Vector & _b ) {
        assert( _a.n() == _b.n() );
        return alglib::vdotproduct( &_a.value()[0][0], &_b.value()[0][0], _a.n() );
    }
    double operator%( const Vector & _a, const Vector & _b ) { return dot( _a, _b ); }
    // angle between vectors in radians
    double angle( const Vector & _a, const Vector & _b ) {
        assert( _a.n() == _b.n() );
        size_t n_ = _a.n();
        return acos( alglib::vdotproduct( &_a.value()[0][0], &_b.value()[0][0], n_ ) /
                    sqrt( alglib::vdotproduct( &_a.value()[0][0], &_a.value()[0][0], n_ ) * 
                        alglib::vdotproduct( &_b.value()[0][0], &_b.value()[0][0], n_ ) ) );
    }
    // angle between vectors
    Vector project( const Vector & _a, const Vector & onto ) {
        assert( _a.n() == onto.n() );
        size_t n_ = _a.n();
        Vector out( n_, false );
        alglib::vmove( &out.value()[0][0], &onto.value()[0][0], n_, 
                    alglib::vdotproduct( &_a.value()[0][0], &out.value()[0][0], n_ ) /
                    alglib::vdotproduct( &out.value()[0][0], &out.value()[0][0], n_ ) );
        return out;
    }

}