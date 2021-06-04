
#ifndef __SOCKET_HEADER__
#define __SOCKET_HEADER__
#define PORT 0xBEEF
#define BUFSIZE 1024
#define FAILURE -1
#define READ_WRITE_LEN 3

// #define SOCKET_DEBUG 1


enum FAILURE_e
{
    SUCCESS = 0,
    CREATE_SOCKET_FAILED = 1,
    SET_SOCKET_OPTIONS_FAILED = 2,
    CONVERT_IP_FAILED = 3,
    BIND_ADDRESS_FAILED = 4,
    CONNECT_FAILED = 5,
    LISTEN_FAILED = 6,
    ACCEPT_FAILED = 7,
    SEND_FAILED = 8,
    RECEIVE_FAILED = 9,
    RECEIVE_TIMEOUT = 10,
    WINSOCK_SETUP_ERROR = 11
};

int socket_create(int *socket_fd)
{
    int result_i = SUCCESS;
    struct sockaddr_in addr_s;
    int length_i = sizeof(addr_s);
    const char sendBuf_c[BUFSIZE] = {0};
    int opt;
    int flag;

    #ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    result_i = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result_i != SUCCESS)
    {
        perror("socket_create winsock setup failed\n");
        result_i = WINSOCK_SETUP_ERROR;
    }
    else
    {
        #ifdef SOCKET_DEBUG
        printf("socket_create winsock setup\n");
        #endif
        result_i = SUCCESS;
    }
    #endif

    // create the client socket
    *socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*socket_fd == 0)
    {
        perror("socket_create socket create failed\n");
        result_i = CREATE_SOCKET_FAILED;
    }
    else
    {
        #ifdef SOCKET_DEBUG
        printf("socket_create socket created\n");
        #endif
        result_i = SUCCESS;
    }
    if (result_i == SUCCESS)
    {
        opt = 1;
        #ifdef __linux__
        result_i = setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        #else
        result_i = setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
        #endif
        #ifdef __linux__
        if (result_i != SUCCESS)
        #elif _WIN32
        if (result_i == SOCKET_ERROR)
        #endif
        {
            perror("socket_create setsockopt failed");
            result_i = SET_SOCKET_OPTIONS_FAILED;
        }
        else
        {
            #ifdef SOCKET_DEBUG
            printf("socket_create setsockopt completed\n");
            #endif
            result_i = SUCCESS;
        }
    }
    return result_i;
}
int socket_send(int socket_fd, unsigned char* buffer, int *length)
{
    int result_i = SUCCESS;
    if (*length >= BUFSIZE)
    {
        *length = (BUFSIZE-1);
    }
    *length = send(socket_fd, (char*)buffer, *length, 0);
    if (*length < SUCCESS)
    {
        perror("socket_send send data failed\n");
        #ifdef __linux__
            close(socket_fd);
        #elif _WIN32
            closesocket(socket_fd);
        #endif
        result_i = SEND_FAILED;
    }
    else
    {
        #ifdef SOCKET_DEBUG
        printf("socket_send sent data: %s (%d bytes)\n", buffer, *length);
        #endif
        result_i = SUCCESS;
    }
    return result_i;
}
int socket_recv(int socket_fd, unsigned char* buffer, int *length)
{
    int readLength_i = -1;
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    fd_set rfds;
    int result_i = 0;
    FD_ZERO(&rfds);
    FD_SET(socket_fd, &rfds);
    result_i = select(socket_fd+1, &rfds, NULL, NULL, &tv);
    if (result_i == 0)
    {
        #ifdef SOCKET_DEBUG
        printf("socket_recv select timeout\n");
        #endif
        result_i = RECEIVE_TIMEOUT;
        *length = -1;
    }
    else if (result_i == -1)
    {
        printf("socket_recv select error\n");
        result_i = RECEIVE_FAILED;
    }
    else
    {
        readLength_i = recv(socket_fd, (char*)buffer, *length, 0);
        if (readLength_i >= *length)
        {
            #ifdef SOCKET_DEBUG
            printf("socket_recv received data: %s (%d bytes)\n", buffer, readLength_i);
            #endif
            *length = readLength_i;
            result_i = SUCCESS;
        }
        else
        {
            printf("socket_recv receive error\n");
            result_i = RECEIVE_FAILED;
        }
    }
    return result_i;
}

int server_connect(int *socket_fd, int port)
{
    int result_i = 0;
    struct sockaddr_in addr_s;
    int opt = 0;
    int flag;

    // create socket
    result_i = socket_create(socket_fd);

    if (result_i == SUCCESS)
    {
        // convert ip string to int
        addr_s.sin_family = AF_INET;
        addr_s.sin_addr.s_addr = INADDR_ANY;
        addr_s.sin_port = htons(port);
        result_i = inet_pton(AF_INET, "127.0.0.1", &addr_s.sin_addr);
        if(result_i != 1)
        {
            perror("server_connect inet_pton error occured\n");
            result_i = CONVERT_IP_FAILED;
        }
        else
        {
            #ifdef SOCKET_DEBUG
            printf("server_connect address converted\n");
            #endif
            result_i = SUCCESS;
        }
    }
    if (result_i == SUCCESS)
    {
        // bind socket to ip & port
        result_i = bind(*socket_fd, (struct sockaddr *)&addr_s, sizeof(addr_s));
        #ifdef __linux__
        if (result_i != SUCCESS)
        #elif _WIN32
        if (result_i == SOCKET_ERROR)
        #endif
        {
            perror("server_connect bind failed");
            result_i = BIND_ADDRESS_FAILED;
        }
        else
        {
            #ifdef SOCKET_DEBUG
            printf("server_connect socket bound to address\n");
            #endif
            result_i = SUCCESS;
        }
    }
    return result_i;
}
int server_listen(int socket_fd)
{
    int result_i = listen(socket_fd, 1);
    #ifdef __linux__
    if (result_i != SUCCESS)
    #elif _WIN32
    if (result_i == SOCKET_ERROR)
    #endif
    {
        perror("server_listen listen failed");
        result_i = LISTEN_FAILED;
    }
    else
    {
        #ifdef SOCKET_DEBUG
        printf("server_listen socket listening\n");
        #endif
        result_i = SUCCESS;
    }
    return result_i;
}
int server_accept(int socket_fd, int *clientSocket_fd, struct sockaddr_in *clientAddr_s)
{
    int result_i = SUCCESS;
    int length_i = 0;
    int flag = 0;
    #ifdef __linux__
    *clientSocket_fd = accept(socket_fd, (struct sockaddr *)clientAddr_s, (socklen_t*)&length_i);
    if (*clientSocket_fd < SUCCESS)
    #else
    *clientSocket_fd = accept(socket_fd, NULL, NULL);
    if (*clientSocket_fd == INVALID_SOCKET)
    #endif
    {
        // perror("server socket accept connection failed");
        result_i = ACCEPT_FAILED;
    }
    else
    {
        result_i = SUCCESS;
        printf("server_accept accepted connection\n");
    }
    if(result_i == SUCCESS)
    {
        // Set non-blocking
        #ifdef __linux__
            flag = fcntl(socket_fd, F_GETFL, NULL);

            if(flag < SUCCESS)
            {
                perror("server_accept fcntl F_GETFL failed");
                result_i = SET_SOCKET_OPTIONS_FAILED;
            }
            else
            {
                flag |= O_NONBLOCK;
                result_i = fcntl(socket_fd, F_SETFL, flag);
                if(result_i < SUCCESS)
                {
                    perror("server_accept fcntl F_SETFL failed");
                    result_i = SET_SOCKET_OPTIONS_FAILED;
                }
                else
                {
                    result_i = SUCCESS;
                    #ifdef SOCKET_DEBUG
                    printf("server_accept fcntl completed\n");
                    #endif
                }
            }
        #elif _WIN32
            flag = 1;
            ioctlsocket(*clientSocket_fd, FIONBIO, (u_long *)&flag);
            if(result_i < SUCCESS)
            {
                perror("server_accept ioctlsocket FIONBIO failed");
                result_i = SET_SOCKET_OPTIONS_FAILED;
            }
            else
            {
                #ifdef SOCKET_DEBUG
                printf("server_accept ioctlsocket completed\n");
                #endif
                result_i = SUCCESS;
            }
        #endif
    }
    return result_i;
}

int client_connect(int *socket_fd, int port)
{
    struct sockaddr_in addr_s;
    int length_i = sizeof(addr_s);
    const char sendBuf_c[BUFSIZE] = {0};
    char recvBuf_c[BUFSIZE];
    int result_i = SUCCESS;
    int opt;
    int flag;

    // create socket
    result_i = socket_create(socket_fd);

    if (result_i == SUCCESS)
    {
        // set up client ip & port
        addr_s.sin_family = AF_INET;
        addr_s.sin_addr.s_addr = htonl(INADDR_ANY);
        addr_s.sin_port = htons(port);
        result_i = inet_pton(AF_INET, "127.0.0.1", &addr_s.sin_addr);
        if(result_i < SUCCESS)
        {
            perror("client_connect inet_pton error occured\n");
            result_i = CONVERT_IP_FAILED;
        }
        else
        {
            #ifdef SOCKET_DEBUG
            printf("client_connect address converted\n");
            #endif
            result_i = SUCCESS;
        }
    }

    if (result_i == SUCCESS)
    {
        // connect to server socket
        result_i = connect(*socket_fd, (sockaddr *)&addr_s, sizeof(addr_s));

        #ifdef __linux__
        if (result_i != SUCCESS)
        #elif _WIN32
        if (result_i == SOCKET_ERROR)
        #endif
        {
            printf("client_connect unable to connect to server\n");
            result_i = CONNECT_FAILED;
        }
        else
        {
            #ifdef SOCKET_DEBUG
            printf("client_connect socket connected\n");
            #endif
            result_i = SUCCESS;
        }
    }
    if(result_i == SUCCESS)
    {
        // Set non-blocking
        #ifdef __linux__
            flag = fcntl(*socket_fd, F_GETFL, NULL);
            if(flag < SUCCESS)
            {
                perror("client_connect error fcntl(F_GETFL)\n");
                result_i = SET_SOCKET_OPTIONS_FAILED;
            }
            else
            {
                flag |= O_NONBLOCK;
                result_i = fcntl(*socket_fd, F_SETFL, flag);
                if(result_i < SUCCESS)
                {
                    perror("client_connect error with fcntl(F_SETFL)\n");
                    result_i = SET_SOCKET_OPTIONS_FAILED;
                }
                else
                {
                    #ifdef SOCKET_DEBUG
                    printf("client_connect socket options set\n");
                    #endif
                    result_i = SUCCESS;
                }
            }
        #elif _WIN32
            flag = 1;
            result_i = ioctlsocket(*socket_fd, FIONBIO, (u_long *)&flag);
        #endif
    }
    return result_i;
}

#endif