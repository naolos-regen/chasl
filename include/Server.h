//
// Created by nao on 11/12/25.
//

#ifndef CHASL_SERVER_H
#define CHASL_SERVER_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>


class Server final
{
private:
	const int port;
	const int sock;
	int client_sock;
	sockaddr_in server_address;
	char buffer[1024]{};
	bool running;

public:
	explicit Server(const int port) : port(port), sock(socket(AF_INET, SOCK_STREAM, 0)), client_sock(-1),
									server_address({.sin_family = AF_INET}),
									running(false)
	{
		if (sock < 0)
		{
			printf("socket error\n");
			exit(1);
		}
		this->server_address.sin_addr.s_addr = INADDR_ANY;
		this->server_address.sin_port = htons(this->port);
		if (bind(this->sock, reinterpret_cast<sockaddr*>(&this->server_address), sizeof(this->server_address)) < 0)
		{
			printf("bind error\n");
			exit(1);
		}

		if (listen(this->sock, 1) < 0)
		{
			printf("listen error\n");
			exit(1);
		}
		this->running = true;
		memset(buffer, 0, sizeof(buffer));
	}

	~Server()
	{
		close(this->client_sock);
		close(this->sock);
	};
	void run();
	void shutdown();
	void connect_client();
	[[nodiscard]] bool is_running() const;
};

#endif //CHASL_SERVER_H
