private procedure write_in_debug(Byte *source, Byte byte)
{
    printf("%c", byte);
}


procedure initialize_debug_output (Output *output)
{
    initialize_output(output, 0, &write_in_debug);
}
