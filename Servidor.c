#include<stdio.h>
#include<sys/socket.h>
#include<assert.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include "Util.c"
#define PORTA 50000

int main(int argc, char const *argv[])
{
	int desc_socket, desc_cliente, lido, enviado;
	int habilita = 1;
	struct sockaddr_in endereco, cliente;
	char *rec_msg;
	char resp[] = "OK\t";


	desc_socket = socket(AF_INET, // IPv4
						 SOCK_STREAM, // TCP ou SOCK_DGRAM = UDP
						 0 // Procolor específico
						);

	if (desc_socket == 0)
	{
		perror("Socket - Descritor do servidor");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(desc_socket, // Qual socket
				   SOL_SOCKET, // Define a API (nível da pilha)
				   SO_REUSEADDR | SO_REUSEPORT, // Permite reutilizar a porta (Address already in use)
				   &habilita, // Passa por referência para valor 1 (habilita)
				   sizeof(habilita)))
	{
		perror("Setando opcao");
		exit(EXIT_FAILURE);
	}

	endereco.sin_family = AF_INET;
	endereco.sin_addr.s_addr = INADDR_ANY;
	endereco.sin_port = htons(PORTA);

	// Atribuí o endereço
	if (bind(desc_socket // Descritor do socket
		    ,(struct sockaddr *)&endereco // Pega de rede presente na struct
		    ,sizeof(endereco)) < 0)
	{
		perror("Erro endereco");
		exit(EXIT_FAILURE);
	}

	// Escutar no máximo 3!
	if (listen(desc_socket, 3))
	{
		perror("Ao ouvir");
		exit(EXIT_FAILURE);
	}

	printf("Escutando...");
	// Frita
	while(1)
	{

		if ((desc_cliente = accept(desc_socket, // descritor do socket
								  (struct sockaddr *) &cliente,
							  	  (socklen_t*)&cliente)) < 0)
		{
			perror("Aceita");
			exit(EXIT_FAILURE);
		}

		printf("Conectou...");

		rec_msg = tcp_recebe(desc_cliente, &lido);
		printf("Recebido: %d\n", lido);

		// Responde
		enviado = tcp_envia(desc_cliente, resp);

		free(rec_msg);

		close(desc_cliente);
	}


	return 0;
}
