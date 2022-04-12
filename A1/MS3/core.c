/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// USER INTERFACE FUNCTIONS /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void) 
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

// receives a phone number in the form of a string array
// validates that the phone number is of length 10 and contains digits only
// then displays the phone number
void displayFormattedPhone(const char *number) {
    int i;
    int digits = 0;
    if (number == NULL) {
        printf("(___)___-____");
    } else {
        // find how many digits the number has
        for (i = 0; i < 10; ++i) { // find that number has 10 digits
            if (isdigit(number[i])) {
                ++digits;
            }
        }
        // number isn't 10 digits long:
        if (digits != 10) {
            printf("(___)___-____");
        } else { // number IS 10 digits long
            printf("(");
            for (i = 0; i < 3; ++i) {
                printf("%c", number[i]);
            }
            printf(")");
            for (i = 3; i < 6; ++i) {
                printf("%c", number[i]);
            }
            printf("-");
            for (i = 6; i < 10; ++i) {
                printf("%c", number[i]);
            }
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// USER INPUT FUNCTIONS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// scans user input until an integer is entered
int inputInt(void) {
    char newLine = 'x';
    int val;
    while(1) {
        scanf("%d%c", &val, &newLine);
        if (newLine == '\n') {
            return val;
        } else {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        
    } 
}


// scans user input until an integer greater than 0 is entered
int inputIntPositive(void) {
    char newLine = 'x';
    int val;
    while(1) {
        scanf("%d%c", &val, &newLine);
        if (newLine == '\n') {
            if (val <= 0) {
                printf("ERROR! Value must be > 0: ");
            } else {
                return val;
            }
        } else {
           clearInputBuffer();
            printf("ERROR! Value must be > 0: "); 
        }
    } 
}


// takes two integers as arguments and sets them as the range, 
// and then scans user input until an integer within that range is entered
int inputIntRange(int min, int max) {
    int num;
    while(1) {
      num = inputInt();
      if (min <= num && num <= max) {
          return num;
      } else {
          printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
      }
    }
}


// receives a string array representing a list of valid characters
// and then takes user input of a singular character
// until the entered character matches one in the string argument
char inputCharOption(const char word[]) {
    // determining length of string word[]
    int length = 0;
    int flag = 1;
    while(flag) {
        if (word[length] != '\0') {
            ++length;
        } else { // at null terminator we break
            flag = 0;
        }        
    }
    // taking user input until it matches a character in word[]    
    int i;
    flag = 1;
    char temp[50];
    while(flag) {
        scanf("%[^\n]", temp);
        for(i = 0; i < length; ++i) {
            if (temp[0] == word[i] && temp[1] == '\0') {
                flag = 0; // if there is a match flag = 0 and loop ends
            }
        }
        if (flag) {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", word);
        }       
    }
    return temp[0];
 }

// receieves a char pointer, an int for min length, and an int for max length
// then takes user input for a C string until one that has a length within range is obtained  
void inputCString(char *strptr, int min, int max) {
    char temp[50];
    int length;
    int flag = 1;
    int flag2 = 1;
    while(flag) {
        // take user input string
        scanf ("%[^\n]", temp);
        // find the length of that string
        length = 0;
        while(flag2) {
            if (temp[length] != '\0') {
                ++length;
            } else { // at null terminator we break
                flag2 = 0;
            }
        }
        // see if length is within range
        if (min <= length && length <= max) { // within range
            memset(strptr, '\0', max); // clear strptr first
            strcpy(strptr, temp); // assign the string in temp to the strptr given to function 
         /*   for (i = 0; i < length; ++i ) { 
                strptr[i] = temp[i];
            } */
            flag = 0; // this ends loop
        } else { // not within range
            flag2 = 1; // reset flag2 for next try
            clearInputBuffer();
            if (min == max) {
                printf("ERROR: String length must be exactly %d chars: ", max);
            } else if (length > max) {
                printf("ERROR: String length must be no more than %d chars: ", max);
            } else {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
        }
    }
}

// takes user input until a phone number of the correct length is entered
// stores it in strptr
void inputPhoneNumber(char *strptr, int num_length) {
    char temp[50];
    int length;
    int flag = 1;
    int flag2 = 1;
    while(flag) {
        // take user input string
        scanf ("%[^\n]", temp);
        // find the length of that string
        length = 0;
        while(flag2) {
            if (temp[length] != '\0') {
                ++length;
            } else { // at null terminator we break
                flag2 = 0;
            }
        }
        if (length == num_length) { // length is what phone number length should be
            strcpy(strptr, temp);
            flag = 0; // this ends loop
        } else { // not correct length
            clearInputBuffer();
            flag2 = 1; // reset this flag for next input
            printf("Invalid %d-digit number! Number: ", num_length);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// UTILITY FUNCTIONS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// returns 1 if the year is a leap year, and 0 if it isn't
int isLeapYear(int year) {
    if (year % 4 == 0) { // first check year is divisible by 4;
        if (year % 100 == 0 && year % 400 != 0) { // a century year that isn't also divisible by 400
            return 0;
        } else {
            return 1; // non-century leap years, century years divisible by 400
        }
    } else {
        return 0;
    }
}

// returns the length of the month
int monthLength(int month, int year) {
    if (month == 2) {
        if (isLeapYear(year)) {
            return 29;
        } else {
            return 28;
        }
    } else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    } else {
        return 30;
    }
}

// swaps the integer values a and b
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}