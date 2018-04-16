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
#define SRV_HOST "69.164.216.30"
#define SRV_PORTA 50000
#define R 0x52

int main()
{
	int size = 50;
	int aux = 0;
	while(aux < 30){
		int isocket, iconector, i, lido;
		struct sockaddr_in servidor;
		char buffer[size], resp[3];
		struct timeval inicio, fim;

		printf("loop: %d\n", size);

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

		for(i=0; i < size; i++)
		{
			buffer[i] = (char) R;
		}
		buffer[size-1] = '\0';

		printf("Enviando...%lu\n", strlen(buffer));

		// Enviando
		gettimeofday(&inicio, NULL);
		if (write(isocket, buffer, strlen(buffer)) < 0)
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
		aux++;
		size = size + 150;
	}
	return 0;
}