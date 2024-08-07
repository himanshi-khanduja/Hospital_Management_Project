#include <stdio.h>
#include <stdbool.h> // Include the library for the boolean type (true/false)
#include <string.h> // Include the library for string functions

// Define the structure for hospital data
struct Hospital 
{
    char name[100];
    char place[100];
    int available_beds;
    float bed_price;
    float ratings;
    char review[200];
};

#define NAME_LEN 100
#define MAX_PATIENTS 5

typedef struct 
{
    char name[NAME_LEN];
    int age;
    char gender;
    char illness[NAME_LEN];
} Patient;

#define NUMBER_OF_HOSPITALS 5

// Function to sort hospitals by bed price in descending order
void sortByPrice(struct Hospital hospitals[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        bool flag = false;
        for (int j = 0; j < n - 1 - i; j++) 
        {
            if (hospitals[j].bed_price < hospitals[j + 1].bed_price) 
            {
                struct Hospital temp = hospitals[j];
                hospitals[j] = hospitals[j + 1];
                hospitals[j + 1] = temp;
                flag = true;
            }
        }
        if (!flag) 
        {
            break;
        }
    }
}

// Function to sort hospitals by available beds in descending order
void sortByBeds(struct Hospital hospitals[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        bool flag = false;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (hospitals[j].available_beds < hospitals[j + 1].available_beds) 
            {
                struct Hospital temp = hospitals[j];
                hospitals[j] = hospitals[j + 1];
                hospitals[j + 1] = temp;
                flag = true;
            }
        }
        if (!flag) 
        {
            break;
        }
    }
}

// Function to sort hospitals by rating in descending order
void sortByRating(struct Hospital hospitals[], int size) 
{
    for (int i = 0; i < size - 1; i++) 
    {
        for (int j = i + 1; j < size; j++) {
            if (hospitals[i].ratings < hospitals[j].ratings) 
            {
                struct Hospital temp = hospitals[i];
                hospitals[i] = hospitals[j];
                hospitals[j] = temp;
            }
        }
    }
}

// Function to print hospital data
void hospital_data(int index, struct Hospital hospital) 
{
    printf("%d. Name: %s, Place: %s, Available Beds: %d, Bed's Price: %.2f, Ratings: %.1f  \n\tReview: %s\n",
           index, hospital.name, hospital.place, hospital.available_beds, hospital.bed_price, hospital.ratings, hospital.review);
}

int main() 
{
    // Create an array of structures to hold data for multiple hospitals
    struct Hospital hospitals[NUMBER_OF_HOSPITALS] = 
    {
        {"Rajiv Gandhi Cancer Institute and Research Centre", "Delhi", 100, 2000.0, 4.5, "The facility was spotless and well-maintained.\n"},
        {"Apollo Hospitals", "Chennai", 80, 1000.0, 4.0, "Friendly and efficient staff.\n"},
        {"Kokilaben Dhirubhai Ambani Hospital", "Mumbai", 105, 2500.0, 5.0, "Compassionate and attentive doctors.\n"},
        {"Fortis Memorial Research Institute", "Gurgaon", 50, 1500.0, 3.0, "The staff was dismissive and unhelpful.\n"},
        {"Manipal Hospital", "Bangalore", 20, 1200.0, 4.3, "The hospital utilizes advanced technology and equipment.\n"}
    };

    Patient patients[MAX_PATIENTS] = 
    {
        {"Simran", 23, 'F', "Flu"},
        {"Aayush", 25, 'M', "Cold"},
        {"Amit", 40, 'M', "Asthma"},
        {"Rina", 25, 'F', "Cough"},
        {"Rohan", 23, 'M', "Fever"}
    };

    // Print hospital data
    printf("\n                 Hospital Data\n\n");
    for (int i = 0; i < NUMBER_OF_HOSPITALS; i++) 
    {
        hospital_data(i + 1, hospitals[i]); // Print each hospital's data with numbering
    }

    // Print patient data
    printf("\n                 Patients' Details\n\n");
    for (int i = 0; i < MAX_PATIENTS; i++) 
    {
        printf("%d. Name: %s, Age: %d, Gender: %c, Illness: %s\n",
               i + 1, patients[i].name, patients[i].age, patients[i].gender, patients[i].illness);
    }

    // Sort by bed price
    sortByPrice(hospitals, NUMBER_OF_HOSPITALS);
    printf("\n                 Sort by Bed's Price\n\n");
    for (int i = 0; i < NUMBER_OF_HOSPITALS; i++) 
    {
        hospital_data(i + 1, hospitals[i]); // Print each hospital's data with numbering after sorting by bed price
    }

    // Sort by available beds
    sortByBeds(hospitals, NUMBER_OF_HOSPITALS);
    printf("\n                 Sort by Available Beds\n\n");
    for (int i = 0; i < NUMBER_OF_HOSPITALS; i++) 
    {
        hospital_data(i + 1, hospitals[i]); // Print each hospital's data with numbering after sorting by available beds
    }

    // Sort patients by name
    Patient temp;
    for (int i = 0; i < MAX_PATIENTS - 1; i++) 
    {
        for (int j = i + 1; j < MAX_PATIENTS; j++) 
        {
            if (strcmp(patients[i].name, patients[j].name) > 0) 
            {
                temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }

    // Print sorted patient data
    printf("\n            Sort by Patient's Name\n\n");
    for (int i = 0; i < MAX_PATIENTS; i++) 
    {
        printf("%d. Name: %s, Age: %d, Gender: %c, Illness: %s\n",
               i + 1, patients[i].name, patients[i].age, patients[i].gender, patients[i].illness);
    }

    // Sort by rating
    sortByRating(hospitals, NUMBER_OF_HOSPITALS);
    printf("\n            Sort by Ratings and Reviews\n\n");
    for (int i = 0; i < NUMBER_OF_HOSPITALS; i++) 
    {
        hospital_data(i + 1, hospitals[i]);
    }

    return 0; // Return 0 to indicate successful execution
}
