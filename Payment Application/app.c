#include "app.h"

extern uint8_t gIndexOfValidAccount;
extern ST_accountsDB_t ST_Accounts_DB_t[];

void appStart(void)
{
    ST_cardData_t cardData;
    ST_terminalData_t termData;
    ST_transaction_t transData;

    EN_serverError_t checkResultServ;
    EN_terminalError_t checkResultTerm;
    EN_cardError_t checkResultname;

    getCardHolderName(&cardData);
    fflush(stdin);
    getCardExpiryDate(&cardData);
    fflush(stdin);
    getCardPAN(&cardData);
    fflush(stdin);

    setMaxAmount(&termData);
    getTransactionDate(&termData);

    checkResultTerm = isCardExpired(cardData, termData);

    if (checkResultTerm != TERMINAL_OK)
    {
        printf("\nDECLINED_EXPIRED_CARD\n");
    }
    else
    {
        checkResultTerm = INVALID_MAX_AMOUNT;

        getTransactionAmount(&termData);
        fflush(stdin);
        checkResultTerm = isBelowMaxAmount(&termData);

        if (checkResultTerm != TERMINAL_OK)
        {
            printf("\nDECLINED_AMOUNT_EXCEEDING_LIMIT\n");
        }
        else
        {
            checkResultServ = ACCOUNT_NOT_FOUND;
            checkResultServ = isValidAccount(&cardData);

            if (checkResultServ != TERMINAL_OK)
            {
                printf("\nDECLINED_INVALID_ACCOUNT\n");
            }
            else
            {
                checkResultServ = ACCOUNT_NOT_FOUND;
                transData = (ST_transaction_t){ 0,cardData,termData,0 };
                checkResultServ = isAmountAvailable(&transData);

                if (checkResultServ != TERMINAL_OK)
                {
                    printf("\nDECLINED_INSUFFECIENT_FUNDS\n");
                }
                else
                {
                    EN_transState_t checkResultStat;
                    checkResultStat = INTERNAL_SERVER_ERROR;

                    checkResultStat = recieveTransactionData(&transData);

                    if (checkResultStat != APPROVED)
                    {
                        printf("\nFAILED\n");
                    }
                    else
                    {
                        printf("\nSuccess Transactions Process\n");
                        printf("Your New balance is %.2f", ST_Accounts_DB_t[gIndexOfValidAccount].balance);
                    }
                }
            }
        }
    }
}

void main(void)
{
    printf("\t\t\t\t\t\tWELCOME\n");

    appStart();
}
