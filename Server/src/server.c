#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}


int main (int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    int server_socket;
    int client_socket_fs;

    socklen_t client_length;

    // structs that hold port and address of server and client
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;

    // data coming in
    char buffer[256];


    server_socket = socket(AF_INET, SOCK_STREAM, 0); // get a socket from the system
    if (server_socket < 0) {
        error("ERROR opening socket");
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr)); // initialise serv_address to zero
    serv_addr.sin_family = AF_INET; // set the data of the server's address
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    // try to bind the socket into serv_adress we have
    if (bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    listen(server_socket, 5); // listens for requests
    printf("Server listening on port %d\n", port);

    // when we get a connection request on server_socket, try to accept it
    client_length = sizeof(cli_addr);
    client_socket_fs = accept(server_socket, (struct sockaddr *) &cli_addr, &client_length);
    if (client_socket_fs < 0) {
        error("ERROR on accept");
    }

    memset(buffer, 0, 256); // clear the message buffer

    int n = read(client_socket_fs, buffer, 255);
    if (n < 0) {
        error("ERROR reading from socket");
    }
    printf("Here is the message: %s\n", buffer);

    // Send the received message back to the client
    n = write(client_socket_fs, buffer, strlen(buffer));
    if (n < 0) {
        error("ERROR writing to socket");
    }

    close(client_socket_fs);
    close(server_socket);

    return 0;
}

