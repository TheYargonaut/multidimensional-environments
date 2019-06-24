#include "StringManip.h"

template< typename... argv >
std::string stringf( const char* format, argv... args ) {
    const size_t SIZE = std::snprintf( NULL, 0, format, args... );

    std::string output;
    output.resize(SIZE+1);
    std::snprintf( &(output[0]), SIZE+1, format, args... );
    return std::move(output);
}