#include "Def.h"

void PrintUUID(PBYTE uuidBuffer)
{
    printf("%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n",
        uuidBuffer[3], uuidBuffer[2], uuidBuffer[1], uuidBuffer[0], uuidBuffer[5], uuidBuffer[4], uuidBuffer[7], uuidBuffer[6],
        uuidBuffer[8], uuidBuffer[9], uuidBuffer[10], uuidBuffer[11], uuidBuffer[12], uuidBuffer[13], uuidBuffer[14], uuidBuffer[15]);
}


int main(int argc, char* argv[])
{
    ULONG buffSize = 65536;
    PSYSTEM_FIRMWARE_TABLE_INFORMATION firmwareTableInfo = (PSYSTEM_FIRMWARE_TABLE_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, buffSize);

    firmwareTableInfo->Action = SystemFirmwareTable_Get;
    firmwareTableInfo->ProviderSignature = 'RSMB';
    firmwareTableInfo->TableBufferLength = buffSize;

    NTSTATUS okF = fnNtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)0x4C, firmwareTableInfo, buffSize, &buffSize);
    PSMBIOSData buf = (PSMBIOSData)(firmwareTableInfo->TableBuffer);

    PSMBIOSData Smbios;
    PDMIHeader header;

    Smbios = (PSMBIOSData)buf;
    BYTE* tableData = Smbios->SMBIOSTableData;

    for (int i = 0; i < Smbios->Length; i++) {
        header = (PDMIHeader)tableData;

       if (header->type == 1) {
           PrintUUID(tableData + 0x8);
        }

        tableData += header->length;
        while ((*(WORD*)tableData) != 0) tableData++;
        tableData += 2;
    }

    return 0;
}