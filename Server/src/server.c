#include "server.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


void show_menu(int client_socket_fs) {
    send_data_to_client(client_socket_fs, menu);
}

int main (int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    int server_socket = set_up_server_socket();
    set_server_address(port, server_socket);

    listen(server_socket, 5); // listens for requests
    printf("Server listening on port %d\n", port);
    int client_socket_fs = set_client_socket(server_socket);

    show_menu(client_socket_fs);

    navigation_menu(client_socket_fs);

    close(client_socket_fs);
    close(server_socket);

    return 0;
}

