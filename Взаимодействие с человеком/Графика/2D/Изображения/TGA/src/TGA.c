function Canvas* load_TGA (Input *input)
{
    Byte    uncompressed[]= {0,0,2,0,0,0,0,0,0,0,0,0};
    N_32    width;
    N_32    height;
    N_8     bytes_per_pixel;
    Canvas *canvas;
    N_32    i;

    if(!read_if_next_byte_array(input, uncompressed, 12))
        return 0;

    width           = read_binary_N_16(input);
    height          = read_binary_N_16(input);
    bytes_per_pixel = read_binary_N_8(input) / 8;

    canvas = create_canvas(width, height, bytes_per_pixel);

    for(i=0; i<width * height * bytes_per_pixel; ++i)
    {
    	canvas->data[i] = input->head;
    	read_byte(input);
    }

    if(bytes_per_pixel == 4)
    {
        for(i=0; i<width * height * bytes_per_pixel; i += bytes_per_pixel)
        {
            swap(&canvas->data[i], &canvas->data[i+3], 1);
            swap(&canvas->data[i+1], &canvas->data[i+2], 1);
        }
    }

    if(bytes_per_pixel == 3 || bytes_per_pixel == 4)
    {
        for(i=0; i<width * height * bytes_per_pixel; i += bytes_per_pixel)
        {
            swap(&canvas->data[i], &canvas->data[i+2], 1);
            swap(&canvas->data[i], &canvas->data[i+1], 1);
        }
    }

    return canvas;
}
