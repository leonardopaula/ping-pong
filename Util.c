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
			printf("Sim: %s\n", buffer);
			break;
		} else {
			printf("Nop: %s\n", buffer);
		}

	}
	*(lido) = iOffset;

	if (iOffset == 0)
	{
		free(buffer);
		return NULL;
	}


	printf("Data: %s\n", buffer);

	return buffer;
}

//char *tcp_envia(int socket, )
