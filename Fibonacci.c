// Fibonacci Data Structures Project, by John Bodoh, U0000007613

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "Fibonacci.h"

// Returns digits array of passed hugeIntegers
int *add(HugeInteger *longInt, HugeInteger *shortInt);

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    HugeInteger *hugeIntSum;
    int *sumTempArray, pEqualOrLonger, *tempDigitsPtr, i;

    // Allocate memory for hugeIntSum
    hugeIntSum = malloc(sizeof(HugeInteger));
    if(hugeIntSum == NULL)
        return NULL;
    // Check if any passed HugeIntegers are null
    if(p == NULL || p->digits == NULL || q == NULL || q->digits == NULL)
        return NULL;
    // Determine whether p or q is longer, set pEqualOrLonger flag appropriately, and perform addition
    if(p->length >= q->length)
    {
        pEqualOrLonger = 1;
        sumTempArray = add(p, q);
    }
    else
    {
        pEqualOrLonger = 0;
        sumTempArray = add(q, p);
    }
    // Check if add() returned null
    if(sumTempArray == NULL)
        return NULL;
    // Determine number of digits in sum by checking if the final carry value in sumTempArray is 0, and allocate memory for digits in hugeIntSum
    if(pEqualOrLonger && sumTempArray[p->length] == 0)
    {
        hugeIntSum->length = p->length;
        hugeIntSum->digits = malloc(sizeof(int) * p->length);
    }
    else if(pEqualOrLonger && sumTempArray[p->length] != 0)
    {
        hugeIntSum->length = p->length + 1;
        hugeIntSum->digits = malloc(sizeof(int) * (p->length + 1));
    }
    else if(!pEqualOrLonger && sumTempArray[q->length] == 0)
    {
        hugeIntSum->length = q->length;
        hugeIntSum->digits = malloc(sizeof(int) * q->length);
    }
    else
    {
        hugeIntSum->length = q->length + 1;
        hugeIntSum->digits = malloc(sizeof(int) * (q->length + 1));
    }
    if(hugeIntSum->digits == NULL)
    {
        free(hugeIntSum);
        free(sumTempArray);
        return NULL;
    }
    // populate hugeIntSum->digits with sumTempArray
    for(i = 0; i < hugeIntSum->length; i++)
        hugeIntSum->digits[i] = sumTempArray[i];
    free(sumTempArray);
    return hugeIntSum;
}

HugeInteger *hugeDestroyer(HugeInteger *p)
{
    // Make sure neither p nor p->digits is null, and if so, handle appropriately
    if(p == NULL)
        return NULL;
    if(p->digits == NULL)
    {
        free(p);
        return NULL;
    }
    free(p->digits);
    free(p);
    return NULL;
}

HugeInteger *parseString(char *str)
{
    HugeInteger *hugeInt;
    int hugeIntNumDigits, stringPos, i;

    // Check for null string
    if(str == NULL)
        return NULL;
    // Allocate space for hugeInt
    hugeInt = malloc(sizeof(HugeInteger));
    if(hugeInt == NULL)
        return NULL;
    // For an empty or "0" string, create a HugeInteger equal to 0
    if((strcmp(str, "") == 0) || (strcmp(str, "0") == 0))
    {
        hugeInt->digits = malloc(sizeof(int));
        hugeInt->digits[0] = 0;
        hugeInt->length = 1;
        return hugeInt;
    }
    // Number of digits in string is equal to length of string
    hugeIntNumDigits = strlen(str);
    // Set length of hugeInt and allocate memory for hugeInt->digits
    hugeInt->length = hugeIntNumDigits;
    hugeInt->digits = malloc(sizeof(int) * hugeIntNumDigits);
    if(hugeInt->digits == NULL)
    {
        free(hugeInt);
        return(0);
    }
    // Populate hugeInt->digits
    for(stringPos = 0; hugeIntNumDigits > 0 && stringPos < strlen(str); stringPos++, hugeIntNumDigits--)
        // Get numerical value of ASCII digit by typecasting as int and subtracting 48
        hugeInt->digits[hugeIntNumDigits - 1] = (int)str[stringPos] - 48;
    return hugeInt;
}

HugeInteger *parseInt(unsigned int n)
{
    HugeInteger *hugeInt;
    int hugeIntNumDigits, i, tempDigit, hugeIntDigitsTempSize;
    unsigned int tempNum;
    void* tempDigitsPtr;

    // Allocate memory for hugeInt
    hugeInt = malloc(sizeof(HugeInteger));
    if(hugeInt == NULL)
        return NULL;
    // Handle case where sent integer is 0
    if(n == 0)
    {
        hugeInt->digits = malloc(sizeof(int));
        if(hugeInt->digits == NULL)
        {
            free(hugeInt);
            return NULL;
        }
        hugeInt->length = 1;
        hugeInt->digits[0] = 0;
        return hugeInt;
    }
    // Allocate initial block of memory for hugeInt digits
    hugeIntDigitsTempSize = 10;
    hugeInt->digits = malloc(sizeof(int) * hugeIntDigitsTempSize);
    if(hugeInt->digits == NULL)
    {
        free(hugeInt);
        return NULL;
    }
    i = 0;
    hugeIntNumDigits = 0;
    tempNum = n;
    // For each digit in n, add it to hugeInt using modulus to find the value of each digit, and increment the digit counter
    while(tempNum != 0)
    {
        tempDigit = tempNum % 10;
        hugeInt->digits[i] = tempDigit;
        tempNum = tempNum - tempDigit;
        tempNum = tempNum / 10;
        hugeIntNumDigits++;
        i++;
        // Allocate space for 5 more ints if allocated memory runs out
        if(i == (hugeIntDigitsTempSize - 1))
        {
            hugeIntDigitsTempSize += 5;
            tempDigitsPtr = realloc(hugeInt->digits, sizeof(int) * hugeIntDigitsTempSize);
            if(tempDigitsPtr == NULL)
            {
                free(hugeInt->digits);
                free(hugeInt);
                return NULL;
            }
            else
                hugeInt->digits = tempDigitsPtr;
        }
    }
    // Set length of HugeInteger equal to counted number of digits
    hugeInt->length = hugeIntNumDigits;
    // Reallocate hugeInt->digits size to match number of digits
    tempDigitsPtr = realloc(hugeInt->digits, sizeof(int) * hugeIntNumDigits);
    if(tempDigitsPtr == NULL)
    {
        free(hugeInt->digits);
        free(hugeInt);
        return NULL;
    }
    else
        hugeInt->digits = tempDigitsPtr;
    return hugeInt;
}

unsigned int *toUnsignedInt(HugeInteger *p)
{
    HugeInteger *maxValue;
    unsigned int *unsignedIntPtr, unsignedInt;
    int digitPos, isLargerSmallerFlag;

    if(p == NULL)
        return NULL;
    if(p->digits == NULL)
        return NULL;
    // Convert UINT_MAX to HugeInteger for comparison purposes
    maxValue = parseInt(UINT_MAX);
    if(maxValue == NULL)
        return NULL;
    // Check if p has more digits than maxValue, if so we know p is larger than maxValue
    if(p->length > maxValue->length)
    {
        free(maxValue->digits);
        free(maxValue);
        return NULL;
    }
    // Check if p and maxValue have the same number of digits, if so manually check each digit to ensure that p is not greater than maxValue
    if(p->length == maxValue->length)
    {
        digitPos = (p->length - 1);
        // flag is 0 when p is less than maxValue, 1 when p is larger
        isLargerSmallerFlag = -1;
        while(isLargerSmallerFlag == -1 && digitPos >= 0)
        {
            if(p->digits[digitPos] > maxValue->digits[digitPos])
                isLargerSmallerFlag = 1;
            if(p->digits[digitPos] < maxValue->digits[digitPos])
                isLargerSmallerFlag = 0;
            digitPos--;
        }
        // p is larger than maxValue, return NULL
        if(isLargerSmallerFlag == 1)
        {
            free(maxValue->digits);
            free(maxValue);
            return NULL;
        }
    }
    // Convert p to unsigned int
    for(digitPos = (p->length - 1); digitPos >= 0; digitPos--)
        unsignedInt += (p->digits[digitPos] * pow(10, (digitPos)));
    // Allocate space for returned pointer and set unsignedInt equal to it
    unsignedIntPtr = malloc(sizeof(unsigned int));
    if(unsignedIntPtr == NULL)
    {
        free(maxValue->digits);
        free(maxValue);
        return NULL;
    }
    *unsignedIntPtr = unsignedInt;
    free(maxValue->digits);
    free(maxValue);
    return unsignedIntPtr;
}

HugeInteger *fib(int n)
{
    HugeInteger *fibArray[3];
    int sum1Index, sum2Index, resultIndex;

    if((n == 0) || (n == 1))
        return parseInt(n);
    // Set all index values such that they will equal their correct first values in the loop
    sum1Index = 2;
    sum2Index = 0;
    resultIndex = 1;
    // Fill fibArray with initial values
    fibArray[0] = parseInt(0);
    fibArray[1] = parseInt(1);
    fibArray[2] = NULL;
    // During each addition, fibArray[resultIndex] must equal the sum of fibArray[sum1Index] and fibArray[sum2Index]
    for(n -= 1; n > 0; n--)
    {
        // Change index values for next addition
        sum1Index = (sum1Index + 1) % 3;
        sum2Index = (sum2Index + 1) % 3;
        resultIndex = (resultIndex + 1) % 3;
        fibArray[resultIndex] = hugeAdd(fibArray[sum1Index], fibArray[sum2Index]);
        // Free number not used in next addition
        free(fibArray[sum1Index]->digits);
        free(fibArray[sum1Index]);
    }
    free(fibArray[sum2Index]->digits);
    free(fibArray[sum2Index]);
    return fibArray[resultIndex];
}

double difficultyRating()
{
    return 3.0;
}

double hoursSpent()
{
    return 15;
}

// Returns digits array of passed hugeIntegers
int *add(HugeInteger *longInt, HugeInteger *shortInt)
{
    int sumDigit, carry, *sum, *tempDigitsPtr, i;

    // Allocate space for sum array to account for carry digit
    sum = malloc(sizeof(int) * (longInt->length + 1));
    if(sum == NULL)
        return NULL;
    carry = 0;
    // Add together all shortInt and longInt digits
    for(i = 0; i < shortInt->length; i++)
    {
        sumDigit = longInt->digits[i] + shortInt->digits[i] + carry;
        sum[i] = sumDigit % 10;
        carry = sumDigit / 10;
    }
    // Handle any remaining carries
    for(; i < longInt->length; i++)
    {
        sumDigit = longInt->digits[i] + carry;
        sum[i] = sumDigit % 10;
        carry = sumDigit / 10;
    }
    // Perform last carry
    sum[i] = carry;
    return sum;
}
