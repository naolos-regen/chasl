//
// Created by nao on 11/12/25.
//

#ifndef CHASL_SERVER_H
#define CHASL_SERVER_H
#include <cstring>
#include "Runnable.h"

class Server final : public Runnable
{
private:
	const int port;
	int sock;
	int client_sock;
	char buffer[1024]{};
	bool running = true;

public:
	explicit Server() : port(8080), sock(-1), client_sock(-1)
	{
		memset(buffer, 0, sizeof(buffer));
	}

	~Server() override = default;
	bool run() override;
	bool shutdown() override;
};

#endif //CHASL_SERVER_H
