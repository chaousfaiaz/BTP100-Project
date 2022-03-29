

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



#include <stdio.h>
#include <ctype.h>

 // Clear the standard input buffer 
 void clearInputBuffer(void);
 
 // Wait for user to input the "enter" key to continue 
 void suspend(void);
 
 // scans user input until an integer is entered
 int inputInt(void);
 
 // scans user input until an integer greater than 0 is entered
 int inputIntPositive(void);
 
 // takes two integers as arguments and sets them as the range, 
 // and then scans user input until an integer within that range is entered
 int inputIntRange(int min, int max);
 
 // receives a string array representing a list of valid characters
 // and then takes user input of a singular character
 // until the entered character matches one in the string argument
 int inputCharOption(const char word[]);
 
 // receieves a char pointer, an int for min length, and an int for max length
 // then takes user input for a C string until one that has a length within range is obtained  
 void inputCString(char *strptr, int min, int max);
 
 // receieves a phone number in the form of a string array
 // validates that the phone number is of length 10 and contains digits only
 // then displays the phone number
 void displayFormattedPhone(const char *number);