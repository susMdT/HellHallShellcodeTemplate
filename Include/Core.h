
#include <windows.h>
#include <Macros.h>
#include <stdio.h>
UINT_PTR GetRIP(VOID);

typedef struct {

    struct {
        WIN32_FUNC( MessageBoxA );
        WIN32_FUNC( LoadLibraryA );
        WIN32_FUNC( RtlSecureZeroMemory );
        WIN32_FUNC( printf );
    } Win32; 

    struct {
        // Basics
        HMODULE     Kernel32;
        HMODULE     Ntdll;
        HMODULE     Msvcrt;
        HMODULE     User32;
    } Modules;

} INSTANCE, *PINSTANCE;