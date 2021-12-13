#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "assign08.h"

#define DATA_FORMAT_STRING "%-14d %-13s %-11s %-17.2f %-23.2f\n"

static const char* DAT_FILE;
static const char* INDEX_FILE;

int main(int argc, char* argv[])
{
	atexit(_getch);

	if (argc != 3)
	{
		printf("Need 2 arguments: <Data filename> <Index filename>\n");
		exit(EXIT_FAILURE);
	}
	DAT_FILE = argv[1];
	INDEX_FILE = argv[2];
	void (*listDataFuncPtr[2])(FILE*, FILE*) = {
		naturalOrder,
		accountBalanceDecending
	};

	FILE* datFPtr = fopen(DAT_FILE, "rb");
	if (datFPtr == NULL)
	{
		printf("Error: could not locate/open %s\n", DAT_FILE);
		exit(EXIT_FAILURE);
	}

	FILE* idxFPtr = fopen(INDEX_FILE, "rb");
	if (idxFPtr == NULL)
	{
		printf("Error: could not locate/open %s\n", INDEX_FILE);
		fclose(datFPtr);
		exit(EXIT_FAILURE);
	}

	int op;
	while ((op = menuOption()) != 3)
	{
		switch (op)
		{
		case 1:
			(*listDataFuncPtr[0])(datFPtr, idxFPtr);
			break;

		case 2:
			(*listDataFuncPtr[1])(datFPtr, idxFPtr);
			break;

		default:
			printf("\nInvalid option\n");
			break;
		}
	}

	fclose(datFPtr);
	fclose(idxFPtr);
}

int menuOption(void)
{
	int op;
	printf(
		"\nChoose an option\n"
		"1. Natural order\n"
		"2. Account Balance Descending\n"
		"3. Exit\n? "
	);
	scanf("%d", &op);
	fflush(stdin);
	return op;
}

void printDataHeader(void)
{
	printf("\n%-15s %-13s %-10s %-17s %-23s\n",
		"Account Number",
		"First Name",
		"Last Name",
		"Account Balance",
		"Last Payment Amount");
}

void naturalOrder(FILE* datFPtr, FILE* idxFPtr)
{
	rewind(datFPtr);
	ClientData temp = { 0, "", "", 0.0, 0.0 };
	printDataHeader();

	int readCount = fread(&temp, sizeof(ClientData), 1, datFPtr);
	while (!feof(datFPtr) && readCount == 1)
	{
		printf(DATA_FORMAT_STRING,
			temp.accountNumber,
			temp.firstName,
			temp.lastName,
			temp.accountBalance,
			temp.lastPaymentAmount);
		readCount = fread(&temp, sizeof(ClientData), 1, datFPtr);
	}
	puts("");
}

void accountBalanceDecending(FILE* datFPtr, FILE* idxFPtr)
{
	unsigned long fileSize;
	unsigned long recordCount;

	fseek(datFPtr, 0, SEEK_END);
	fileSize = ftell(datFPtr);
	rewind(datFPtr);
	fileSize -= ftell(datFPtr);
	recordCount = fileSize / sizeof(ClientData);

	IndexHeader indexHeader = { "", (time_t)0, 0 };
	rewind(idxFPtr);
	int idxReadCount = fread(&indexHeader, sizeof(IndexHeader), 1, idxFPtr);

	if (idxReadCount != 1) {
		printf("Error reading index header\n");
		fclose(datFPtr);
		fclose(idxFPtr);
		exit(EXIT_FAILURE);
	}

	if (strcmp(indexHeader.datFilename, DAT_FILE) != 0) {
		printf("ERROR - Data and Index File mismatch\n");
		fclose(datFPtr);
		fclose(idxFPtr);
		exit(EXIT_FAILURE);
	}

	if (indexHeader.recordCount != recordCount) {
		printf("ERROR - Data and Index File record count do not match\n");
		fclose(datFPtr);
		fclose(idxFPtr);
		exit(EXIT_FAILURE);
	}

	struct tm* tm = localtime(&indexHeader.createdOn);
	printf("\nAccount balance descending, created on: %s", asctime(tm));
	printDataHeader();

	ClientData clientData = { 0, "", "", 0.0, 0.0 };
	IndexRecord indexRecord = { 0.0, 0 };
	int datReadCount = -1;
	idxReadCount = fread(&indexRecord, sizeof(IndexRecord), 1, idxFPtr);

	while (!feof(idxFPtr) && idxReadCount == 1 && datReadCount != 0)
	{
		if (fseek(datFPtr, indexRecord.filePosition, SEEK_SET) != 0) {
			printf("Seek Error\n");
			fclose(datFPtr);
			fclose(idxFPtr);
			exit(EXIT_FAILURE);
		}

		datReadCount = fread(&clientData, sizeof(ClientData), 1, datFPtr);
		printf(DATA_FORMAT_STRING,
			clientData.accountNumber,
			clientData.firstName,
			clientData.lastName,
			clientData.accountBalance,
			clientData.lastPaymentAmount);

		idxReadCount = fread(&indexRecord, sizeof(IndexRecord), 1, idxFPtr);
	}
	puts("");
}
