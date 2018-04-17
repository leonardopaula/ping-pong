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
#include"Util.c"
#define SRV_HOST "127.0.0.1"
#define SRV_PORTA 50000
#define MAX_ENVIO 1000000
#define INCREMENTO 500

int envia(const struct sockaddr_in *servidor, char *msg, double *tempo);

int main()
{
	int tamanho_mensagem;
	struct sockaddr_in servidor;
	char *msg;
	double tempo;

	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(SRV_PORTA);
	servidor.sin_addr.s_addr = inet_addr(SRV_HOST);
	bzero(&(servidor.sin_zero), 8);

	printf("Tamanho;Tempo;\n");
	do
	{
		tamanho_mensagem = tamanho_mensagem + INCREMENTO;
		msg  = monta_mensagem(tamanho_mensagem);
		//printf("%s\n", msg);
		envia(&servidor, msg, &tempo);

		printf("%d;%.06f\n", tamanho_mensagem,tempo);	

	} while(tamanho_mensagem < MAX_ENVIO);
	//printf("-> %.06f\n", ((fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) * 1e-6));


	return 0;
}

int envia(const struct sockaddr_in *servidor, char *msg, double *tempo)
{
	int isocket, iconector, tamanho_mensagem, iretorno;
	char *retorno;
	struct timeval tInicio, tFim;

	isocket = socket(AF_INET, SOCK_STREAM, 0);
	if (isocket < 0)
	{
	  	perror("Socket");
		exit(EXIT_FAILURE);
	}

	iconector = connect(isocket, (struct sockaddr *)servidor, sizeof(*servidor));
	if (iconector < 0)
	{
		perror("Ao conectar");
		exit(EXIT_FAILURE);
	}

	*(tempo) = 0;

	gettimeofday(&tInicio, NULL);
	iretorno = tcp_envia(isocket, msg);
	free(msg);

	retorno = tcp_recebe(isocket, &tamanho_mensagem);
	gettimeofday(&tFim, NULL);

	if (retorno != NULL)
	{
		*(tempo) = (tFim.tv_sec - tInicio.tv_sec) + (tFim.tv_usec - tInicio.tv_usec) * 1e-6;
		free(retorno);
	}

	close(isocket);

	return 0;
}
