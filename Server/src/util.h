#pragma once

void show_error(const char *msg);

int set_up_server_socket();

int set_client_socket(int server_socket);

void set_server_address(int port, int server_socket);

void send_data_to_client(int client_socket_fs, char buffer[]);

void read_client_data(int client_socket_fs, char* buffer, int size);

void navigation_menu(int client_socket_fs);

