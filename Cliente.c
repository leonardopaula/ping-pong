#include<sys/types.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define SRV_HOST "127.0.0.1"
#define SRV_PORTA 50000
#define R 0x52

int main()
{
	int isocket, iconector, i;
	struct sockaddr_in servidor;
	char buffer[2000];
	struct timeval inicio, fim;

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
	bzero(buffer, sizeof(buffer));

	for(i=0; i < 1024; i++)
	{
		buffer[i] = (char *) R;
	}
	buffer[1024-1] = '\0';

	printf("Enviando...%d\n", strlen(buffer));

	// Enviando
	gettimeofday(&inicio, NULL);
	if (write(isocket, buffer, strlen(buffer)) < 0)
	{
		perror("Enviar dados");
		exit(EXIT_FAILURE);
	}

	/* TODO: Receber */
	

	close(isocket);

	return 0;
}