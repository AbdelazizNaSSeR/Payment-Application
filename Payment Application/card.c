#include "card.h"

#define cardMonthStartInd   0
#define cardMonthEndInd     1
#define cardYearStartInd    3
#define cardYearEndInd      4

EN_cardError_t getCardHolderName(ST_cardData_t * cardData)
{
    uint8_t cardHolderName[25];
    uint8_t cardHolderNameLength;
    EN_cardError_t retResult = CARD_OK;
    EN_cardError_t isChar = CARD_OK;

    printf("\nPlease enter the card holder name: ");
    scanf("%[^\n]s", cardHolderName);
    printf("\n");

    cardHolderNameLength = strlen(cardHolderName);
    if (cardData == NULL)
    {
        retResult = WRONG_NAME;
    }
    else if ((cardHolderNameLength < 25) && (cardHolderNameLength > 19))
    {
        int i;

        for (i = 0; cardHolderName[i] != '\0'; i++)
        {
            if (((cardHolderName[i] >= 'a') && (cardHolderName[i] <= 'z'))
                || ((cardHolderName[i] >= 'A') && (cardHolderName[i] <= 'Z'))
                || (cardHolderName[i] == ' '))
            {
                continue;
            }
            else
            {
                retResult = WRONG_NAME;
                isChar = WRONG_NAME;
                break;
            }
        }
        if (isChar == CARD_OK)
        {
            strcpy(cardData->cardHolderName, cardHolderName);
        }
    }
    else
    {
        printf("DECLINED_WRONG_NAME");
        retResult = WRONG_NAME;
        exit(0);
    }

    return retResult;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    uint8_t cardExpirationDate[5];
    uint8_t cardExpirationDateLength;
    EN_cardError_t retResult = CARD_OK;

    uint8_t month;
    uint8_t year;

    printf("Please enter the expiry date: ");
    scanf("%[^\n]s", cardExpirationDate);
    printf("\n");

    month = convertDateToInteger(cardExpirationDate, cardMonthStartInd, cardMonthEndInd);
    year = convertDateToInteger(cardExpirationDate, cardYearStartInd, cardYearEndInd);
    cardExpirationDateLength = strlen(cardExpirationDate);

    if (cardData == NULL)
    {
        retResult = WRONG_NAME;
    }
    else if (cardExpirationDateLength == 5 && cardExpirationDate[2] == '/' && year > 0 && month > 0 && month < 13)
    {
        strcpy(cardData->cardExpirationDate, cardExpirationDate);
    }
    else
    {
        retResult = WRONG_EXP_DATE;
    }

    return retResult;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    uint8_t primaryAccountNumber[20];
    uint8_t primaryAccountNumberLength;
    EN_cardError_t retResult = CARD_OK;
    EN_cardError_t isNumeric = CARD_OK;

    printf("Please enter the Primary Account Number: ");
    scanf("%[^\n]s", primaryAccountNumber);
    printf("\n");

    primaryAccountNumberLength = strlen(primaryAccountNumber);

    if (cardData == NULL)
    {
        retResult = WRONG_NAME;
    }
    else if ((primaryAccountNumberLength > 15) && (primaryAccountNumberLength < 20))
    {
        int i;

        for (i = 0; primaryAccountNumber[i] != '\0'; i++)
        {
            if ((primaryAccountNumber[i] >= '0') && (primaryAccountNumber[i] <= '9'))
            {
                continue;
            }
            else
            {
                retResult = WRONG_PAN;
                isNumeric = WRONG_PAN;
                break;
            }
        }
        if (isNumeric == CARD_OK)
        {
            strcpy(cardData->primaryAccountNumber, primaryAccountNumber);
        }
    }
    else
    {
        retResult = WRONG_PAN;
    }

    return retResult;
}
