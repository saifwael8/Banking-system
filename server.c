#define _CRT_SECURE_NO_WARNINGS
#include "server.h"
#include "card.h"
#include "terminal.h"



EN_transState_t recieveTransactionData(ST_transaction_t* transData) //incomplete
{
	EN_serverError_t val = isValidAccount(&transData->cardHolderData, &ref);
		if (val == ACCOUNT_NOT_FOUND)
		{
			return FRAUD_CARD;
		}
		val = isBlockedAccount(&ref);
		if (val == BLOCKED_ACCOUNT)
		{
			return DECLINED_STOLEN_CARD;
		}
		val = isAmountAvailable(&transData->terminalData, &ref);
		if (val == LOW_BALANCE)
		{
			DECLINED_INSUFFECIENT_FUND;
		}
		return APPROVED;
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	for (int i = 0; i < 5; i++)
	{
		int count = 0;
		for (int j = 0; j < cardData->primary_account_size; j++)
		{
			if (cardData->primaryAccountNumber[j] -48 == accountsDB[i].primaryAccountNumber[j] - 48)
			{
				count++;
			}
			if (count == cardData->primary_account_size)
			{
				*accountRefrence = accountsDB[i]; //copy constructor does not work on pointers
				return SERVER_OK;
			}
			
		}
	}
	accountRefrence = NULL;
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == RUNNING)
	{
		return SERVER_OK;
	}
	return BLOCKED_ACCOUNT;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount > accountRefrence->balance)
	{
		return LOW_BALANCE;
	}
	return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (transeq > 256)
	{
		return INTERNAL_SERVER_ERROR;
	}
	transData->transactionSequenceNumber = transeq;
	transactionsDB[transeq].cardHolderData = transData->cardHolderData; //may cause an error
	transactionsDB[transeq].terminalData = transData->terminalData; //may cause an error
	transactionsDB[transeq].transState = transData->transState;
	transeq++;
	return SERVER_OK;
}

void listSavedTransactions(void)
{
	for (int i = 0; i < transeq; i++)
	{
		printf("#########################\n");
		printf("Transaction Sequence Number: %d\n", i + 1);
		printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate); //may cause an error
		printf("Transaction Amount: %f\n", transactionsDB[i].terminalData.transAmount);
		//printf("Transaction State: %s\n", transactionsDB[i].transState); //enum needs translation
		enumtos(transactionsDB[i].transState);
		printf("Terminal Max Amount: %f\n", transactionsDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", transactionsDB[i].cardHolderData.cardHolderName);
		printf("PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
		/*for (int j = 0; j < 20; j++)
		{
			printf(" %c", transactionsDB[i].cardHolderData.primaryAccountNumber[j]);
		} */
		printf("Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
		printf("#########################\n");
		Sleep(1000);
	}
}

void enumtos(EN_transState_t transtate) //better using switch-case
{
	if (transtate == APPROVED)
	{
		printf("Transaction State: Approved\n");
	}
	else if (transtate == DECLINED_INSUFFECIENT_FUND)
	{
		printf("Transaction State: Declined (insuffecient fund)\n");
	}
	else if (transtate == DECLINED_STOLEN_CARD)
	{
		printf("Transaction State: Declined (stolen card)\n");
	}
	else if (transtate == FRAUD_CARD)
	{
		printf("Transaction State: Declined (Fraud card)\n");
	}
	else 
	{
		printf("Transaction State: Internal server error\n");
	}
}

void initialising_accDB(void)
{
	accountsDB[0].balance = 2000.0;
	accountsDB[0].state = RUNNING;
	strcpy(accountsDB[0].primaryAccountNumber, "4929490221354874"); //strcpy is crucial 

	accountsDB[1].balance = 100000.0;
	accountsDB[1].state = BLOCKED;
	strcpy(accountsDB[1].primaryAccountNumber, "5116688643150545");

	accountsDB[2].balance = 1005236.0;
	accountsDB[2].state = RUNNING;
	strcpy(accountsDB[2].primaryAccountNumber, "4003600000000014");

	accountsDB[3].balance = 1000001520.0;
	accountsDB[3].state = RUNNING;
	strcpy(accountsDB[3].primaryAccountNumber, "4560605457143204");

	accountsDB[4].balance = 2000582.0;
	accountsDB[4].state = RUNNING;
	strcpy(accountsDB[4].primaryAccountNumber, "4539716963465698");
} 

void initialising_transDB(void)
{
	for (int i = 0; i < 256; i++)
	{
		transactionsDB[i].transState = 0;
		transactionsDB[i].transactionSequenceNumber = 0;
	}
}


void isValidAccountTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: isValidAccountTest\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_cardData_t Data1;
	ST_accountsDB_t ref;
	EN_cardError_t val = getCardPAN(&Data1);
	EN_serverError_t val1 = isValidAccount(&Data1, &ref);
	printf("Expected Result: Result is Valid\n");
	if (val1 == SERVER_OK)
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
	val1 = isValidAccount(&Data1, &ref);
	printf("Expected Result: Result is Invalid!\n");
	if (val1 == SERVER_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void isBlockedAccountTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: isValidAccountTest\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_cardData_t Data1;
	ST_accountsDB_t ref = accountsDB[3];
	EN_serverError_t val1 = isBlockedAccount(&ref);
	printf("Expected Result: Result is Valid\n");
	if (val1 == SERVER_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	ref = accountsDB[1];
	val1 = isBlockedAccount(&ref);
	printf("Expected Result: Result is Invalid!\n");
	if (val1 == SERVER_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void isAmountAvailableTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: isAmountAvailableTest\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_terminalData_t term;
	ST_accountsDB_t ref = accountsDB[0];
	EN_terminalError_t val = getTransactionAmount(&term);
	EN_serverError_t val1 = isAmountAvailable(&term, &ref);
	printf("Expected Result: Result is Valid\n");
	if (val1 == SERVER_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	ref = accountsDB[3];
	val = getTransactionAmount(&term);
	val1 = isAmountAvailable(&term, &ref);
	printf("Expected Result: Result is Invalid!\n");
	if (val1 == SERVER_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void saveTransactionTest(void)
{
	printf("Tester Name: Saifeldin Wael Elsaid\n");
	printf("Function name: saveTransactionTest + listsaved transactions\n");
	printf("Test Case 1\n");
	printf("Input Data: \n");
	ST_cardData_t card = { "Saif-Eldin Wael Elsaid", "4003600000000014", 16, "05/27" };
	ST_terminalData_t term = {250.0, MAX_AMOUNT, "11/12/2023"};
	ST_transaction_t trans1 = { card, term, RUNNING, transeq };
	EN_serverError_t val1 = saveTransaction(&trans1);
	listSavedTransactions();
	printf("Expected Result: Result is Valid\n");
	if (val1 == SERVER_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
	printf("Test Case 2\n");
	printf("Input Data: \n");
	ST_cardData_t card1 = {"Abdulrahman Wael Elsaid", "4560605457143204", 16, "12/29" }; 
	ST_terminalData_t term1 = { 950.0, MAX_AMOUNT, "11/02/2021" };
	ST_transaction_t trans2 = { card1, term1, RUNNING, transeq };
	val1 = saveTransaction(&trans2);
	listSavedTransactions();
	printf("Expected Result: Result is Invalid!\n");
	if (val1 == SERVER_OK)
	{
		printf("Actual Result: Result is Valid\n");
	}
	else
	{
		printf("Actual Result: Result is Invalid!\n");
	}
}

void inisialising_data(ST_cardData_t* card, ST_terminalData_t* term)
{
	for (int i = 0; i < 25; i++)
	{
		card->cardHolderName[i] = ' ';
	}

	for (int i = 0; i < 20; i++)
	{
		card->primaryAccountNumber[i] = ' ';
	}
	for (int i = 0; i < 6; i++)
	{
		card->cardExpirationDate[i] = ' ';
	}
	for (int i = 0; i < 11; i++)
	{
		term->transactionDate[i] = ' ';
	}
}