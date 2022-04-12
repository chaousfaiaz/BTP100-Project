/*
*****************************************************************************
                        Assignment 1 - Milestone 3
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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// DISPLAY FUNCTIONS //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// MENU & ITEM SELECTION FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format (from MS#2)
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

// Search for a patient record based on patient number or phone number (from MS#2)
void searchPatientData(const struct Patient patient[], int max) {
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
                break;
        }
    } while(select);
}

// Add a new patient record to the patient array (from MS#2)
void addPatient(struct Patient patient[], int max) {
    int i;
    int current_index = -1;
    for (i = 0; i < max; ++i) {
        if (patient[i].patientNumber == 0) {
            current_index = i;
            break;
        }
    }
    if (current_index == -1) {
        printf("ERROR: Patient listing is FULL!\n\n");
    } else {
        patient[current_index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[current_index]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array (from MS#2)
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
}

// Remove a patient record from the patient array (from MS#2)
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

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//                         Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData *clinic) {
    int i;
    int length = 0;
    struct Appointment valid_appointments[clinic->maxAppointments];
    for (i = 0; i < clinic->maxAppointments; ++i) {
        if (clinic->appointments[i].patientNumber > 0) {
            valid_appointments[length] = clinic->appointments[i];
            ++length;
        }
    }
    sortAppointmentArray(valid_appointments, length);
    displayScheduleTableHeader(NULL, FMT_ALL_RECORDS);
    int index;
    for (i = 0; i < length; ++i) {
        index = findPatientIndexByPatientNum(valid_appointments[i].patientNumber, clinic->patients, clinic->maxPatient);
        displayScheduleData(&clinic->patients[index], &valid_appointments[i], DATE_FIELD);
    }
    printf("\n"); 
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData *clinic) {
    struct Date input_date;
    createDate(&input_date);
    printf("\n");
    displayScheduleTableHeader(&input_date, FMT_DATE_SPECIFIC);
    int i = 0; int n = 0; 
    struct Appointment matched_appointments[clinic->maxAppointments];
    // goes through appointments array to find appointments that match input date:
    for (i = 0; i < clinic->maxAppointments; ++i) {
        if (clinic->appointments[i].date.year == input_date.year && 
            clinic->appointments[i].date.month == input_date.month && 
            clinic->appointments[i].date.day ==  input_date.day) {
                matched_appointments[n] = clinic->appointments[i];
                ++n;
        }
    }
    // sorts the array of matched appointments based on time:
    int j;
    for (i = 0; i < n-1; i++) {     
       for (j = 0; j < n-i-1; j++) {
           if (matched_appointments[j].time.hour > matched_appointments[j+1].time.hour ||
               ((matched_appointments[j].time.hour == matched_appointments[j+1].time.hour) && 
                (matched_appointments[j].time.min > matched_appointments[j+1].time.min))) 
            { 
               swap(&matched_appointments[j].patientNumber, &matched_appointments[j+1].patientNumber);
               swap(&matched_appointments[j].time.hour, &matched_appointments[j+1].time.hour);
               swap(&matched_appointments[j].time.min, &matched_appointments[j+1].time.min);
           }
       }
    }
    // displays the appointments:
    int index;
    for (i = 0; i < n; ++i) {
        index = findPatientIndexByPatientNum(matched_appointments[i].patientNumber, clinic->patients, clinic->maxPatient);
        displayScheduleData(&clinic->patients[index], &matched_appointments[i], NO_DATE_FIELD);
    }
    printf("\n");
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointment_array, int appointment_limit, 
                    struct Patient* patient_array, int patient_limit) {
    int flag = 1; int flag2 = 1; int flag3 = 1;
    int length = 0; int index = 0;
    int taken = 0;
    // finds how many appointments there currently are:
    while(flag && length < appointment_limit) {
        if(appointment_array[length].patientNumber < 1) {
            flag = 0;
        }
        ++length;
    }
    // if there is no space print error, otherwise:
    if (length >= appointment_limit) {
        printf("ERROR: Appointment listing is FULL!\n\n");
    } else {
        index = length - 1; // this is where the new appointment will be stored
        printf("Patient Number: ");
        appointment_array[index].patientNumber = inputIntPositive();
        while(flag2) {
            createDate(&appointment_array[index].date); // validates a proper date:
            while(flag3) {
                createTime(&appointment_array[index].time); // takes user input for time
                if (validTime(appointment_array[index].time)) { // checks if time meets conditions
                    flag3 = 0;
                } else {
                    printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START, END, INTERVAL);
                }
            }
            taken = timeslotMatch(appointment_array, index); // check if that timeslot is taken
            if (taken) { // taken == 1 means timeslot not available
                printf("\nERROR: Appointment timeslot is not available!\n\n");
                flag3 = 1; // flag3 set to 1 means user will be asked to input time again
                taken = 0; // taken reset for next try
            } else {
                printf("\n*** Appointment scheduled! ***\n\n");
                flag2 = 0; // flag2 set to 0 means loop ends
            }
        }
    }
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointment_array, int appointment_limit, 
                    struct Patient* patient_array, int patient_limit) {
    int i;
    char select;
    // takes user input for a patient number
    printf("Patient Number: ");
    int input_number = inputIntPositive();
    int index = findPatientIndexByPatientNum(input_number, patient_array, patient_limit);
    if (index == -1) { 
        printf("ERROR: Patient record not found!\n\n");
    } else {
        // takes user input for a date
        struct Date input_date;
        createDate(&input_date);
        // iterates appointment_array to find matching date && see if its patientNumber matches input_number
        for (i = 0; i < appointment_limit; ++i) {
            if (appointment_array[i].date.year == input_date.year && 
                appointment_array[i].date.month == input_date.month && 
                appointment_array[i].date.day == input_date.day &&
                appointment_array[i].patientNumber == patient_array[index].patientNumber) {
                printf("\n");
                displayPatientData(&patient_array[index], FMT_FORM); // displays patient form
                printf("Are you sure you want to remove this appointment (y,n): ");
                select = inputCharOption("yn"); // makes user enter y or n
                if (select == 'y') {
                    appointment_array[i].patientNumber = 0;
                    printf("\nAppointment record has been removed!\n\n");
                } else {
                    printf("\nOperation aborted.\n\n");
                }
                clearInputBuffer();
            }
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// UTILITY FUNCTIONS /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// Search and display patient record by patient number (form) (from MS#2)
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

// Search and display patient records by phone number (tabular) (from MS#2)
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

// Get the next highest patient number (from MS#2)
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

// Find the patient array index by patient number (returns -1 if not found) (from MS#2)
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

// takes a Time and checks if it meets scheduling conditions
// i.e. if hour is end hour, min must be 0 OR hour must be <= start hour and < end hour
int validTime(const struct Time time) {
    int match = 0;
    if ((time.hour == END && time.min == 0) || (time.hour == START && time.hour == 0) || 
        ((START <= time.hour && time.hour < END) && (time.min % INTERVAL == 0))) {
            match = 1;
    }
    return match;
}

// takes an Appointment array and the index where the new appointment will go
// then iterates Appointment array to check if that date and time are already taken
// returns 1 if there is a match, and 0 otherwise
int timeslotMatch(const struct Appointment appointments[], int new_appointment_index) {
    int match = 0;
    int i;
    for (i = 0; i < new_appointment_index; ++i) {
        if (appointments[i].date.year == appointments[new_appointment_index].date.year &&
            appointments[i].date.month == appointments[new_appointment_index].date.month &&
            appointments[i].date.day == appointments[new_appointment_index].date.day &&
            appointments[i].time.hour == appointments[new_appointment_index].time.hour &&
            appointments[i].time.min == appointments[new_appointment_index].time.min) {
            match = 1;
        }
    }
    return match;
}

// sorts an array of appointments into chronological order
void sortAppointmentArray(struct Appointment *arr, int arr_length) {
    int i, j;
    for (i = 0; i < arr_length-1; ++i) {
        for (j = 0; j < arr_length-i-1; ++j) {
            if (arr[j].date.year == arr[j+1].date.year && 
                arr[j].date.month == arr[j+1].date.month &&
                arr[j].date.day == arr[j+1].date.day && 
                arr[j].time.hour > arr[j+1].time.hour) {
                swap(&arr[j].patientNumber, &arr[j+1].patientNumber);
                swap(&arr[j].time.hour, &arr[j+1].time.hour);
                swap(&arr[j].time.min, &arr[j+1].time.min);
                
            } else if (arr[j].date.year == arr[j+1].date.year &&
                       arr[j].date.month == arr[j+1].date.month &&
                       arr[j].date.day == arr[j+1].date.day &&
                       arr[j].time.hour == arr[j+1].time.hour &&
                       arr[j].time.min > arr[j+1].time.min) {
                swap(&arr[j].patientNumber, &arr[j+1].patientNumber);
                swap(&arr[j].time.min, &arr[j+1].time.min);
                
            } else if (arr[j].date.year == arr[j+1].date.year &&
                       arr[j].date.month == arr[j+1].date.month &&
                       arr[j].date.day > arr[j+1].date.day) {
                swap(&arr[j].patientNumber, &arr[j+1].patientNumber);
                swap(&arr[j].date.day, &arr[j+1].date.day);
                swap(&arr[j].time.hour, &arr[j+1].time.hour);
                swap(&arr[j].time.min, &arr[j+1].time.min);
            
            } else if (arr[j].date.year == arr[j+1].date.year &&
                       arr[j].date.month > arr[j+1].date.month) {
                swap(&arr[j].patientNumber, &arr[j+1].patientNumber);
                swap(&arr[j].date.month, &arr[j+1].date.month);
                swap(&arr[j].date.day, &arr[j+1].date.day);
                swap(&arr[j].time.hour, &arr[j+1].time.hour);
                swap(&arr[j].time.min, &arr[j+1].time.min);
            
            } else if (arr[j].date.year > arr[j+1].date.year) {
                swap(&arr[j].patientNumber, &arr[j+1].patientNumber);
                swap(&arr[j].date.year, &arr[j+1].date.year);
                swap(&arr[j].date.month, &arr[j+1].date.month);
                swap(&arr[j].date.day, &arr[j+1].date.day);
                swap(&arr[j].time.hour, &arr[j+1].time.hour);
                swap(&arr[j].time.min, &arr[j+1].time.min);
            }
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// USER INPUT FUNCTIONS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Get user input for a new patient record (from MS#2)
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n"
           "------------------\n"
           "Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 0, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information (from MS#2)
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
        inputPhoneNumber(phone->number, PHONE_LEN);
        clearInputBuffer();
        printf("\n");
    } else if (select == 2) {
        strcpy(phone->description, "HOME");
        printf("Contact: HOME\n"
               "Number : ");
        inputPhoneNumber(phone->number, PHONE_LEN);
        clearInputBuffer();
        printf("\n");
    } else if (select == 3) {
        strcpy(phone->description, "WORK");
        printf("Contact: WORK\n"
               "Number : ");
        inputPhoneNumber(phone->number, PHONE_LEN);
        clearInputBuffer();
        printf("\n");
    } else {
        strcpy(phone->description, "TBD");
    }
}

// takes user input and sets a valid date
void createDate(struct Date *date) {
    printf("Year        : ");
    date->year = inputIntRange(CURRENT_YEAR, CURRENT_YEAR + 5);
    printf("Month (1-12): ");
    date->month = inputIntRange(1, 12);
    int month_length = monthLength(date->month, date->year);
    printf("Day (1-%d)  : ", month_length);
    date->day = inputIntRange(1, month_length);
}

// takes user input and sets a valid time
void createTime(struct Time *time) {
    printf("Hour (0-23)  : "); 
    time->hour = inputIntRange(0, 23);
    printf("Minute (0-59): ");
    time->min = inputIntRange(0, 59);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// FILE FUNCTIONS //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max) {
    int count = 0;
    FILE *fp = fopen(datafile, "r");
    while ((fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]\n", &patients[count].patientNumber, patients[count].name, 
                                                patients[count].phone.description, patients[count].phone.number) != EOF) 
            && count != max) {
        ++count;
    }
    fclose(fp);
    return count;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    int count = 0;
    FILE *fp = fopen(datafile, "r");
    while ((fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[count].patientNumber, 
                                            &appoints[count].date.year, &appoints[count].date.month, &appoints[count].date.day, 
                                            &appoints[count].time.hour, &appoints[count].time.min) != EOF) 
            && (count != max)) {
        ++count;
    }
    fclose(fp);
    return count;
}