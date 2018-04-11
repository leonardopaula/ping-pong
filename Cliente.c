#include<stdio.h>
#include<sys/socket.h>
#include<assert.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define SRV_HOST "127.0.0.1"
#define SRV_PORTA 50000
#define R 0x52

main()
{
	int isocket, iconector;
	struct sockaddr_in servidor;
	char *buffer;

	isocket = socket(AF_INET, SOCK_STREAM, 0);
	if (isocket < 0)
	{
		perror("Socket");
		exit(EXIT_FAILURE);
	}

	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(SRV_PORTA);
	servidor.sin_addr.s_addr = inet_addr(SRV_HOST);
	bzero(&(servidor.sin_zero), 8);

	iconector = connect(isocket, (struct sockaddr *)&servidor, sizeof(servidor));
	if (iconector < 0)
	{
		perror("Ao conectar");
		exit(EXIT_FAILURE);
	}

	/* Conexão estabelecida */



}