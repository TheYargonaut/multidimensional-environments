# pragma once

#include <string>

template< typename... argv >
std::string stringf( const char* format, argv... args );