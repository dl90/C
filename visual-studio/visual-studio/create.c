#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned int accountNumber;
	char firstName[20];
	char lastName[20];
	double accountBalance;
	double lastPaymentAMount;
} ClientData;

void readParse(FILE*, ClientData*);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Need 2 arguments: <Input filename> <output filename>\n");
		exit(EXIT_FAILURE);
	}

	FILE* readFPtr;
	FILE* writeFPtr;

	readFPtr = fopen(argv[1], "r");
	if (readFPtr == NULL)
	{
		printf("Error %s could not be found\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	writeFPtr = fopen(argv[2], "r");
	if (writeFPtr != NULL)
	{
		printf("\n%s already exists, it will be overwritten\n", argv[2]);
		printf("Do you want to continue? (y/n): ");

		char answer;
		scanf("%c", &answer);
		if (answer == 'n')
		{
			fclose(readFPtr);
			fclose(writeFPtr);

			printf("\nGoodbye\n");
			exit(EXIT_SUCCESS);
		}
	}

	writeFPtr = fopen(argv[2], "wb");
	if (writeFPtr == NULL)
	{
		printf("Error opening file %s\n", argv[2]);
		fclose(readFPtr);
		exit(EXIT_FAILURE);
	}

	ClientData client = { 0, "", "", 0.0, 0.0 };
	readParse(readFPtr, &client);

	while (!feof(readFPtr))
	{
		fwrite(&client, sizeof(ClientData), 1, writeFPtr);
		readParse(readFPtr, &client);
	}

	fclose(readFPtr);
	fclose(writeFPtr);

	puts("\nFile written\n");
	atexit(_getch);
	return 0;
}

void readParse(FILE* readFPtr, ClientData* client)
{
	char strBuffer[100];
	if (fgets(strBuffer, sizeof(strBuffer), readFPtr) != NULL)
	{
		char* token = strtok(strBuffer, " ,");

		client->accountNumber = strtod(token, NULL);
		token = strtok(NULL, " ,");

		strcpy(client->firstName, token);
		token = strtok(NULL, " ,");

		strcpy(client->lastName, token);
		token = strtok(NULL, " ,");

		client->accountBalance = strtod(token, NULL);
		token = strtok(NULL, " ,");

		client->lastPaymentAMount = strtod(token, NULL);
	}

}
