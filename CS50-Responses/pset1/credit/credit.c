#include <stdio.h>
#include <cs50.h>

int main(void) {

  long number = get_long("Number: "); // Gets user input
  int digits = 0, lastdigit = 0, DoubledSum = 0, unDoubledSum = 0, totalsum = 0, firstDigit, secondDigit; // Variables

  if (number >= 1000000000000000) { // Checks for total # of digits
    digits = 16;
  } else if (number >= 100000000000000) {
    digits = 15;
  } else if (number >= 1000000000000) {
    digits = 13;
  }

  for (int a = 1; a <= digits; a++, number /= 10) { // Finds last digit, calculates sum of doubled digits
    lastdigit = number % 10; // and sum of un-doubled digits, records first two digits,
    if (a >= (digits - 2)) { // then shifts number right one decimal place & repeats
      if ((digits - a) == 0) {
        firstDigit = lastdigit;
      } else {
        secondDigit = lastdigit;
      }

    }
    if ((a % 2) == 0) {
      ;
      lastdigit *= 2;
      if (lastdigit < 10) {
        DoubledSum += lastdigit;
      } else {
        DoubledSum += (lastdigit % 10);
        lastdigit /= 10;
        DoubledSum += (lastdigit % 10);
      }
    } else {
      unDoubledSum += lastdigit;
    }
  }

  totalsum = unDoubledSum + DoubledSum;

  if ((digits == 13 || digits == 15 || digits == 16) && totalsum % 10 == 0) { // Prints corresponding card to algorithm
    if ((firstDigit == 3) && (secondDigit == 4 || secondDigit == 7)) {
      printf("AMEX\n");
    } else if (firstDigit == 5 && (secondDigit >= 1 && secondDigit <= 5)) {
      printf("MASTERCARD\n");
    } else if (firstDigit == 4) {
      printf("VISA\n");
    } else {
      printf("INVALID\n");
    }
  } else {
    printf("INVALID\n");
  }
}