//
// Created by nao on 11/12/25.
//
#include <iostream>
#include <unistd.h>

#include "../include/Server.h"
#include <arpa/inet.h>

void Server::connect_client()
{
	sockaddr_in client_addr{};
	socklen_t client_addr_len = sizeof(client_addr);
	this->client_sock = accept(this->sock, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addr_len);
	if (this->client_sock < 0)
	{
		printf("accept failed\n");
	}
	printf("Client connected\n");
}

void Server::run()
{
	memset(buffer, 0, sizeof(buffer));
	const ssize_t bytes_read = read(this->client_sock, buffer, sizeof(buffer));
	if (bytes_read <= 0)
	{
		std::cout << "Client disconnected\n";
		this->shutdown();
	}
	std::cout << "Client says: " << buffer << std::endl;
	write(this->client_sock, buffer, bytes_read);
}

void Server::shutdown()
{
	(this->running = false);
}

bool Server::is_running() const
{
	return this->running;
}
