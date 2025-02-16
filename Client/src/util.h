#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>

#define MSG_SIZE 4096
#define BUFFER_SIZE 4096

void set_server_address(int client_socket, int port_number, struct hostent *server);

int set_client_socket();

void read_server_data(int client_socket, char* buffer, int size);

void write_to_server();

void write_to_server(int client_socket, char buffer[]);

void main_navigation(int client_socket);
