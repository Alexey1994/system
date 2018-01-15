#include <windows.h>
#include <output/output.h>
#include "cryptography.h"


void print_hash(Byte *hash)
{
    N_32 i;

    for(i=0; i<20; ++i)
        if(hash[i] > 0x0f)
            printf("%x", hash[i]);
        else
            printf("0%x", hash[i]);

    printf("\n");
}


void print_SHA_256_hash(Byte *hash)
{
    N_32 i;

    for(i=0; i<32; ++i)
        if(hash[i] > 0x0f)
            printf("%x", hash[i]);
        else
            printf("0%x", hash[i]);

    printf("\n");
}


Boolean hashes_equals(Byte *hash_1, Byte *hash_2)
{
    N_32 i;

    for(i=0; i<20; ++i)
        if(hash_1[i] != hash_2[i])
            return 0;

    return 1;
}


Boolean SHA_256_hashes_equals(Byte *hash_1, Byte *hash_2)
{
    N_32 i;

    for(i=0; i<32; ++i)
        if(hash_1[i] != hash_2[i])
            return 0;

    return 1;
}


procedure test_SHA_1()
{

    N_32 hashes[6][5] = {
        {0xa9993e36, 0x4706816a, 0xba3e2571, 0x7850c26c, 0x9cd0d89d},
        {0xda39a3ee, 0x5e6b4b0d, 0x3255bfef, 0x95601890, 0xafd80709},
        {0x84983e44, 0x1c3bd26e, 0xbaae4aa1, 0xf95129e5, 0xe54670f1},
        {0xa49b2446, 0xa02c645b, 0xf419f995, 0xb6709125, 0x3a04a259},
        {0x34aa973c, 0xd4c4daa4, 0xf61eeb2b, 0xdbad2731, 0x6534016f},
        {0x7789f0c9, 0xef7bfc40, 0xd9331114, 0x3dfbe69e, 0x2017f592}
    };

    N_32 i;
    N_32 j;

    Byte   hash[20];
    Buffer data[6];
    Output data_output;

    for(i=0; i<6; ++i)
        initialize_buffer(&data[i], 1);

    for(i=0; i<6; ++i)
        for(j=0; j<5; ++j)
            convert_big_to_little_endian(&hashes[i][j], 4);


    initialize_buffer_output(&data[0], &data_output);
    write_null_terminated_byte_array(&data_output, "abc");
    calculate_SHA_1_hash(&data[0], hash);

    if(!hashes_equals(hash, &hashes[0]))
        printf("test 1 faild\n");
    else
        printf("test 1 Ok\n");

/*
    initialize_buffer_output(&data[1], &data_output);
    write_null_terminated_byte_array(&data_output, "");
    calculate_SHA_1_hash(&data[1], hash);

    if(!hashes_equals(hash, &hashes[1]))
        printf("test 2 faild\n");
    else
        printf("test 2 Ok\n");


    initialize_buffer_output(&data[2], &data_output);
    write_null_terminated_byte_array(&data_output, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    calculate_SHA_1_hash(&data[2], hash);

    if(!hashes_equals(hash, &hashes[2]))
        printf("test 3 faild\n");
    else
        printf("test 3 Ok\n");


    initialize_buffer_output(&data[3], &data_output);
    write_null_terminated_byte_array(&data_output, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu");
    calculate_SHA_1_hash(&data[3], hash);

    if(!hashes_equals(hash, &hashes[3]))
    {
        printf("test 4 faild\n");
        print_hash(hash);
        print_hash(&hashes[3]);
    }
    else
        printf("test 4 Ok\n");


    initialize_buffer_output(&data[4], &data_output);

    for(i=0; i<1000000; ++i)
        write_byte(&data_output, 'a');

    calculate_SHA_1_hash(&data[4], hash);

    if(!hashes_equals(hash, &hashes[4]))
    {
        printf("test 5 faild\n");
        print_hash(hash);
        print_hash(&hashes[4]);
    }
    else
        printf("test 5 Ok\n");


    initialize_buffer(&data[5], 17777216 * strlen("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno"));
    initialize_buffer_output(&data[5], &data_output);

    for(i=0; i<16777216; ++i)
        write_null_terminated_byte_array(&data_output, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno");

    calculate_SHA_1_hash(&data[5], hash);

    if(!hashes_equals(hash, &hashes[5]))
    {
        printf("test 6 faild\n");
        print_hash(hash);
        print_hash(&hashes[5]);
    }
    else
        printf("test 6 Ok\n");*/
}


procedure test_SHA_256()
{
    N_32 hashes[6][8] = {
        {0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad},
        {0xe3b0c442, 0x98fc1c14, 0x9afbf4c8, 0x996fb924, 0x27ae41e4, 0x649b934c, 0xa495991b, 0x7852b855},
        {0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1},
        {0xcf5b16a7, 0x78af8380, 0x036ce59e, 0x7b049237, 0x0b249b11, 0xe8f07a51, 0xafac4503, 0x7afee9d1},
        {0xcdc76e5c, 0x9914fb92, 0x81a1c7e2, 0x84d73e67, 0xf1809a48, 0xa497200e, 0x046d39cc, 0xc7112cd0},
        {0x50e72a0e, 0x26442fe2, 0x552dc393, 0x8ac58658, 0x228c0cbf, 0xb1d2ca87, 0x2ae43526, 0x6fcd055e}
    };

    N_32 i;
    N_32 j;

    Byte   hash[32];
    Buffer data[6];
    Output data_output;

    for(i=0; i<6; ++i)
        initialize_buffer(&data[i], 1);

    for(i=0; i<6; ++i)
        for(j=0; j<8; ++j)
            convert_big_to_little_endian(&hashes[i][j], 4);


    initialize_buffer_output(&data[0], &data_output);
    write_null_terminated_byte_array(&data_output, "abc");
    calculate_SHA_256_hash(&data[0], hash);

    if(!SHA_256_hashes_equals(hash, &hashes[0]))
        printf("test 1 faild\n");
    else
        printf("test 1 Ok\n");


    initialize_buffer_output(&data[1], &data_output);
    write_null_terminated_byte_array(&data_output, "");
    calculate_SHA_256_hash(&data[1], hash);

    if(!SHA_256_hashes_equals(hash, &hashes[1]))
        printf("test 2 faild\n");
    else
        printf("test 2 Ok\n");


    initialize_buffer_output(&data[2], &data_output);
    write_null_terminated_byte_array(&data_output, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    calculate_SHA_256_hash(&data[2], hash);

    if(!SHA_256_hashes_equals(hash, &hashes[2]))
        printf("test 3 faild\n");
    else
        printf("test 3 Ok\n");


    initialize_buffer_output(&data[3], &data_output);
    write_null_terminated_byte_array(&data_output, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu");
    calculate_SHA_256_hash(&data[3], hash);

    if(!SHA_256_hashes_equals(hash, &hashes[3]))
        printf("test 4 faild\n");
    else
        printf("test 4 Ok\n");


    initialize_buffer_output(&data[4], &data_output);

    for(i=0; i<1000000; ++i)
        write_byte(&data_output, 'a');

    calculate_SHA_256_hash(&data[4], hash);

    if(!SHA_256_hashes_equals(hash, &hashes[4]))
        printf("test 5 faild\n");
    else
        printf("test 5 Ok\n");


    initialize_buffer(&data[5], 17777216 * strlen("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno"));
    initialize_buffer_output(&data[5], &data_output);

    for(i=0; i<16777216; ++i)
        write_null_terminated_byte_array(&data_output, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno");

    calculate_SHA_256_hash(&data[5], hash);

    if(!SHA_256_hashes_equals(hash, &hashes[5]))
        printf("test 6 faild\n");
    else
        printf("test 6 Ok\n");
}


Boolean is_true_SHA_256_hash(Byte *SHA_256_hash)
{
    N_32 i;

    //for(i=0; i<9; ++i)
    for(i=0; i<3; ++i)
        if(SHA_256_hash[i])
            return 0;

    //if(SHA_256_hash[i] & 0b11110000)
    //    return 0;

    return 1;
}


void add(Buffer *data)
{
    N_32 i;

    i = 0;

    while(data->data[i] == 255)
    {
        data->data[i] = 0;
        ++i;
    }

    if(i == buffer_length(data))
        write_in_buffer(data, 0);
    else
        ++data->data[i];
}


void mining_test()
{
    Buffer data;
    Byte   hash[32];
    N_64   i;

    initialize_buffer(&data, 1);
    write_in_buffer(&data, 0);

    i = 0;

    loop
    {
        calculate_SHA_256_hash(&data, hash);
/*
        if(!((i+1) % 1000000))
        {
            printf("\n\n%ld hashes\n\n", i);
            break;
        }*/

        if(is_true_SHA_256_hash(hash))
        {
            printf("hash: ");
            print_SHA_256_hash(hash);

            printf("data:\n");

            for(i=0; i<buffer_length(&data); ++i)
                if(data.data[i] > 0x0f)
                    printf("%x", data.data[i]);
                else
                    printf("0%x", data.data[i]);

            printf("\n\n");
            break;
        }

        add(&data);
        ++i;
    }
}


int main()
{
    //printf("%d\n", C(3, 0));
    /*Buffer data;
    Output data_output;
    Byte   hash[20];

    initialize_buffer(&data, 1);
    initialize_buffer_output(&data, &data_output);

    write_null_terminated_byte_array(&data_output, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    //write_byte(&data_output, 'a');
    //write_byte(&data_output, 'b');
    //write_byte(&data_output, 'c');

    calculate_SHA_1_hash(&data, hash);
    print_hash(hash);*/

    //test_SHA_1();
    //test_SHA_256();
    mining_test();

    return 0;
}

