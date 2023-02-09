#include <cs50.h>
#include <stdio.h>

//Validate that a credit card is strictly numbers
//implement Luhn's algorithm
//modulo credit to zero


//Initialize functions for later use
int Luhn(long credit);
void Validate(long creditNum, int algoRes);



int main(void)
{
    string res;
    int algoRes;
    long credit;

//Continue asking for the card number until it's the proper length
    do
    {

        credit = get_long("Number: ");
        if(credit / 1000000000000 < 1)
        {
            printf("INVALID\n");
            return 0;
        }
    }
    while (credit / 1000000000000 < 1 );


    algoRes = Luhn(credit);

    Validate(credit, algoRes);

}

//Luhn's Algorithm
//long as input.
//output an integer representing every other digit's sum
//If sums last digit is a zero, then the card is valid
int Luhn(long credit)
{

    int sum = 0;
    int place = 0;
    int possDub;

    while (credit !=0)
    {
        //Checking evert other digit
        if (place % 2 != 0)
        {
            //seperates double digit numbers to add them individualy
            possDub = 2 * (credit % 10);
            if(possDub > 9)
            {
                sum += (possDub / 10) + (possDub % 10);
            }
            //multiply number at placement by 2 and add to variable
            else
            {
                sum += 2 * (credit % 10);
            }
        }else
        {
            //add regular digit to variable
            sum += credit%10;
        }
        //update credit value to remove numnber previously used
        credit = credit/10;
        //increment position each cycle
        place++;
    }

    //printf("%d", sum);
    return sum;
}

//function that validates card number based on the the luhn's algorithm and the length of the credit card number
void Validate(long creditNum, int algoRes)
{
    //Express uses 15 digits
    //Express starts with 34 or 37

    //Mastercard uses 16 digits
    //Master starts with 51, 52, 53, 54, or 55

    //Visa uses 13 and 16 digits
    //Visa starts with 4

    int tot_length = 0;
    long card_copy = creditNum;
    int master_card;
    int americanX;
    int Visa;
    char res[] = "";


    //while loop that will contine running incrementaly counting the length of the card number
    while(card_copy != 0)
    {
        card_copy = card_copy / 10;
        tot_length++;

    }

    if (algoRes % 10 == 0)
    {
        //divide the credit card number to collect the first two digits based on the expected length of the credit card number
        americanX = creditNum / 10000000000000;
        master_card = creditNum / 100000000000000;
        Visa = creditNum / 1000000000000;

        //America Express
        if((americanX == 34 || americanX == 37) && tot_length == 15)
        {
            res = "AMEX\n";
            printf("%s", res);
            return;
        }


        //Master
        if((master_card >= 51 && master_card <= 55) && tot_length == 16)
        {
            res = "MASTERCARD\n";
            printf("%s", res);
            return;
        }


        //Visa
        //printf("%i\n", Visa);
        if((tot_length == 13 || tot_length == 16) && (Visa == 4 || master_card / 10 == 4))
        {
            res = "VISA\n";
            printf("%s", res);
            return;
        }

        res = "INVALID\n";

    }//if no conditions are true, then the card is invalid
    else
    {
        res = "INVALID\n";
    }
    printf("%s", res);
    return;
}