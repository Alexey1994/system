Byte* read_WAV(WAV *wav, Input *input)
{
    N_32           i;
    unsigned int   source_size;
    unsigned int   source_subchunk_size;
    unsigned short source_format;
    unsigned short source_num_channels;
    unsigned int   frequency;
    unsigned int   source_byte_rate;
    unsigned short source_block_align;
    unsigned short source_bits_per_sample;
    //unsigned int   data_size;

    if(!read_if_next(input, "RIFF"))
        return 0;

    source_size=read_binary_N_32(input);

    if(!read_if_next(input, "WAVEfmt "))
        return 0;

    source_subchunk_size   = read_binary_N_32(input);
    source_format          = read_binary_N_16(input);
    source_num_channels    = read_binary_N_16(input);
    frequency              = read_binary_N_32(input);
    source_byte_rate       = read_binary_N_32(input);
    source_block_align     = read_binary_N_16(input);
    source_bits_per_sample = read_binary_N_16(input);

    while(!read_if_next(input, "data"))
    {
        read_byte(input);
        read_byte(input);
        read_byte(input);
        read_byte(input);

        source_subchunk_size = read_binary_N_32(input);

        for(i=0; i<source_subchunk_size; ++i)
            read_byte(input);
    }

    wav->data_size = read_binary_N_32(input);
    //Byte *data = new_array(Byte, data_size);
    //read_byte_array(input, data, data_size);

    //return data;
}
