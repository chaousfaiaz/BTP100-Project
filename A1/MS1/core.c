

/*
*****************************************************************************
                        Assignment 1 - Milestone 1
Full Name  : MD Faiaz
Student ID#: 164899213
Email      : mfaiaz@myseneca.ca
Section    : NBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/


#include "core.h"


 // As demonstrated in the course notes:
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer 
// Clear the standard input buffer
void clearInputBuffer(void) {
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n') {
        ; // do nothing!
    }
}


// Wait for user to input the "enter" key to continue 
void suspend(void) {
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


// scans user input until an integer is entered
int inputInt(void) {
    char newLine = 'x';
    int val;
    do {
        scanf("%d%c", &val, &newLine);
        if (newLine == '\n') {
            return val;
        } else {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        
    } while (newLine != '\n');
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
int inputCharOption(const char word[]) {
    // determining length of string word[]
    int length = 0;
    while(1) {
        if (word[length] != '\0') {
            ++length;
        } else { // at null terminator we break
            break;
        }        
    }
    // taking user input until it matches a character in word[]    
    int i;
    char match;
    while(1) {
        scanf("%c", &match);
        for(i = 0; i < length; ++i) {
            if (match == word[i]) {
                return match; // if there is a match function will return match and loop ends
            }
        }
        // so this error message is only reached if return does not occur above
        clearInputBuffer();
        printf("ERROR: Character must be one of [");
        for (i = 0; i < length; ++i) {
            printf("%c", word[i]);
        }
        printf("]: ");
    }
 }


// receieves a char pointer, an int for min length, and an int for max length
// then takes user input for a C string until one that has a length within range is obtained  
void inputCString(char *strptr, int min, int max) {
    char temp[max];
    int length, i;
    while(1) {
        // take user input string
        scanf ("%[^\n]", temp);
        // find the length of that string
        length = 0;
        while(1) {
            if (temp[length] != '\0') {
                ++length;
            } else { // at null terminator we break
                break;
            }
        }
        // see if length is within range
        if (min <= length && length <= max) { // within range
            for (i = 0; i < length; ++i ) { // assign the string in temp to the strptr given to function 
                strptr[i] = temp[i];
            }
            break;
        } else { // not within range
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


// receieves a phone number in the form of a string array
// validates that the phone number is of length 10 and contains digits only
// then displays the phone number
void displayFormattedPhone(const char *number) {
    int length = 0;
    int not_all_digits = 0;
    int i;
    // first check if number is NULL
    if (number == NULL) {
        printf("(___)___-____");
    } else {
        // find length of phone number
        while(1) {
            if (number[length] != '\0') {
                ++length;
            } else { // at null terminator we break
                break;
            }
        }
        // check that number contains only digits
        for (i = 0; i < length; ++i) {
            if(!(isdigit(number[i]))) {
                not_all_digits = 1;
            }
        }
        if (length != 10 || not_all_digits) { // if number length isn't 10 or number isn't only digits
            printf("(___)___-____");
        } else { // number satisifies conditions so it is printed
            printf("(");
            for (i = 0; i < 3; ++i) {
                printf("%c", number[i]);
            }
            printf(")");
            for (i = 3; i < 6; ++i) {
                printf("%c", number[i]);
            }
            printf("-");
            for (i = 6; i < length; ++i) {
                printf("%c", number[i]);
            }
        }
    }
}








