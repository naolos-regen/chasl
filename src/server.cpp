//
// Created by nao on 11/12/25.
//

#include "../include/Server.h"

int main()
{
	Server server(8080);

	server.connect_client();
	while (server.is_running())
	{
		server.run();
	}
	return (0);
}
