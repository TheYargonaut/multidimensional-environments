#include <process.h>
#include <windows.h>
#include <functional>
#include <map>

namespace thread {

    typedef std::function< void() > Callable;
    typedef HANDLE Handle;

    Handle start( const Callable & callable );
    void join( const Handle & handle, DWORD timeout=INFINITE );
}