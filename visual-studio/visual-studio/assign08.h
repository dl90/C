#ifndef ASSIGN_08_H
#define ASSIGN_08_H

#include <time.h>

typedef struct
{
	unsigned int accountNumber;
	char firstName[20];
	char lastName[20];
	double accountBalance;
	double lastPaymentAmount;
} ClientData;

typedef struct
{
	double accountBalance;
	unsigned long filePosition;
} IndexRecord;

typedef struct
{
	char datFilename[20];
	time_t createdOn;
	unsigned long recordCount;
} IndexHeader;


int menuOption(void);
void printDataHeader(void);
void naturalOrder(FILE* dat, FILE* idx);
void accountBalanceDecending(FILE* dat, FILE* idx);
int accountBalanceDescendingComparator(const void* left, const void* right);

#endif