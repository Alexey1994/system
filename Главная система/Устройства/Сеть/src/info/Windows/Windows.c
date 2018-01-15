/*static WSADATA *wsa_data = 0;


static int get_host_name(char *name, int name_length)
{
    if(!wsa_data)
    {
        wsa_data = new(WSADATA);
        WSAStartup(MAKEWORD(2, 2), wsa_data);
    }

    return gethostname(name, name_length);
}


static int get_address_info(char *node_name, char *service_name, struct addrinfo *hints, struct addrinfo **result)
{
    static int (*get_address_info)(char             *node_name,
                                   char             *service_name,
                                   struct addrinfo  *hints,
                                   struct addrinfo **result) = 0;

    if(!get_address_info)
        get_address_info = open_system_function("ws2_32.dll", "getaddrinfo");

    return get_address_info(node_name, service_name, hints, result);
}


void get_IPv4_host_address(char *host)
{
    struct addrinfo     *result;
    char                *computer_name[256];
    struct sockaddr_in  *sockaddr_ipv4;

    struct addrinfo *i     = 0;
    struct addrinfo  hints = {0};

    get_host_name(computer_name, 256);

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    get_address_info(computer_name, "80", &hints, &result);

    for(i = result; i; i = i->ai_next)
    {
        if(i->ai_family == AF_INET)
        {
            sockaddr_ipv4 = (struct sockaddr_in *) i->ai_addr;
            snprintf(host, 16, "%s", inet_ntoa(sockaddr_ipv4->sin_addr));
            return;
        }
    }
}
*/
