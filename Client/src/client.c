#include "client.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>


int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    int port_number = atoi(argv[2]);

    int client_socket =  set_client_socket();

    set_server_address(client_socket, port_number, server);

    main_navigation(client_socket);

    close(client_socket);
    return 0;
}