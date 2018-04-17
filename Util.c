#define TAM_BUFFER 10

char *tcp_recebe(int socket, int *lido)
{
	unsigned long long int  tamanhoBuffer;
	int recebido;
	char *buffer;
	char *temporario;
	int  iOffset;

	tamanhoBuffer = TAM_BUFFER;
	*(lido) = 0;
	iOffset = 0;
	buffer = malloc(sizeof(char) * (tamanhoBuffer + 1));
	memset(buffer, 0, sizeof(char) * (tamanhoBuffer + 1)); // Limpa variável

	while((recebido = recv(socket, &buffer[iOffset], (tamanhoBuffer - iOffset), 0)) > 0)
	{
		iOffset += recebido;
		if (iOffset == tamanhoBuffer) // Pacote cheio
		{
			tamanhoBuffer *= TAM_BUFFER;
			temporario = malloc(sizeof(char) * (tamanhoBuffer + 1));
			memset(temporario, 0, sizeof(char) * (tamanhoBuffer + 1));
			memcpy(temporario, buffer, iOffset);
			free(buffer);
			buffer = temporario;
		}

		if (strstr(buffer, "\t\0") != NULL)
		{
			buffer[--iOffset] = '\0';
			break;
		}

	}
	*(lido) = iOffset;

	if (iOffset == 0)
	{
		free(buffer);
		return NULL;
	}


	//printf("Data: %s\n", buffer);

	return buffer;
}

char *monta_mensagem(int tamanho_mensagem)
{
	int i;
	struct timeval inicio, fim;
	char *msg;

	msg = malloc(sizeof(char) * (tamanho_mensagem + 1));
	memset(msg, 0, sizeof(msg));

	// printf("%d\n", tamanho_mensagem);
	// Popula mensagem
	for(i=0; i < tamanho_mensagem; i++)
	{
		msg[i] = 'D';
	}
	msg[tamanho_mensagem-1] = '\t';

	//printf("msg: %s\n", msg);

	return msg;
}


int tcp_envia(int socket, char *buffer)
{

	//printf("Enviando...%s\n", buffer);

	// Enviando
	//gettimeofday(&inicio, NULL);
	if (write(socket, buffer, strlen(buffer)+1) < 0)
	{
		perror("Enviar dados");
		exit(EXIT_FAILURE);
	}

	return 0;
}
