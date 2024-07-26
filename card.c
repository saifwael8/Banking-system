#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "card.h"
#include "application.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	int count = 0;
	uint8_t temp[40];
	for (int i = 0; i < 40; i++)
	{
		temp[i] = ' ';
	}
	printf("Enter CardHolder Name: ");
	//fflush(stdin);
	//fflush(stdout);
	/*for (int i = 0; i < 25; i++)
	{
		temp[i] = getchar();
	}*/
	fgets(temp, sizeof(uint8_t)*28, stdin);
	int size = strlen(temp);
	if (size == 1)
	{
		temp[strcspn(temp, "\n")] = 0;
		fgets(temp, sizeof(uint8_t) * 25, stdin);
	}
	temp[strcspn(temp, "\n")] = 0;
	size = strlen(temp);
	if (size > 24 || size < 20)
	{
		return WRONG_NAME;
	}
	for (int i = 0; i < size; i++)
	{
		cardData->cardHolderName[i] = temp[i];
	}
	cardData->cardHolderName[size] = '\0';
	return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t temp[15];
	for (int i = 0; i < 15; i++)
	{
		temp[i] = ' ';
	}
	printf("Enter card expiry date please: ");
	fflush(stdin);
	gets(temp);
	int size = strlen(temp);
	if (size == 0) //gets error solution
	{
		gets(temp);
	}
	size = strlen(temp);
	if (size > 5 || size < 5)
	{
		return WRONG_EXP_DATE;
	}
	for (int i = 0; i < 5; i++)
	{
		if (temp[0] >= 49 && temp[1] > 50)
		{
			return WRONG_EXP_DATE;
		}
		if (i == 2)
		{
			if (temp[i] != 47)
			{
				return WRONG_EXP_DATE;
			}
			else
			{
				continue;
			}
		}
		if (temp[i] > 57 || temp[i] < 48 )
		{
			return WRONG_EXP_DATE;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		cardData->cardExpirationDate[i] = temp[i];
	}
	cardData->cardExpirationDate[5] = '\0';
	return CARD_OK;
}

int sum_of_digits(float number) //in integer division always divide over a float, male all variables dealing with floats a float
{
	float sum = 0;
	while (number > 1)
	{
		float p = ((number / 10.0) - floor(number / 10.0)) * 10;
		sum = sum + ((number / 10.0) - floor(number / 10.0)) * 10;
		number = floor(number / 10.0);
	}
	return sum + number;
}

uint8_t card_number_verification(uint8_t* arr, uint8_t size)
{
	int sum1 = 0;
	int sum2 = 0;
	if (arr[0] == '4' || (arr[0] == '5' && arr[1] == '1') || (arr[0] == '5' && arr[1] == '2') || (arr[0] == '5' && arr[1] == '3') || (arr[0] == '5' && arr[1] == '4') || (arr[0] == '5' && arr[1] == '5') || (arr[0] == '3' && arr[1] == '4') || (arr[0] == '3' && arr[1] == '7'))
	{
		for (int i = 0; i < size; i = i + 2)
		{
			int x = arr[i];
			x = x - 48;
			float z = x * 2;
			if (z > 9)
			{
				sum1 = sum1 + sum_of_digits(z);
				continue;
			}
			sum1 = sum1 + x * 2;
		}
		for (int i = 1; i < size; i = i + 2)
		{
			int y = arr[i];
			y = y - 48;
			sum2 = sum2 + y;
		}
		if ((sum1 + sum2) % 10 == 0)
		{
			return 0;
		}
		return 1;
	}
	return 1;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) //do not use strlen() as an argument or condition
{
	uint8_t temp[22];
	printf("Please enter the primary account number (PAN): ");
	fflush(stdin);
	gets(temp);
	int size = strlen(temp);
	if (size == 0) //gets error solution
	{
		gets(temp);
	}
	uint8_t string_size = strlen(temp);
	cardData->primary_account_size = string_size;
	if (string_size > 19 || string_size < 16)
	{
		return WRONG_PAN;
	}
	cardData->primary_account_size = string_size;
	for (int i = 0; i < string_size; i++)
	{
		cardData->primaryAccountNumber[i] = temp[i];
	}
	cardData->primaryAccountNumber[string_size] = '\0'; //an essential move to change an array of characters to string
	return CARD_OK;
}

void getCardPANTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: getCardPAN\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_cardData_t Data1;
	EN_cardError_t val = getCardPAN(&Data1);
	printf("Expected Result: Result is Valid\n");
	if (val == CARD_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	val = getCardPAN(&Data1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == CARD_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}


void getCardHolderNameTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: getCardHolderName\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_cardData_t Data1;
	EN_cardError_t val = getCardHolderName(&Data1);
	printf("Expected Result: Result is Valid\n");
	if (val == CARD_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	val = getCardHolderName(&Data1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == CARD_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void getCardExpiryDateTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: getCardExpiryDate\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_cardData_t Data1;
	EN_cardError_t val = getCardExpiryDate(&Data1);
	printf("Expected Result: Result is Valid\n");
	if (val == CARD_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	val = getCardExpiryDate(&Data1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == CARD_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}



