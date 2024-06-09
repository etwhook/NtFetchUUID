#include <Windows.h>
#include<winternl.h>
#include<print>

typedef NTSTATUS(NTAPI* t_NtQuerySystemInformation) (
    SYSTEM_INFORMATION_CLASS SystemInformationClass,
    PVOID                    SystemInformation,
    ULONG                    SystemInformationLength,
    PULONG                   ReturnLength
    );

typedef enum _SYSTEM_FIRMWARE_TABLE_ACTION {
    SystemFirmwareTable_Enumerate,
    SystemFirmwareTable_Get
} SYSTEM_FIRMWARE_TABLE_ACTION;

typedef struct _SYSTEM_FIRMWARE_TABLE_INFORMATION {
    ULONG 	ProviderSignature;
    SYSTEM_FIRMWARE_TABLE_ACTION Action;
    ULONG 	TableID;
    ULONG 	TableBufferLength;
    UCHAR 	TableBuffer[ANYSIZE_ARRAY];
} SYSTEM_FIRMWARE_TABLE_INFORMATION, * PSYSTEM_FIRMWARE_TABLE_INFORMATION;


typedef struct _DMIHeader
{
    BYTE type;
    BYTE length;
    WORD handle;
} DMIHeader, * PDMIHeader;

typedef struct SMBIOSData
{
    BYTE    Used20CallingMethod;
    BYTE    SMBIOSMajorVersion;
    BYTE    SMBIOSMinorVersion;
    BYTE    DmiRevision;
    DWORD   Length;
    BYTE    SMBIOSTableData[];
} SMBIOSData, * PSMBIOSData;

t_NtQuerySystemInformation fnNtQuerySystemInformation = (t_NtQuerySystemInformation)GetProcAddress(GetModuleHandleA("NTDLL"), "NtQuerySystemInformation");
