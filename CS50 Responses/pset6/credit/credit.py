# Checks the validity of a credit card with an implementation of Luhn's algorithm, along with additional test checkings

# Regular Expressions module required for string analysis
# sys module for exitcode functions
from cs50 import get_int
import re
import sys


# Looks at beginning numbers of a card, and prints out the corresponding card company
# 34 or 37 for AMEX, 51-55 for MASTERCARD, and  4 for VISA
def printCard(number):
    result = re.match("3[47]", str(number))
    if result != None:
        print("AMEX")
        sys.exit(0)
    result = re.match("5[1-5]", str(number))
    if result != None:
        print("MASTERCARD")
        sys.exit(0)
    result = re.match("4", str(number))
    if result != None:
        print("VISA")
        sys.exit(0)
    print("INVALID")


# Runs card number through Luhn's Algorithm to check if it is valid, returns true if so
def luhn(number):
    length = len(number)
    multipliedDigits = []
    digitSum = 0
    otherSum = 0
    totalSum = 0

    # Starting from 2nd last, multiplies every other digit by 2, and adds to list
    # Beginning condition must be -1 for last index, and -2 for second last index, since arrays are 0-indexed, and length is not
    # End condition must be -1 in order to reach index 0, because the end condition for range(), by design, is not inclusive
    for even in range(length - 2, -1, -2):
        multipliedDigits.append(int(number[even]) * 2)

    # Adds unmultiplied digits
    for odd in range(length - 1, -1, -2):
        otherSum += int(number[odd])

    # Goes through list, and adds 1-digit numbers and digits of two-digit numbers
    for digit in multipliedDigits:
        if digit >= 10:
            digit = str(digit)
            digitSum += int(digit[0])
            digitSum += int(digit[1])
        else:
            digitSum += digit
    
    # Combines sum of unmultiplied digits with sum of the digits of the multiplied digits
    totalSum = digitSum + otherSum
    
    # Checks if last digit is 0, and returns True if so; otherwise, returns False
    if (totalSum % 10) == 0:
        return True
    else:
        return False


# Checks if number is 13, 15, or 16 digits, returns true if so
def lengthCheck(number):
    length = len(number)
    if length == 13 or length == 15 or length == 16:
        return True


def main():
    error = "INVALID"
    
    card = str(get_int("Number: "))
    
    if lengthCheck(card) == False:
        print(error)
        sys.exit(0)
        
    if luhn(card) == False:
        print(error)
        sys.exit(0)
    
    printCard(card)


# Runs main()
main()