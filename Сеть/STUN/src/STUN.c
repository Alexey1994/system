#include "STUN.h"
#include <libs/data structures/string/string.h>

#include "attributes/MAPPED_ADDRESS.h"
#include "attributes/RESPONSE_ADDRESS.h"
#include "attributes/CHANGE_REQUEST.h"
#include "attributes/SOURCE_ADDRESS.h"
#include "attributes/CHANGED_ADDRESS.h"
#include "attributes/USERNAME.h"
#include "attributes/PASSWORD.h"
#include "attributes/MESSAGE_INTEGRITY.h"
#include "attributes/ERROR_CODE.h"
#include "attributes/UNKNOWN_ATTRIBUTES.h"
#include "attributes/REFLECTED_FROM.h"
#include "attributes/REALM.h"
#include "attributes/NONCE.h"
#include "attributes/XOR_MAPPED_ADDRESS.h"
#include "attributes/SOFTWARE.h"
#include "attributes/ALTERNATE_SERVER.h"
#include "attributes/FINGERPRINT.h"


static void(*print_attribute_handlers[65536])(Byte *attribute, int attribute_length);
static void(*read_attribute_handlers[65536])(STUN_Attributes *attributes, Byte *attribute, int attribute_length);


void initialize_STUN()
{
    int i;

    for(i=0; i<65536; ++i)
    {
        print_attribute_handlers[i] = 0;
        read_attribute_handlers[i] = 0;
    }

    print_attribute_handlers[MAPPED_ADDRESS]     = print_MAPPED_ADDRESS_attribute;
    print_attribute_handlers[RESPONSE_ADDRESS]   = print_RESPONSE_ADDRESS_attribute;
    print_attribute_handlers[CHANGE_REQUEST]     = print_CHANGE_REQUEST_attribute;
    print_attribute_handlers[SOURCE_ADDRESS]     = print_SOURCE_ADDRESS_attribute;
    print_attribute_handlers[CHANGED_ADDRESS]    = print_CHANGED_ADDRESS_attribute;
    print_attribute_handlers[USERNAME]           = print_USERNAME_attribute;
    print_attribute_handlers[PASSWORD]           = print_PASSWORD_attribute;
    print_attribute_handlers[MESSAGE_INTEGRITY]  = print_MESSAGE_INTEGRITY_attribute;
    print_attribute_handlers[ERROR_CODE]         = print_ERROR_CODE_attribute;
    print_attribute_handlers[UNKNOWN_ATTRIBUTES] = print_UNKNOWN_ATTRIBUTES_attribute;
    print_attribute_handlers[REFLECTED_FROM]     = print_REFLECTED_FROM_attribute;
    print_attribute_handlers[REALM]              = print_REALM_attribute;
    print_attribute_handlers[NONCE]              = print_NONCE_attribute;
    print_attribute_handlers[XOR_MAPPED_ADDRESS] = print_XOR_MAPPED_ADDRESS_attribute;
    print_attribute_handlers[SOFTWARE]           = print_SOFTWARE_attribute;
    print_attribute_handlers[ALTERNATE_SERVER]   = print_ALTERNATE_SERVER_attribute;
    print_attribute_handlers[FINGERPRINT]        = print_FINGERPRINT_attribute;


    read_attribute_handlers[MAPPED_ADDRESS]     = read_MAPPED_ADDRESS_attribute;
    read_attribute_handlers[RESPONSE_ADDRESS]   = read_RESPONSE_ADDRESS_attribute;
    read_attribute_handlers[CHANGE_REQUEST]     = read_CHANGE_REQUEST_attribute;
    read_attribute_handlers[SOURCE_ADDRESS]     = read_SOURCE_ADDRESS_attribute;
    read_attribute_handlers[CHANGED_ADDRESS]    = read_CHANGED_ADDRESS_attribute;
    read_attribute_handlers[USERNAME]           = read_USERNAME_attribute;
    read_attribute_handlers[PASSWORD]           = read_PASSWORD_attribute;
    read_attribute_handlers[MESSAGE_INTEGRITY]  = read_MESSAGE_INTEGRITY_attribute;
    read_attribute_handlers[ERROR_CODE]         = read_ERROR_CODE_attribute;
    read_attribute_handlers[UNKNOWN_ATTRIBUTES] = read_UNKNOWN_ATTRIBUTES_attribute;
    read_attribute_handlers[REFLECTED_FROM]     = read_REFLECTED_FROM_attribute;
    read_attribute_handlers[REALM]              = read_REALM_attribute;
    read_attribute_handlers[NONCE]              = read_NONCE_attribute;
    read_attribute_handlers[XOR_MAPPED_ADDRESS] = read_XOR_MAPPED_ADDRESS_attribute;
    read_attribute_handlers[SOFTWARE]           = read_SOFTWARE_attribute;
    read_attribute_handlers[ALTERNATE_SERVER]   = read_ALTERNATE_SERVER_attribute;
    read_attribute_handlers[FINGERPRINT]        = read_FINGERPRINT_attribute;
}


void destroy_attributes(STUN_Attributes *attributes)
{
    free(attributes->MAPPRED_ADDRESS.host);
    free(attributes);
}


static void print_attribute(STUN_Attribute *attribute)
{
    void(*attribute_handler)(Byte *attribute, int attribute_length);

    attribute_handler = print_attribute_handlers[ attribute->type ];

    if(!attribute_handler)
    {
        printf("\tunknow attribute 0x%02x, %d bytes\n\n", attribute->type, attribute->length);
        return;
    }

    attribute_handler((Byte*)attribute + 4, attribute->length);
    printf("\n");
}


static void print_attributes(String *message)
{
    int             length     = 20;
    Byte           *attributes = message->begin + 20;
    STUN_Attribute *attribute  = attributes;

    printf("\n\tAttributes:\n\n");

    while(length < message->length)
    {
        convert_big_to_little_endian(&attribute->type, 2);
        convert_big_to_little_endian(&attribute->length, 2);
        print_attribute(attribute);
        length += 4 + attribute->length;
        attribute = (Byte*)attribute + 4 + attribute->length;
    }
}


static void read_attribute(STUN_Attribute *attribute, STUN_Attributes *attributes)
{
    void(*attribute_handler)(STUN_Attributes *attributes, Byte *attribute, int attribute_length);

    attribute_handler = read_attribute_handlers[ attribute->type ];

    if(!attribute_handler)
        return;

    attribute_handler(attributes, (Byte*)attribute + 4, attribute->length);
    printf("\n");
}


static void read_attributes(STUN_Attributes *attributes, String *message)
{
    int             length     = 20;
    STUN_Attribute *attribute  = message->begin + 20;

    printf("\n\tAttributes:\n\n");

    while(length < message->length)
    {
        convert_big_to_little_endian(&attribute->type, 2);
        convert_big_to_little_endian(&attribute->length, 2);
        read_attribute(attribute, attributes);
        length += 4 + attribute->length;
        attribute = (Byte*)attribute + 4 + attribute->length;
    }
}


static void print_header(STUN_Header *header)
{
    printf("Type:            ");

    switch(header->message_type)
    {
        case BINDING_REQUEST:        printf("REQUEST\n");               break;
        case BINDING_RESPONSE:       printf("SERVER RESPONSE\n");       break;
        case BINDING_ERROR_RESPONSE: printf("SERVER RESPONSE ERROR\n"); break;
    }

    printf("Length:          %d\n", header->message_length);

    printf("magic:           0x%04x\n", header->magic_cookie);

    printf("transaction ID:  0x%01x", header->transaction_ID[0]);
    printf("%01x", header->transaction_ID[1]);
    printf("%01x", header->transaction_ID[2]);
    printf("%01x", header->transaction_ID[3]);
    printf("%01x", header->transaction_ID[4]);
    printf("%01x", header->transaction_ID[5]);
    printf("%01x", header->transaction_ID[6]);
    printf("%01x", header->transaction_ID[7]);
    printf("%01x", header->transaction_ID[8]);
    printf("%01x", header->transaction_ID[9]);
    printf("%01x", header->transaction_ID[10]);
    printf("%01x\n", header->transaction_ID[11]);
}


static void generate_transaction_ID(Byte *transaction_ID)
{
    memset(transaction_ID, 0, 12);
}


static void add_request_header(String *message)
{
    STUN_Header *header      =  message->begin;

    header->message_type   = BINDING_REQUEST;
    header->message_length = 0;
    header->magic_cookie   = STUN_COOKIE;
    generate_transaction_ID(header->transaction_ID);

    message->length = 20;
}


static void request(NetworkConnection connection, String *message)
{
    printf("Request\n\n");
    print_header(message->begin);
    printf("\n");

    open_network_connection(connection, message->begin, 20);
}


static String* response(NetworkConnection connection, STUN_Attributes *attributes)
{
    STUN_Header *header;

    String      *message = create_string(200);

    get_network_connection_array(connection, message->begin, 200);

    header = message->begin;
    convert_big_to_little_endian(&header->message_length, 2);
    message->length = 20 + header->message_length;

    printf("Response\n\n");
    print_header(header);
    //print_attributes(message);
    read_attributes(attributes, message);
    printf("\n");
}


STUN_Attributes* STUN_request(char *host, int port)
{
    STUN_Attributes   *attributes  =  new(STUN_Attributes);
    NetworkConnection  connection  =  create_UDP_connection(host, port);
    String            *message     =  create_string(200);

    add_request_header(message);

    request(connection, message);
    response(connection, attributes);

    return attributes;
}


void get_STUN_MAPPED_ADDRESS(char *STUN_host, unsigned short STUN_port, char *mapped_host, unsigned short *mapped_port)
{
    STUN_Attributes *attributes = STUN_request(STUN_host, STUN_port);

    snprintf(mapped_host, 16, "%s", attributes->MAPPRED_ADDRESS.host);
    *mapped_port = attributes->MAPPRED_ADDRESS.port;

    destroy_attributes(attributes);
}


NetworkConnection connect_to_STUN_MAPPED_ADDRESS(char *STUN_host, int STUN_port)
{
    STUN_Attributes   *attributes = STUN_request(STUN_host, STUN_port);
    NetworkConnection  connection = create_UDP_connection(attributes->MAPPRED_ADDRESS.host, attributes->MAPPRED_ADDRESS.port);

    destroy_attributes(attributes);

    return connection;
}
