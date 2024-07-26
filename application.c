#include "application.h"

void appStart(void)
{
	ST_cardData_t card;
	ST_terminalData_t term;
	inisialising_data(&card, &term);
	term.maxTransAmount = MAX_AMOUNT;
	EN_cardError_t val3 = getCardHolderName(&card);
	if (val3 == WRONG_NAME)
	{
		printf("Wrong name\n");
		return;
	}
	EN_cardError_t Cdate =  getCardExpiryDate(&card);
	if (Cdate == WRONG_EXP_DATE)
	{
		printf("Wrong expiaration date\n");
		return;
	}
	EN_cardError_t Cpan =  getCardPAN(&card);
	if (Cpan == WRONG_PAN)
	{
		printf("Wrong primary account number\n");
	}
	EN_terminalError_t val = isValidCardPAN(&card);
	if (val == INVALID_CARD)
	{
		printf("Invalid Card\n");
		return;
	}
	EN_terminalError_t Tdate =  getTransactionDate(&term);
	if (Tdate == WRONG_DATE)
	{
		printf("Invalid transaction date\n");
		return;
	}
	val = isCardExpired(&card, &term);
	if (val == EXPIRED_CARD)
	{
		printf("Declined (expired date)\n");
		return;
	}
	val = getTransactionAmount(&term);
	if (val == INVALID_AMOUNT)
	{
		printf("Invalid amount\n");
	}
	val = isBelowMaxAmount(&term);
	if (val == EXCEED_MAX_AMOUNT)
	{
		printf("You exceeded your maximum daily limit\n");
		return;
	}
	EN_serverError_t val1 = isValidAccount(&card, &ref);
	if (val1 == ACCOUNT_NOT_FOUND)
	{
		printf("Declined (invalid account)\n");
		return;
	}
	EN_serverError_t val2 = isAmountAvailable(&term, &ref);
	if (val2 == LOW_BALANCE)
	{
		printf("Declined (insufficient funds)\n");
		return;
	}

	ref.balance = ref.balance - term.transAmount;
	//recieve trans data
	ST_transaction_t trans = { card, term, RUNNING, transeq };
	EN_transState_t state = recieveTransactionData(&trans);
	trans.transState = state;
	/*trans.cardHolderData = card;
	trans.terminalData = term;
	trans.transactionSequenceNumber = transeq;
	trans.transState = RUNNING; */
	saveTransaction(&trans);
	

}