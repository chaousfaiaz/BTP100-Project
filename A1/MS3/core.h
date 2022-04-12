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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdio.h>
#include <ctype.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// USER INTERFACE FUNCTIONS /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// receives a phone number in the form of a string array
// validates that the phone number is of length 10 and contains digits only
// then displays the phone number
void displayFormattedPhone(const char *number);


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// USER INPUT FUNCTIONS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

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
char inputCharOption(const char word[]);

// receives a char pointer, an int for min length, and an int for max length
// then takes user input for a C string until one that has a length within range is obtained  
void inputCString(char *strptr, int min, int max);

// takes user input until a phone number of the correct length is entered
// stores it in strptr
void inputPhoneNumber(char *strptr, int num_length);

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// UTILITY FUNCTIONS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// returns 1 if the year is a leap year, and 0 if it isn't
int isLeapYear(int year);

// returns the length of the month
int monthLength(int month, int year);

// swaps the integer values a and b
void swap(int *a, int *b);


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H