#include "util.h"

void set_server_address(int client_socket, int port_number, struct hostent *server) {

    struct sockaddr_in serv_addr;
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *) &serv_addr.sin_addr.s_addr, (char *) server->h_addr_list[0], server->h_length);
    serv_addr.sin_port = htons(port_number);

    // tries to connect to the server
    if (connect(client_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
}

int set_client_socket() {
    int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    return socket_file_descriptor;
}

void read_server_data(int client_socket, char* buffer, int size) {
    int bytes_received = recv(client_socket, buffer, size, 0);
    if (bytes_received == 0) { // Connection closed by the server
        printf("Connection closed by the server.\n");
        exit(0);
    } else if (bytes_received < 0) { // An error occurred
        perror("recv");
        exit(0);
    } else { // All good
        buffer[bytes_received] = '\0';
    }
}

void write_to_server(int client_socket, char buffer[]) {
    int op_result = write(client_socket, buffer, strlen(buffer));
    if (op_result < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}

void main_navigation(int client_socket) {
    char buffer[BUFFER_SIZE];

    while (true) {

        memset(buffer, 0, BUFFER_SIZE); // read data
        read_server_data(client_socket, buffer, BUFFER_SIZE-1);
        printf("%s\n\n", buffer);

        char msg[MSG_SIZE];
        printf("Please Select an option\n\n");
        memset(msg, 0, MSG_SIZE);
        fgets(msg, MSG_SIZE-1, stdin); // get user input

        write_to_server(client_socket, msg); // send data
    }
}

