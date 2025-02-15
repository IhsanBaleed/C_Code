#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    
    int socket_file_descriptor;
    int port_number;
    int op_result;

    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    port_number = atoi(argv[2]);
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *) &serv_addr.sin_addr.s_addr, (char *) server->h_addr_list[0], server->h_length);
    serv_addr.sin_port = htons(port_number);

    // tries to connect to the server
    if (connect(socket_file_descriptor, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    printf("Please enter the message: ");
    memset(buffer, 0, 256);
    fgets(buffer, 255, stdin); // get user input

    // try writing to the socket
    op_result = write(socket_file_descriptor, buffer, strlen(buffer));
    if (op_result < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    memset(buffer, 0, 256); // clear the buffer

    // read the result
    op_result = read(socket_file_descriptor, buffer, 255);
    if (op_result < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    printf("%s\n", buffer);
    close(socket_file_descriptor);
    return 0;
}