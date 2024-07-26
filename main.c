#include "application.h"

int main(void)
{
	ST_cardData_t card;
	//getCardHolderNameTest();
	//getCardExpiryDateTest(&card);
	//getCardPANTest();
	//getTransactionDateTest();
	//isCardExpriedTest();
	//getTransactionAmountTest();
	//isBelowMaxAmountTest();
	//setMaxAmountTest();
	//isValidCardPANTest();

	initialising_accDB();
	initialising_transDB();
	
	//isValidAccountTest();
	//isBlockedAccountTest();
	//isAmountAvailableTest();
	saveTransactionTest();

	/*ST_cardData_t card;
	ST_terminalData_t term;
	inisialising_data(&card, &term);
	term.maxTransAmount = MAX_AMOUNT;
	EN_cardError_t val3 = getCardHolderName(&card);
	if (val3 == WRONG_NAME)
	{
		printf("Wrong name\n");
	}
	getCardExpiryDate(&card);
	getCardPAN(&card);
	EN_terminalError_t val = isValidCardPAN(&card);
	if (val == INVALID_CARD)
	{
		printf("Invalid Card");
	}
	getTransactionDate(&term);
	val =  isCardExpired(&card, &term);
	if (val == EXPIRED_CARD)
	{
		printf("Declined (expired date)\n");
	}
	val = getTransactionAmount(&term);
	val = isBelowMaxAmount(&term);
	if (val == EXCEED_MAX_AMOUNT)
	{
		printf("You exceeded your maximum daily limit\n");
	}
	EN_serverError_t val1 = isValidAccount(&card, &ref);
	if (val1 == ACCOUNT_NOT_FOUND)
	{
		printf("Declined (invalid account)\n");
	}
	EN_serverError_t val2 =  isAmountAvailable(&term, &ref);
	if (val2 == LOW_BALANCE)
	{
		printf("Declined (insufficient funds)\n");
	}
	ref.balance = ref.balance - term.transAmount;
	//recieve trans data
	ST_transaction_t trans = {card, term, RUNNING, transeq};
	/*trans.cardHolderData = card;
	trans.terminalData = term;
	trans.transactionSequenceNumber = transeq;
	trans.transState = RUNNING; 
	saveTransaction(&trans); 
	listSavedTransactions(); */
	//ST_cardData_t card;
	//ST_terminalData_t term;
	/*for (i = 0; i < 4; i++)
	{
		appStart();
		printf("------------------------\n");
	}*/
	//appStart();
	//listSavedTransactions();
}