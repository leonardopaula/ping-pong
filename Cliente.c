#include<sys/types.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<Util.c>
#define SRV_HOST "127.0.0.1"
#define SRV_PORTA 50000

int main()
{
	int isocket, iconector, i, lido, tamanho_mensagem;
	struct sockaddr_in servidor;
	char buffer[2000], resp[3];
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
	tamanho_mensagem = 12;

	for(i=0; i < tamanho_mensagem; i++)
	{
		buffer[i] = 'D';
	}
	buffer[tamanho_mensagem] = '\t';

	printf("Enviando...%s\n", buffer);

	// Enviando
	gettimeofday(&inicio, NULL);
	if (write(isocket, buffer, strlen(buffer)+1) < 0)
	{
		perror("Enviar dados");
		exit(EXIT_FAILURE);
	}

	/* TODO: Receber */
	lido = read(isocket, resp, 3);
	printf("Resp: %s\n", resp);
	gettimeofday(&fim, NULL);

	printf("-> %.06f\n", ((fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) * 1e-6));

	close(isocket);

	return 0;
}
