#pragma once
#ifndef CARD_H
#define CARD_H
#include <ctype.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

typedef unsigned char uint8_t;


typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t primary_account_size;
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

int sum_of_digits(float number); //utility functions
uint8_t card_number_verification(uint8_t* arr, uint8_t size);


void getCardHolderNameTest(void); //test functions
void getCardExpiryDateTest(void);
void getCardPANTest(void);

#endif // !CARD_H

