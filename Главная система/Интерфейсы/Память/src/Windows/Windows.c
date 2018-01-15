function Byte* allocate_memory (N_32 size)
{
    return VirtualAlloc(0, size, WINDOWS_COMMIT_MEMORY, WINDOWS_PAGE_EXECUTE_READWRITE);
}


procedure free_memory(Byte *memory_address)
{
    VirtualFree(memory_address, 0, WINDOWS_RELEASE_MEMORY);
}