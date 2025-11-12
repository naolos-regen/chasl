//
// Created by nao on 11/12/25.
//

#include "../include/Client.h"

int main()
{
	Client client("127.0.0.1", 8080);

	if (!client.run())
	{
		return (1);
	}
	return (0);
}