//
// Created by nao on 11/12/25.
//

#include <iostream>
#include <unistd.h>

#include "../include/Client.h"
#include <arpa/inet.h>

bool Client::run()
{
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock < 0)
	{
		return false;
	}

	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->port);

	if (inet_pton(AF_INET, this->server_ip.c_str(), &server_addr.sin_addr) != 1)
	{
		return false;
	}

	if (connect(this->sock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(sockaddr_in)) != 0)
	{
		return false;
	}

	std::cout << "Connected to Server" << std::endl;

	while (this->running)
	{
		std::cout << "Enter message: " << std::endl;
		std::string msg;
		std::getline(std::cin, msg);

		if (msg == "quit")
		{
			this->shutdown();
			break;
		}

		send(this->sock, msg.c_str(), msg.size(), 0);
		memset(buffer, 0, sizeof(buffer));
		read(sock, buffer, sizeof(buffer));

		std::cout << "Server echoed: " << buffer << std::endl;
	}

	close(this->sock);
	return true;
}

bool Client::shutdown()
{
	return (this->running = false);
}
