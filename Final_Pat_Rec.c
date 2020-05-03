#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define NULL 0

long int create_PatientID();

void display_Menu(int*);

void add_Patient(FILE*);

void check_Rec(FILE*);

void update_Rec(FILE*);

void delete_Rec(FILE*);

void search_Rec(FILE*);

typedef struct{
	int day;
	int month;
	int year;
}date;

struct record{
	int patientID;
	char name[30];
	int age;
	char department[30];
	date admission_date;
}; 

int main()
{
	FILE *fptr;
	int user_Choice= NULL;
	int rec_Choice=1;
	
	do{
		printf("Enter 1 for old records \n");
		printf("Enter 2 for new records \n");
		scanf("%d", &rec_Choice);
		
		if (rec_Choice==1){
			fptr=fopen("patient_records.txt", "a+");
			break;}
		else if (rec_Choice==2){
			fptr=fopen("new_records.txt", "a+");
			break;}
		else{
			printf("Please try again\n");
		}	
	}while (1);
	
	display_Menu(&user_Choice);
	
	switch(user_Choice){
		case 1:
			add_Patient(fptr);
			break;
		case 2:
			check_Rec(fptr);
			break;
		case 3:
			update_Rec(fptr);
			break;
		case 4:
			delete_Rec(fptr);
			break;
		case 5:
			search_Rec(fptr);
			break;
		case 6:
			return 0;
		default:
			printf("Please try again ");
	}
	fclose(fptr);	
}

void display_Menu(int* user_Choice)
{
    printf("*****WELCOME TO THE HOSPITAL MANAGEMENT SYSTEM*****\n");
    printf("1. Add New Patient\n");
    printf("2. Check Existing Records\n");
    printf("3. Update Existing Records\n");
    printf("4. Delete Record\n");
    printf("5. Search Records\n");
    printf("6. Exit\n");
    printf("Enter Your Choice: ");

    scanf("%d", user_Choice);
	
	int i;
    for (i = 0; *user_Choice > 6; ++i) {
        printf("Invalid input, please try again  ");
        scanf("%d", user_Choice);
    }
}

void add_Patient(FILE *fptr)
{
    struct record new_Patient;
    new_Patient.patientID = create_PatientID();
    
	printf("Name: ");
    fflush(stdin);
	gets(new_Patient.name);
    
    printf("Age: ");
    scanf("%d", &new_Patient.age);
    
    printf("Department:  ");
    fflush(stdin);
	gets(new_Patient.department);
    
    printf("Date of admission(dd/mm/yy): ");
    scanf("%d/%d/%d", &new_Patient.admission_date.day,&new_Patient.admission_date.month,&new_Patient.admission_date.year);

    fwrite(&new_Patient,sizeof(new_Patient),1,fptr);
    
	printf("Assigned PatientID: %ld", new_Patient.patientID);
}

void check_Rec(FILE *fptr)
{
    struct record recorded_Patient;

    while (!feof(fptr)){
        fread(&recorded_Patient, sizeof(recorded_Patient), 1, fptr);
            printf("PatientID: %ld\n", recorded_Patient.patientID);
            printf("Name: %s\n", recorded_Patient.name);
            printf("Age: %d\n", recorded_Patient.age);
            printf("Department: %s\n", recorded_Patient.department);
            printf("Admitted Date: %d/%d/%d\n", recorded_Patient.admission_date.day, recorded_Patient.admission_date.month,
                   recorded_Patient.admission_date.year);
        }
}

long int create_PatientID(){
    //Creates random integer using current time as the initial seed
    //Returned Random int can be changed accordingly depending on the size of the hospital
    srand(time(NULL));
    return rand()%20;
};

void update_Rec(FILE *fptr)
{
    struct record recorded_Patient;
    char search_name[30];

    printf("Enter the name: ");
    scanf("%s",search_name);

    fread(&recorded_Patient, sizeof(recorded_Patient),1,fptr);

    while (!feof(fptr)){
        fread(&recorded_Patient, sizeof(recorded_Patient), 1, fptr);
        
		if (strcmp(search_name, recorded_Patient.name) == 0 ) {
            printf("*******CURRENT INFORMATION*******");
            printf("PatientID: %ld\n", recorded_Patient.patientID);
            printf("Name: %s\n", recorded_Patient.name);
            printf("Age: %d\n", recorded_Patient.age);
            printf("Department: %s\n", recorded_Patient.department);
            printf("Admitted Date: %d/%d/%d\n", recorded_Patient.admission_date.day, recorded_Patient.admission_date.month,
                   recorded_Patient.admission_date.year);
            break;
        }
    }
	
	printf("-----ENTER NEW INFORMATION------");
   	printf("Age: ");
    scanf("%d", &recorded_Patient.age);
    
    printf("Department:  ");
    fflush(stdin);
	gets(recorded_Patient.department);

    fwrite(&recorded_Patient, sizeof(recorded_Patient), 1, fptr);
}

void search_Rec(FILE *fptr)
{
    int found=0;
    struct record recorded_Patient;
    char search_name[30];

    printf("Enter the name: ");
    scanf("%s",search_name);

    while (!feof(fptr)){
        fread(&recorded_Patient, sizeof(recorded_Patient), 1, fptr);
        if (strcmp(search_name, recorded_Patient.name) == 0 ) {
            found = 1;
             printf("PatientID: %ld\n", recorded_Patient.patientID);
            printf("Name: %s\n", recorded_Patient.name);
            printf("Age: %d\n", recorded_Patient.age);
            printf("Department: %s\n", recorded_Patient.department);
            printf("Admitted Date: %d/%d/%d\n", recorded_Patient.admission_date.day, recorded_Patient.admission_date.month,
                   recorded_Patient.admission_date.year);
        }
    }
    if (!found)
        printf("Sorry, No Record Found");
}

void delete_Rec(FILE *fptr){
    FILE *fptr_new;
    fptr_new = fopen("new_records.txt","a");
    struct record recorded_Patient;
    char search_name[30];

    printf("Enter the name: ");
    scanf("%20s",search_name);

    while (!feof(fptr)){
        fread(&recorded_Patient, sizeof(recorded_Patient), 1, fptr);
        if (strcmp(search_name, recorded_Patient.name) != 0 ) {
            fwrite(&recorded_Patient,sizeof(recorded_Patient),1,fptr_new);
        }
    }

    fclose(fptr_new);
}









