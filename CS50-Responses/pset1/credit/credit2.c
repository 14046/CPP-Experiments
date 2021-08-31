#include <cs50.h>
#include <stdio.h>
#include <math.h>

// I was too lazy to make comments. I will try to improve on this.

void printResult();
void getLength(long answer);
void changeResult(string newResult);
void checkSum(int sum);
void checkCompany(long number);
long decrementPlaceValue(long number);
int getDigitFromEnd(long number);
int multiplyByTwo(int number);
int splitAndAdd(int number);
bool checkEven(int number);

int length, oddSum = 0, evenSum = 0, combinedSum;
string cardType;

int main(void)
{
    long cardNumber, copyOfCardNumber;

    cardNumber = get_long("Number: ");

    copyOfCardNumber = cardNumber;

    getLength(cardNumber);

    for (int i = 1; i <= length; i++)
    {
        if (checkEven(i) == true)
        {
            evenSum += splitAndAdd(multiplyByTwo(getDigitFromEnd(copyOfCardNumber)));
            copyOfCardNumber = decrementPlaceValue(copyOfCardNumber);
        }
        else
        {
            oddSum += getDigitFromEnd(copyOfCardNumber);
            copyOfCardNumber = decrementPlaceValue(copyOfCardNumber);
        }
    }

    combinedSum = oddSum + evenSum;

    checkSum(combinedSum);

    checkCompany(cardNumber);

    printResult();
}

void getLength(long number)
{
    if (number >= pow(10, 12) && number < pow(10, 13))
    {
        length = 13;
    }
    else if (number >= pow(10, 14) && number < pow(10, 15))
    {
        length = 15;
    }
    else if (number >= pow(10, 15) && number < pow(10, 16))
    {
        length = 16;
    }
    else
    {
        changeResult("INVALID");
    }
}

void changeResult(string newResult)
{
    if (cardType == NULL)
    {
        cardType = newResult;
    }
    else
    {
        return;
    }
}

void printResult()
{
    printf("%s\n", cardType);
}

int getDigitFromEnd(long number)
{
    return number % 10;
}

long decrementPlaceValue(long number)
{
    return number / 10;
}

bool checkEven(int number)
{
    number %= 2;

    if (number == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int multiplyByTwo(int number)
{
    return number * 2;
}

int splitAndAdd(int number)
{
    if (number >= 10)
    {
        int sumOfDigits = 0;
        sumOfDigits += getDigitFromEnd(number);
        number = decrementPlaceValue(number);
        sumOfDigits += number;
        return sumOfDigits;
    }
    else
    {
        return number;
    }
}

void checkSum(int sum)
{
    if ((sum % 10) == 0)
    {
        return;
    }
    else
    {
        changeResult("INVALID");
    }
}

void checkCompany(long number)
{
    number /= pow(10, (length - 2));

    number = (int) number;

    if (number == 34 || number == 37)
    {
        changeResult("AMEX");
    }
    else if (number >= 51 && number <= 55)
    {
        changeResult("MASTERCARD");
    }
    else if (number >= 40 && number <= 49)
    {
        changeResult("VISA");
    }
    else
    {
        changeResult("INVALID");
    }
}