#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define BUFFER_SIZE 256
#define HISTORY_SIZE 4096

char menu[] = "Here are the options\n"
                "1. For Echo Mode\n"
                "2. Show System Info\n"
                "3. Show History\n"
                "4. Close Session\n"
                "Please Select an Option";

void show_error(const char *msg) {
    perror(msg);
    exit(1);
}

int set_up_server_socket() {
    int    server_socket = socket(AF_INET, SOCK_STREAM, 0); // get a socket from the system
    if (server_socket < 0) {
        show_error("ERROR opening socket");
    }

    return server_socket;
}

void set_server_address(int port, int server_socket) {
    struct sockaddr_in serv_addr;
    memset((char *) &serv_addr, 0, sizeof(serv_addr)); // initialise serv_address to zero
    serv_addr.sin_family = AF_INET; // set the data of the server's address
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        show_error("ERROR on binding");
    }
}

int set_client_socket(int server_socket) {

    int client_socket_fs;

    struct sockaddr_in cli_addr;

    socklen_t client_length;

    client_length = sizeof(cli_addr);

    client_socket_fs = accept(server_socket, (struct sockaddr *) &cli_addr, &client_length);
    if (client_socket_fs < 0) {
        show_error("ERROR on accept");
    }

    return client_socket_fs;
}

void send_data_to_client(int client_socket_fs, char buffer[]) {
    int n = write(client_socket_fs, buffer, strlen(buffer));
    if (n < 0) {
        show_error("ERROR writing to socket");
    }
}

void read_client_data(int client_socket_fs, char* buffer, int size) {
    int n = read(client_socket_fs, buffer, size);
    if (n < 0) {
        show_error("ERROR reading from socket");
    }
    printf("Here is the message: %s\n", buffer);
}

void get_system_data(char *result, size_t size) {
    FILE *fp;
    fp =  popen("uname -a", "r");
    if (fp == NULL) {
        perror("popen failed");
        return;
    }

    // Read the output into the result buffer
    if (fgets(result, size, fp) == NULL) {
        perror("fgets failed");
    }

    // Close the pipe
    pclose(fp);
}

void update_hsitory(char history[], char buffer[]) {
    strncat(history, buffer, HISTORY_SIZE - strlen(history) - 1);
    strncat(history, "\n", HISTORY_SIZE - strlen(history) - 1);
}

void show_menu(int client_socket_fs) {
    send_data_to_client(client_socket_fs, menu);
}

void navigation_menu(int client_socket_fs, int server_socket) {
    
    char buffer[BUFFER_SIZE];
    char history[HISTORY_SIZE] = {0};

    while (true) {

        show_menu(client_socket_fs);

        memset(buffer, 0, 256);
        read_client_data(client_socket_fs, buffer, BUFFER_SIZE);

        update_hsitory(history, buffer);

        int val = atoi(buffer);
        switch (val) {

            case 1: // Echo Mode
                printf("Echo Mode Selected. Data: %s\n", buffer);
                send_data_to_client(client_socket_fs, "Tell me something");
                read_client_data(client_socket_fs, buffer, BUFFER_SIZE-1);

                update_hsitory(history, buffer);

                send_data_to_client(client_socket_fs, buffer);
                break;

            case 2: // Getting System data
                printf("System Data Selected. Data: %s\n", buffer);
                get_system_data(buffer, BUFFER_SIZE-1);

                update_hsitory(history, buffer);

                send_data_to_client(client_socket_fs, buffer);
                printf("Data is %s\n", buffer);
                break;

            case 3: // Show History
                printf("Showing The History Data: %s\n", history);
                send_data_to_client(client_socket_fs, history);
                break;
            
            case 4: // System Exit
                printf("Closing The system: %s\n", buffer);
                close(client_socket_fs);
                close(server_socket);
                exit(0);
                break;
            default:
                printf("Something went Wrong.\n");
                exit(0);
                break;
        }

    }
}

