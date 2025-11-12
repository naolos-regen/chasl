//
// Created by nao on 11/12/25.
//

#include "../include/Server.h"

int main()
{
	Server server{};

	if (!server.run())
	{
		return (1);
	}

	return (0);
}
