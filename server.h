#pragma once
#ifndef SERVER_H //header file guard
#define SERVER_H
#include "card.h"
#include "terminal.h"

typedef unsigned int uint32_t;

static int accountsDB_size = 0; //will change upon testing 
static uint32_t transeq = 0;  //make the global variables in header files always static to prevent multiple definitions


typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;
typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


ST_accountsDB_t accountsDB[255]; //never declare global variables before the struct declaration, NEVER!
ST_transaction_t transactionsDB[255];

EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
void listSavedTransactions(void);


//utility functions
void enumtos(EN_transState_t transtate);
void initialising_accDB(void);
void initialising_transDB(void);
void inisialising_data(ST_cardData_t* card, ST_terminalData_t* term);


//test functions
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);


static ST_accountsDB_t ref = {0, RUNNING, " "}; //global variables in header files must be static and struct globale variables in header file must be initialised after the struct definition

#endif
