#pragma once

#include <array>

#include "alglib/src/ap.h"
#include "alglib/src/linalg.h"

namespace LinAlg {

    class Vector {
     public:
        Vector( size_t _n, bool _init=true );
        Vector( std::initializer_list< double > _value );
        
        void valueIs( const Vector & _value );
        void valueIs( size_t index, double _value );
        void valueInc( const Vector & _a );
        void valueInc( size_t index, double _a );
        void valueDec( const Vector & _a );
        void valueDec( size_t index, double _a );
        void valueMul( const Vector & _a );
        void valueMul( size_t index, double _a );
        void valueMul( double _a );

        size_t n() const { return n_; }
        double value( size_t index ) const;
        alglib::real_1d_array * value() const { return &value_; }
        std::string stringValue() const { return value_.tostring( n_ ); }
     protected:
        size_t n_;
        mutable alglib::real_1d_array value_;
    };

    class Basis {
     public:
        Basis( size_t _n, bool _init=true );
        void valueIs( size_t row, size_t col, double _value );
        void transpose();
        void orthonormalize();

        Basis rotate( size_t u, size_t v, const double & rads );

        size_t n() const { return n_; }
        double value( size_t row, size_t col ) const;
        Vector basisVector( size_t row ) const;

        alglib::real_2d_array * value() const { return &value_; }
        std::string stringValue() const { return value_.tostring( n_ ); }
     protected:
        size_t n_;
        mutable alglib::real_2d_array value_;
    };

     // matrix multiplication
    Basis dot( const Basis & _a, const Basis & _b );
    Basis operator%( const Basis & _a, const Basis & _b );

     // matrix multiplication
    Vector dot( const Basis & _a, const Vector & _b );
    Vector operator%( const Basis & _a, const Vector & _b );
     // matrix multiplication
    Vector dot( const Vector & _a, const Basis & _b );
    Vector operator%( const Vector & _a, const Basis & _b );

    Vector add( const Vector & _a, const Vector & _b );
    Vector operator+( const Vector & _a, const Vector & _b );
    Vector sub( const Vector & _a, const Vector & _b );
    Vector operator-( const Vector & _a, const Vector & _b );
    Vector mul( const Vector & _a, double _b );
    Vector operator*( const Vector & _a, double _b );
     // inner product
    double dot( const Vector & _a, const Vector & _b );
    double operator%( const Vector & _a, const Vector & _b );
     // angle between vectors
    double angle( const Vector & _a, const Vector & _b );
     // angle between vectors
    Vector project( const Vector & _a, const Vector & onto );
}