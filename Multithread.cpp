#include "Multithread.h"

namespace thread {

    unsigned __stdcall thread( void* pArguments ) { 
        ( *( Callable * )pArguments )();
        return 0;
    }
    
    Handle start( const Callable & callable ) {
        Callable * c = new Callable( callable );
        unsigned int threadId;
        return (Handle)_beginthreadex( NULL, 0, &thread, c, 0, &threadId );
    }
    
    void join( const Handle & handle, DWORD timeout ) {
        WaitForSingleObject( handle, timeout );
    }
}