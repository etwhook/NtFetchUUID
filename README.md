
# NtFetchUUID

Natively Fetching UUID With SMBIOS.


## Usage In AC/AT Software
This method of fetching UUID / HWID is used in alot in ACs/ATs, Both usermode and kernelmode, One example is **Byfron**, Which utilizes this method to fetch UUIDs for hardware bans, Combined with their inline syscalls this makes it very hard to hook from usermode.


## Resources

- [BaseQuerySystemFirmware - ReactOS](https://doxygen.reactos.org/da/daa/dll_2win32_2kernel32_2client_2sysinfo_8c.html#a45c828685fe0f2f6507d76fe72bfdf5b)
- [NtQuerySystemInformation - MSDN](https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntquerysysteminformation)