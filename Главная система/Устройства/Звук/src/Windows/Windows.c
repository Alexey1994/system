private stdcall procedure play(Byte *sound_device, N_32 uMsg, Sound_Data *data, N_32 *dwParam1, N_32 *dwParam2)
{
    Windows_Sound_Buffer *current_buffer;

    if(uMsg == MM_WOM_DONE)
    {
        if(data->current_buffer_index)
            current_buffer = &data->buffer2;
        else
            current_buffer = &data->buffer1;

        waveOutWrite(sound_device, current_buffer, sizeof(Windows_Sound_Buffer));
        data->current_buffer_index = !data->current_buffer_index;

        if(data->current_buffer_index)
            current_buffer = &data->buffer2;
        else
            current_buffer = &data->buffer1;

        read_byte_array(data->input, current_buffer->data, current_buffer->buffer_length);
        waveOutWrite(sound_device, current_buffer, sizeof(Windows_Sound_Buffer));
    }
}


procedure play_sound(Input *input)
{
    Sound_Data            data;
    Byte                 *sound_device;
    Windows_Sound_Format  sound_format;

    sound_format.format                       = PCM_WAVE_FORMAT;
    sound_format.number_of_channels           = 2;
    sound_format.samples_per_seconds          = 44100;
    sound_format.bits_per_sample              = 16;
    sound_format.block_align                  = sound_format.bits_per_sample / 8 * sound_format.number_of_channels;
    sound_format.bytes_per_seconds            = sound_format.samples_per_seconds * sound_format.block_align;
    sound_format.size_of_appended_information = 0;

    if(waveOutOpen(&sound_device, -1, &sound_format, &play, &data, CALLBACK_FUNCTION))
        return 0;

    data.input                  = input;
    data.current_buffer_index   = 1;

    data.buffer1.data           = data.buffer1_data;
    data.buffer1.buffer_length  = SOUND_BUFFER_LENGTH;
    data.buffer1.bytes_recorded = 0;
    data.buffer1.flags          = 0;
    data.buffer1.loops          = 0;

    data.buffer2.data           = data.buffer2_data;
    data.buffer2.buffer_length  = SOUND_BUFFER_LENGTH;
    data.buffer2.bytes_recorded = 0;
    data.buffer2.flags          = 0;
    data.buffer2.loops          = 0;

    waveOutPrepareHeader(sound_device, &data.buffer2, sizeof(Windows_Sound_Buffer));
    waveOutPrepareHeader(sound_device, &data.buffer1, sizeof(Windows_Sound_Buffer));

    read_byte_array(data.input, data.buffer1.data, data.buffer1.buffer_length);
    read_byte_array(data.input, data.buffer2.data, data.buffer2.buffer_length);

    waveOutWrite(sound_device, &data.buffer1, sizeof(Windows_Sound_Buffer));
}