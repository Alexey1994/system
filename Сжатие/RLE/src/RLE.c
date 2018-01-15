#define NEW_CHUNK   1
#define RLE_SECTION 2
#define RAW_SECTION 3


static char memory_comparision(char *a1, char *a2, unsigned int length)
{
    for(; length; length--, a1++, a2++)
        if(*a1!=*a2)
            return 0;

    return 1;
}


void compress_RLE(Stream *input_stream, Stream *output_stream, int chunk_size)
{
    char current_state                = NEW_CHUNK;
    int  count_data                   = 1;
    int  count_buffer;
    char previouse_data[chunk_size];
    char current_data[chunk_size];
    char buffer[128*chunk_size];
    int  i;
    int  j;

    //if(end_stream(input_stream))
        //return;

    for(i=0; i<chunk_size; i++)
    {
        current_data[i]=input_stream->head;
        get_stream_byte(input_stream);
    }

    memcpy(buffer, current_data, chunk_size);
    count_buffer=1;

    while(!end_stream(input_stream))
    {
        memcpy(previouse_data, current_data, chunk_size);

        for(i=0; i<chunk_size; i++)
        {
            current_data[i]=input_stream->head;
            get_stream_byte(input_stream);
        }

        count_data++;

        if(memory_comparision(current_data, previouse_data, chunk_size))
        {
            switch(current_state)
            {
            case RAW_SECTION://RAW->RLE
                    put_stream_byte(output_stream, count_buffer-1);

                    for(i=0; i<count_buffer*chunk_size; i++)
                        put_stream_byte(output_stream, buffer[i]);

                    count_data=1;
                    current_state=RLE_SECTION;
                    break;

                case NEW_CHUNK:
                    current_state=RLE_SECTION;
                    break;
            }
        }
        else
        {
            switch(current_state)
            {
                case RLE_SECTION://RLE->RAW
                    printf("%d\n", count_data);
                    put_stream_byte(output_stream, count_data+127);

                    for(i=0; i<chunk_size; i++)
                        put_stream_byte(output_stream, previouse_data[i]);

                    count_buffer=0;
                    count_data=0;
                    current_state=NEW_CHUNK;
                    break;

                case RAW_SECTION:
                    memcpy(buffer+count_buffer*chunk_size, previouse_data, chunk_size);
                    count_buffer++;
                    break;

                case NEW_CHUNK:
                    memcpy(buffer, previouse_data, chunk_size);
                    //memcpy(buffer+chunk_size, current_data, chunk_size);
                    count_buffer=1;
                    current_state=RAW_SECTION;
                    break;
            }
        }


        if(count_data==128)
        {
            switch(current_state)
            {
                case RLE_SECTION:
                    put_stream_byte(output_stream, count_data+127);

                    for(i=0; i<chunk_size; i++)
                        put_stream_byte(output_stream, current_data[i]);
                    break;

                case RAW_SECTION:
                    put_stream_byte(output_stream, count_buffer-1);

                    for(i=0; i<count_buffer*chunk_size; i++)
                        put_stream_byte(output_stream, buffer[i]);

                    count_buffer=0;
                    break;
            }

            count_data=0;
            current_state=NEW_CHUNK;
        }
    }
/*
    switch(current_state)
    {
        case RLE_SECTION:
            put_stream_byte(output_stream, count_data+127);

            for(i=0; i<chunk_size; i++)
                put_stream_byte(output_stream, current_data[i]);
            break;

        case RAW_SECTION:
            put_stream_byte(output_stream, count_buffer-1);

            for(i=0; i<count_buffer*chunk_size; i++)
                put_stream_byte(output_stream, buffer[i]);
            break;

        case NEW_CHUNK:
            put_stream_byte(output_stream,  0);

            for(i=0; i<chunk_size; i++)
                put_stream_byte(output_stream, current_data[i]);
            break;
    }*/
}


void decompress_RLE(Stream *input_stream, Stream *output_stream, int chunk_size)
{
    char chunk_count;
    char current_byte[chunk_count];
    int  i;

    while(!end_stream(input_stream))
    {
        chunk_count=input_stream->head;

        if(chunk_count>=0)
        {
            for(; chunk_count>=0; chunk_count--)
            {
                for(i=0; i<chunk_size; i++)
                {
                    get_stream_byte(input_stream);
                    put_stream_byte(output_stream, input_stream->head);
                }
            }
        }
        else
        {
            for(i=0; i<chunk_size; i++)
            {
                get_stream_byte(input_stream);
                current_byte[i]=input_stream->head;
            }

            for(; chunk_count<=0; chunk_count--)
                for(i=0; i<chunk_size; i++)
                    put_stream_byte(output_stream, current_byte[i]);
        }

        get_stream_byte(input_stream);
    }
}
