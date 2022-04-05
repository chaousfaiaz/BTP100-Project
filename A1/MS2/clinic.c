/*
*****************************************************************************
                        Assignment 1 - Milestone 2
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

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}




// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------


// Displays all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    int i = 0;
    displayPatientTableHeader();
    for (i = 0; i < max; ++i) { // go through patient[]
        if (patient[i].patientNumber != 0) { // patientNumber doesn't have a 0 value
            displayPatientData(&patient[i], fmt); // the ith Patient in patient[] to be displayed
        }
    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max) {
    //int flag = 1;
    int select;
    do {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n"
               "Selection: ");
        select = inputIntRange(0, 2); // makes user select 0, 1, or 2 only
        putchar('\n');
        switch (select) {
            case 1: 
                searchPatientByPatientNumber(patient, max);
                printf("\n");
                suspend();
                break;
            case 2: 
                searchPatientByPhoneNumber(patient, max);
                printf("\n");
                clearInputBuffer();
                suspend();
               // printf("\n");
                break;
        }
    } while(select);
}
    
// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max) {
    int i;
    int current_index = 7;
    for (i = 0; i < max; ++i) {
        if (patient[i].patientNumber == 0) {
            current_index = i;
            break;
        }
    }
    if (current_index == 7) {
        printf("ERROR: Patient listing is FULL!\n\n");
    } else {
        patient[current_index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[current_index]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max) {
    printf("Enter the patient number: ");
    int patient_num = inputIntPositive(); // makers user enter positive int patient number
    int index = findPatientIndexByPatientNum(patient_num, patient, max); // finds matching patient
    printf("\n");
    if (index != -1) {
        menuPatientEdit(&patient[index]);
    } else {
        printf("ERROR: Patient record not found!\n\n");
    }
    //clearInputBuffer();
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max) {
    printf("Enter the patient number: ");
    int patient_num = inputIntPositive(); // makers user enter positive int patient number
    int index = findPatientIndexByPatientNum(patient_num, patient, max); // finds matching patient
    printf("\n");
    if (index != -1) {
        displayPatientData(&patient[index], FMT_FORM); // displays patient form
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        char select = inputCharOption("yn"); // makes user enter y or n
        if (select == 'y') {
            patient[index].patientNumber = 0;
            strcpy(patient[index].name, "\0");
            strcpy(patient[index].phone.description, "\0");
            strcpy(patient[index].phone.number, "\0");
            printf("Patient record has been removed!\n\n");
            clearInputBuffer();
        } else {
            printf("Operation aborted.\n\n");
            clearInputBuffer();
        }
    } else {
        printf("ERROR: Patient record not found!\n\n");
    }
}






//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int index; // this will stay 0 if no matches found
    int pet_num;   // to store entered patient number 
    printf("Search by patient number: ");
    pet_num = inputIntPositive(); // makes user enter a positive int patient number
    index = findPatientIndexByPatientNum(pet_num, patient, max); // gives the index of matching patient
    printf("\n");
    if (index != -1) {
        displayPatientData(&patient[index], FMT_FORM);
    } else {
        printf("*** No records found ***\n");
    }
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int i; 
    int match = 0; // this will stay 0 if no matches found
    char phone_num[PHONE_LEN]; // to store entered phone number
    printf("Search by phone number: ");
    inputCString(phone_num, PHONE_LEN, PHONE_LEN); // makes user enter a 10 digit phone number
    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; ++i) {
        if (strncmp(patient[i].phone.number, phone_num, PHONE_LEN) == 0) {
            displayPatientData(&patient[i], FMT_TABLE);
            ++match;
        }
    }
    if (match == 0) {
        printf("\n*** No records found ***\n");
    } 
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max) {
    int highest = 0;
    int i;
    for (i = 0; i < max; ++i) {
        if (patient[i].patientNumber > highest) {
            highest = patient[i].patientNumber;
        }
    }
    return highest + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max) {
    int i;
    int index_match = -1;
    for (i = 0; i < max; ++i) {
        if (patient[i].patientNumber == patientNumber) {
            index_match = i;
            break;
        }
    }
    return index_match;
}







//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n"
           "------------------\n"
           "Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 0, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone) {
    int select;
    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    select = inputIntRange(1, 4); // makes user select 1, 2, 3, or 4 only
    printf("\n");
    if (select == 1) {
        strcpy(phone->description, "CELL");
        printf("Contact: CELL\n"
               "Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        clearInputBuffer();
        printf("\n");
    } else if (select == 2) {
        strcpy(phone->description, "HOME");
        printf("Contact: HOME\n"
               "Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        clearInputBuffer();
        printf("\n");
    } else if (select == 3) {
        strcpy(phone->description, "WORK");
        printf("Contact: WORK\n"
               "Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        clearInputBuffer();
        printf("\n");
    } else {
        strcpy(phone->description, "TBD");
    }
}


