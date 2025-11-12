#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
                printf("Socket creation failed");
                return (1);
        }

        struct sockaddr_in server_addr = {0};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(8080);

        if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) != 1)
        {
                printf("Invalid IP\n");
                return (1);
        }

        if (connect (sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) != 0)
        {
                printf("Connection failed\n");
                return (1);
        }

        printf("Connected to Server\n");

        char *line = NULL;
        size_t size = 0;
        ssize_t line_length;

        while (1)
        {
                printf("Enter Message: ");
                line_length = getline(&line, &size, stdin);

                if (line_length == -1)
                {
                        printf("Error reading line\n");
                        break;
                }

                if (line[line_length -1] == '\n')
                {
                        line[line_length - 1] = '\0';
                        line_length--;
                }

                if (strcmp(line, "exit") == 0)
                {
                        break;
                }

                if (send(sock, line, line_length, 0) == -1)
                {
                        printf("Send failed");
                        break;
                }

                char buffer[1024] = {0};
                ssize_t recv_len = read(sock, buffer, sizeof(buffer) - 1);
                if (recv_len > 0)
                {
                        printf("Server Echoed: %s\n", buffer);
                }
                else 
                {
                        printf("Recieve failed");
                        break;
                }
        }

        free(line);
        close(sock);
        return (0);
}
