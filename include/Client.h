//
// Created by nao on 11/12/25.
//

#ifndef CHASL_CLIENT_H
#define CHASL_CLIENT_H

#include <cstring>
#include <string>
#include <utility>

#include "Runnable.h"

class Client final : public Runnable
{
private:
	int sock;
	int port;
	char buffer[1024]{};
	bool running = true;
	std::string server_ip;

public:
	Client(std::string  server_ip, const int port) : sock(-1), port(port), server_ip(std::move(server_ip))
	{
		memset(buffer, 0, sizeof(buffer));
	};
	~Client() override =default;
	bool run() override;
	bool shutdown() override;
};

#endif //CHASL_CLIENT_H
