#include "terminal.h"
#include "card.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t date[15];
	printf("Please enter transaction date: ");
	fflush(stdin);
	gets(date);
	int size = strlen(date);
	if (size < 10 || size == 0 || size > 10)
	{
		return WRONG_DATE;
	}
	if (date[0] >= 51 && date[1] > 49)
	{
		return WRONG_DATE;
	}
	if (date[3] >= 49 && date[4] > 50)
	{
		return WRONG_DATE;
	}
	if (date[2] != 47 || date[5] != 47)
	{
		return WRONG_DATE;
	}
	for (int i = 6; i < 10; i++)
	{
		if (date[i] > 57 || date[i] < 48)
		{
			return WRONG_DATE;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		termData->transactionDate[i] = date[i];
	}
	termData->transactionDate[size] = '\0'; //Appending the NULL character to the end of the arr of chars to form a string
	return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	int sum1 = 0;
	int sum2 = 0;
	int sum3 = 0;
	int sum4 = 0;

	for (int i = 8; i < 10; i++)
	{
		sum1 = sum1 + (termData->transactionDate[i] - 48);
	}
	for (int i = 3; i < 5; i++)
	{
		sum2 = sum2 + (cardData->cardExpirationDate[i] - 48);
	}
	if (sum2 > sum1)
	{
		return TERMINAL_OK;
	}
	else if (sum1 > sum2)
	{
		return EXPIRED_CARD;
	}
	else
	{
		sum3 = (cardData->cardExpirationDate[0] - 48) + (cardData->cardExpirationDate[1] - 48);
		sum4 = (termData->transactionDate[3] - 48) + (termData->transactionDate[4] - 48);
		if (sum3 >= sum4)
		{
			return TERMINAL_OK;
		}
	}
	return EXPIRED_CARD;
	
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float temp = 0;
	printf("Enter transaction amount: ");
	fflush(stdin);
	scanf_s("%f", &temp);
	if (temp <= 0)
	{
		return INVALID_AMOUNT;
	}
	termData->transAmount = temp;
	return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount <= 0)
	{
		INVALID_MAX_AMOUNT;
	}
	termData->maxTransAmount = maxAmount;
	return TERMINAL_OK;
}


EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	uint8_t val = card_number_verification(cardData->primaryAccountNumber, cardData->primary_account_size);
	if (val == 1)
	{
		return INVALID_CARD;
	} 
	TERMINAL_OK;
	//The previous part will have a dedicated function
}


void getTransactionDateTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: getTransactionDate\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_terminalData_t term1;
	EN_terminalError_t val = getTransactionDate(&term1);
	printf("Expected Result: Result is Valid\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	val = getTransactionDate(&term1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void isCardExpriedTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: isCardExpried\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_terminalData_t term1;
	ST_cardData_t card1;
	EN_cardError_t d1 = getCardExpiryDate(&card1);
	EN_terminalError_t d2 = getTransactionDate(&term1);
	EN_terminalError_t val = isCardExpired(&card1,&term1);
	printf("Expected Result: Result is Valid\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	d1 = getCardExpiryDate(&card1);
	d2 = getTransactionDate(&term1);
	val = isCardExpired(&card1, &term1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void getTransactionAmountTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: getTransactionAmount\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_terminalData_t term1;
	EN_terminalError_t val = getTransactionAmount(&term1);
	printf("Expected Result: Result is Valid\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	val = getTransactionAmount(&term1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void isBelowMaxAmountTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: isBelowMaxAmount\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_terminalData_t term1;
	term1.maxTransAmount = MAX_AMOUNT;
	EN_terminalError_t v = getTransactionAmount(&term1);
	EN_terminalError_t val = isBelowMaxAmount(&term1);
	printf("Expected Result: Result is Valid\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	v = getTransactionAmount(&term1);
	val = isBelowMaxAmount(&term1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void setMaxAmountTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: setMaxAmount\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_terminalData_t term1;
	EN_terminalError_t v = getTransactionAmount(&term1);
	EN_terminalError_t val1 = setMaxAmount(&term1, MAX_AMOUNT);//max amount cannot be an input from the user and must be predetermined 
	EN_terminalError_t val = isBelowMaxAmount(&term1);
	printf("Expected Result: Result is Valid\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	v = getTransactionAmount(&term1);
	val1 = setMaxAmount(&term1, MAX_AMOUNT);
	val = isBelowMaxAmount(&term1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void isValidCardPANTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: isValidCardPAN\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_cardData_t card1;
	EN_cardError_t val1 = getCardPAN(&card1);
	EN_terminalError_t val = isValidCardPAN(&card1);
	printf("Expected Result: Result is Valid\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	val1 = getCardPAN(&card1);
	val = isValidCardPAN(&card1);
	printf("Expected Result: Result is Invalid!\n");
	if (val == TERMINAL_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}
