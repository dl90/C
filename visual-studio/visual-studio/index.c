#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "assign08.h"

static const char* DAT_FILE;
static const char* INDEX_FILE;

int index(int argc, char* argv[])
{
	atexit(_getch);

	if (argc != 3)
	{
		printf("Need 2 arguments: <Input filename> <output filename>\n");
		exit(EXIT_FAILURE);
	}
	DAT_FILE = argv[1];
	INDEX_FILE = argv[2];

	FILE* readFPtr = fopen(DAT_FILE, "rb");
	if (readFPtr == NULL)
	{
		printf("Error: could not localte/open %s\n", DAT_FILE);
		exit(EXIT_FAILURE);
	}

	FILE* writeFPtr = fopen(INDEX_FILE, "wb");
	if (writeFPtr == NULL)
	{
		printf("Error: could not create %s\n", INDEX_FILE);
		fclose(readFPtr);
		exit(EXIT_FAILURE);
	}

	unsigned long fileSize;
	unsigned long recordCount;

	fseek(readFPtr, 0, SEEK_END);
	fileSize = ftell(readFPtr);
	rewind(readFPtr);
	fileSize -= ftell(readFPtr);
	recordCount = fileSize / sizeof(ClientData);

	ClientData temp = { 0, "", "", 0, 0 };
	IndexRecord* indexRecords = (IndexRecord*)calloc(recordCount, sizeof(IndexRecord));
	if (indexRecords == NULL)
	{
		printf("Error: IndexRecord memory allocation\n");
		exit(EXIT_FAILURE);
	}

	unsigned int rIdx = 0;
	unsigned long readFilePos = ftell(readFPtr);
	int readCount = fread(&temp, sizeof(ClientData), 1, readFPtr);
	while (!feof(readFPtr) && readCount == 1)
	{
		indexRecords[rIdx].accountBalance = temp.accountBalance;
		indexRecords[rIdx].filePosition = readFilePos;
		rIdx++;
		readFilePos = ftell(readFPtr);
		readCount = fread(&temp, sizeof(ClientData), 1, readFPtr);
	}

	qsort(indexRecords, recordCount, sizeof(IndexRecord), accountBalanceDescendingComparator);

	IndexHeader indexHeader = {
		.datFilename = "",
		.createdOn = time(NULL),
		.recordCount = recordCount
	};
	strcpy(indexHeader.datFilename, DAT_FILE);
	int writeCount = fwrite(&indexHeader, sizeof(IndexHeader), 1, writeFPtr);
	if (writeCount != 1) {
		printf("Error: writing index header\n");
		exit(EXIT_FAILURE);
	}

	writeCount = fwrite(indexRecords, sizeof(IndexRecord), recordCount, writeFPtr);
	if (writeCount != recordCount) {
		printf("Error: writing index records %d/%d", writeCount, recordCount);
		exit(EXIT_FAILURE);
	}

	free(indexRecords);
	fclose(readFPtr);
	fclose(writeFPtr);
}

int accountBalanceDescendingComparator(const void* left, const void* right)
{
	IndexRecord* pLeft = (IndexRecord*)left;
	IndexRecord* pRight = (IndexRecord*)right;
	double result = pRight->accountBalance - pLeft->accountBalance;
	if (result > 0) {
		result = 1;
	}
	else if (result < 0) {
		result = -1;
	}
	return (int)result;
}
