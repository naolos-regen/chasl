//
// Created by nao on 11/12/25.
//
#include <iostream>
#include <unistd.h>

#include "../include/Server.h"
#include <arpa/inet.h>

bool Server::run()
{
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock < 0)
	{
		return false;
	}
	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(this->port);

	if (bind(this->sock, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0)
	{
		return false;
	}

	if (listen(this->sock, 3) < 0)
	{
		return false;
	}

	std::cout << "Server listening on port" << this->port << std::endl;

	sockaddr_in client_addr{};
	socklen_t client_len = sizeof(client_addr);
	this->client_sock = accept(this->sock, reinterpret_cast<struct sockaddr*>(&client_addr), &client_len);
	if (this->client_sock < 0)
	{
		return false;
	}

	std::cout << "Client connected\n";

	while (this->running)
	{
		memset(buffer, 0, sizeof(buffer));
		ssize_t bytes_read = read(this->client_sock, buffer, sizeof(buffer));
		if (bytes_read <= 0)
		{
			std::cout << "Client disconnected\n";
			break;
		}
		std::cout << "Client says: " << buffer << std::endl;

		write(this->client_sock, buffer, bytes_read);
	}

	close(this->client_sock);
	close(this->sock);
	return true;
}

bool Server::shutdown()
{
	return (this->running = false);
}
