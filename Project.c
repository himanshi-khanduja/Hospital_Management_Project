#include <stdio.h>       
#include <stdlib.h>      
#include <string.h>      
#include <ctype.h>       

#define MAX_DEPARTMENTS 7
#define MAX_DOCTORS 7
#define MAX_BED_TYPES 7
#define MAX_NURSES 6
#define MAX_PATIENTS 50  // Updated maximum number of patients
#define MAX_NAME_LEN 100  

typedef struct {
    char name[MAX_NAME_LEN];            
    char specialization[MAX_NAME_LEN];  
} Doctor;

typedef struct {
    char type[MAX_NAME_LEN];        
    char priceRange[MAX_NAME_LEN];  
    int minPrice;                   
    int availableBeds;              
} BedType;

typedef struct {
    char name[MAX_NAME_LEN];        
    char contactInfo[MAX_NAME_LEN]; 
} Nurse;

typedef struct {
    char name[MAX_NAME_LEN];        
    char gender[2];                 
    int age;                        
    char illness[MAX_NAME_LEN];     
    char diagnoses[MAX_NAME_LEN];   
} Patient;

typedef struct {
    char name[MAX_NAME_LEN];            
    char location[MAX_NAME_LEN];        
    char contact[MAX_NAME_LEN];         
    char departments[MAX_DEPARTMENTS][MAX_NAME_LEN];  
    Doctor doctors[MAX_DOCTORS];        
    BedType beds[MAX_BED_TYPES];        
    struct {                            
        char nurseHeadName[MAX_NAME_LEN];   
        char nurseHeadContact[MAX_NAME_LEN]; 
        Nurse nurses[MAX_NURSES];           
    } staff;
    Patient patients[MAX_PATIENTS];     
    int patientCount;   // Track the number of patients
} Hospital;

void initializeHospital(Hospital *hospital);           
void printHospitalData(const Hospital *hospital);      
void printDepartments(const Hospital *hospital);       
void printDoctors(const Hospital *hospital);           
void printBeds(const Hospital *hospital);              
void printStaff(const Hospital *hospital);             
void printPatients(const Hospital *hospital);          
void sortBedsByPrice(BedType beds[], int n);           
void sortBedsByAvailableBeds(BedType beds[], int n);   
void sortPatientsByName(Patient patients[], int n);    
void addPatientDetails(Hospital *hospital);            
int extractMinPrice(const char *priceRange);           
int strcasecmp(const char *a, const char *b);          

void initDoctor(Doctor *doctor, const char *name, const char *specialization) {
    strcpy(doctor->name, name);               
    strcpy(doctor->specialization, specialization); 
}

void initBedType(BedType *bed, const char *type, const char *priceRange, int availableBeds) {
    strcpy(bed->type, type);                   
    strcpy(bed->priceRange, priceRange);       
    bed->minPrice = extractMinPrice(priceRange); 
    bed->availableBeds = availableBeds;        
}

void initPatient(Patient *patient, const char *name, const char *gender, int age, const char *illness, const char *diagnoses) {
    strcpy(patient->name, name);               
    strcpy(patient->gender, gender);           
    patient->age = age;                        
    strcpy(patient->illness, illness);         
    strcpy(patient->diagnoses, diagnoses);     
}

void initNurse(Nurse *nurse, const char *name, const char *contactInfo) {
    strcpy(nurse->name, name);                
  
}

int main() {
    Hospital hospital;   
    int choice;          

    initializeHospital(&hospital);  

    do {
        printf("\nPlease select an option:\n");
        printf("1. Hospital Data\n");
        printf("2. View Patient Data\n");
        printf("3. Add Patient\n");
        printf("4. Sort by Bed Price\n");
        printf("5. Sort by Available Beds\n");
        printf("6. Sort by Patient Name\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);  

        switch (choice) {
            case 1: printHospitalData(&hospital); break;
            case 2: printPatients(&hospital); break;      
            case 3: addPatientDetails(&hospital); break;  
            case 4: sortBedsByPrice(hospital.beds, MAX_BED_TYPES); printBeds(&hospital); break; 
            case 5: sortBedsByAvailableBeds(hospital.beds, MAX_BED_TYPES); printBeds(&hospital); break;
            case 6: sortPatientsByName(hospital.patients, hospital.patientCount); printPatients(&hospital); break; 
            case 7: printf("Exiting...\n"); break;        
            default: printf("Invalid choice, please try again.\n"); 
        }
    } while (choice != 7);  

    return 0;  
}

void initializeHospital(Hospital *hospital) {
    strcpy(hospital->name, "Rajiv Gandhi Cancer Institute and Research Centre");  
    strcpy(hospital->location, "Delhi - 110085");                                
    strcpy(hospital->contact, "011-28456311");                                   

    const char *departments[] = {"Cardiology", "Gastroenterology", "Gynaecology", "Neurology", "Orthopedics", "Dermatology", "Hematology"};
    const char *doctorNames[] = {"Dr. Nishant Rao", "Dr. Jaspreet Singh", "Dr. Khushboo Sharma", "Dr. Naveen Mukhi", "Dr. Nisha", "Dr. Jahangir Khan", "Dr. Aditi"};
    const char *specializations[] = {"Cardiology", "Gastroenterology", "Gynaecology", "Neurology", "Orthopedics", "Dermatology", "Hematology"};

    const char *bedTypes[] = {"ICU Bed", "Luxury Bed", "Low Bed", "Maternity Bed", "Standard Bed", "Premium Bed", "Economic Bed"};
    const char *priceRanges[] = {"INR 7,000 - INR 25,000 per day", "INR 7,000 - INR 20,000+ per day", "INR 2,000 - INR 5,000 per day", "INR 3,000 - INR 10,000 per day", "INR 500 - INR 2,000 per day", "INR 5,000 - INR 15,000 per day", "INR 300 - INR 500 per day"};
    int availableBeds[] = {3, 5, 2, 7, 10, 8, 15};

    const char *nurseHeadName = "Kritika Rathore";
    const char *nurseHeadContact = "+91-8456149624";

    const char *nurseNames[] = {"Sunita Verma", "Upasna Arora", "Nitin", "Kalpesh", "Shama", "Himesh"};

    const char *patientNames[] = {"Ankit", "Monu", "Sonu", "Deepak", "Piyush", "Tanisha", "Poonam", "Jaya", "Anshika"};
    const char *genders[] = {"M", "M", "M", "M", "M", "F", "F", "F", "F"};
    int ages[] = {34, 45, 31, 43, 37, 55, 28, 29, 40};
    const char *illnesses[] = {"Arthritis", "High Blood Pressure", "High BP", "Diabetes", "Hepatitis", "Arthritis", "High BP", "Diabetes", "High BP"};
    const char *diagnoses[] = {"CT Scan", "X-ray", "Sugar Test", "X-ray", "MRI", "CT Scan", "Sugar Test", "X-ray", "CT Scan"};

    for (int i = 0; i < MAX_DEPARTMENTS; i++) strcpy(hospital->departments[i], departments[i]);
    for (int i = 0; i < MAX_DOCTORS; i++) initDoctor(&hospital->doctors[i], doctorNames[i], specializations[i]);
    for (int i = 0; i < MAX_BED_TYPES; i++) initBedType(&hospital->beds[i], bedTypes[i], priceRanges[i], availableBeds[i]);

    hospital->patientCount = 0;  // Initialize patient count to zero
    for (int i = 0; i < 9; i++) {
        initPatient(&hospital->patients[i], patientNames[i], genders[i], ages[i], illnesses[i], diagnoses[i]);
        hospital->patientCount++;  // Increment patient count
    }

    strcpy(hospital->staff.nurseHeadName, nurseHeadName);  
    strcpy(hospital->staff.nurseHeadContact, nurseHeadContact);  

    for (int i = 0; i < MAX_NURSES; i++) initNurse(&hospital->staff.nurses[i], nurseNames[i], "+91-XXXXXXXXXX"); // Placeholder contact info
}

void printHospitalData(const Hospital *hospital) {
    printf("\nHospital Name: %s\nLocation: %s\nContact: %s\n", hospital->name, hospital->location, hospital->contact);
    printDepartments(hospital);  
    printDoctors(hospital);      
    printBeds(hospital);         
    printStaff(hospital);        
}

void printDepartments(const Hospital *hospital) {
    printf("\nDepartments:\n");
    for (int i = 0; i < MAX_DEPARTMENTS; i++) printf("%s\n", hospital->departments[i]);
}

void printDoctors(const Hospital *hospital) {
    printf("\nDoctors:\n");
    for (int i = 0; i < MAX_DOCTORS; i++) {
        printf("%s - %s\n", hospital->doctors[i].name, hospital->doctors[i].specialization);
    }
}

void printBeds(const Hospital *hospital) {
    printf("\nBeds:\n");
    for (int i = 0; i < MAX_BED_TYPES; i++) {
        printf("%s - %s, Available: %d\n", hospital->beds[i].type, hospital->beds[i].priceRange, hospital->beds[i].availableBeds);
    }
}

void printStaff(const Hospital *hospital) {
    printf("\nNurse Head: %s, Contact: %s\n", hospital->staff.nurseHeadName, hospital->staff.nurseHeadContact);
    printf("Nurses:\n");
    for (int i = 0; i < MAX_NURSES; i++) {
        printf("%s\n", hospital->staff.nurses[i].name, hospital->staff.nurses[i].contactInfo);
    }
}

void printPatients(const Hospital *hospital) {
    printf("\nPatients:\n");
    for (int i = 0; i < hospital->patientCount; i++) {
        printf("%s (%s, %d years) - Illness: %s, Diagnosis: %s\n", 
            hospital->patients[i].name, 
            hospital->patients[i].gender, 
            hospital->patients[i].age, 
            hospital->patients[i].illness, 
            hospital->patients[i].diagnoses);
    }
}

void sortBedsByPrice(BedType beds[], int n) {
    // Sort beds by minimum price (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (beds[j].minPrice > beds[j + 1].minPrice) {
                BedType temp = beds[j];
                beds[j] = beds[j + 1];
                beds[j + 1] = temp;
            }
        }
    }
}

void sortBedsByAvailableBeds(BedType beds[], int n) {
    // Sort beds by available beds (descending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (beds[j].availableBeds < beds[j + 1].availableBeds) {
                BedType temp = beds[j];
                beds[j] = beds[j + 1];
                beds[j + 1] = temp;
            }
        }
    }
}

void sortPatientsByName(Patient patients[], int n) {
    // Sort patients by name (alphabetical order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcasecmp(patients[j].name, patients[j + 1].name) > 0) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }
}

void addPatientDetails(Hospital *hospital) {
    if (hospital->patientCount < MAX_PATIENTS) {
        Patient newPatient;
        printf("Enter patient name: ");
        scanf(" %[^\n]%*c", newPatient.name);
        printf("Enter gender (M/F): ");
        scanf(" %1s", newPatient.gender);
        printf("Enter age: ");
        scanf("%d", &newPatient.age);
        printf("Enter illness: ");
        scanf(" %[^\n]%*c", newPatient.illness);
        printf("Enter diagnoses: ");
        scanf(" %[^\n]%*c", newPatient.diagnoses);
        
        hospital->patients[hospital->patientCount] = newPatient;
        hospital->patientCount++;  // Increment the patient count
        printf("Patient added successfully!\n");
    } else {
        printf("Patient limit reached. Cannot add more patients.\n");
    }
}

int extractMinPrice(const char *priceRange) {
    int minPrice = 0;
    sscanf(priceRange, "INR %d", &minPrice);  // Extract the minimum price
    return minPrice;
}

int strcasecmp(const char *a, const char *b) {
    while (*a && *b && tolower((unsigned char)*a) == tolower((unsigned char)*b)) {
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}
