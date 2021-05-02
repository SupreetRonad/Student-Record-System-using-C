#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void newInfo();
void displayInfo();
void split_func(char str[], char dmt[], char arr[10][1000]);
void deleteRecord(char rollno[]);

//###################################################################################################################

void newInfo(){
	char name[30],rollno[15],dob[20],addr[1000],phno[13],cgpa[10];
	gets(name);
	printf("\n --- ENTER NEW STUDENT INFO ---\n");
	
	printf("\nEnter Roll No. : ");
	gets(rollno);
	
	printf("\nEnter Name : ");
	gets(name);
	
	printf("\nEnter DOB (dd/mm/yyyy) : ");
	gets(dob);
	
	printf("\nEnter CGPA : ");
	gets(cgpa);
	
	printf("\nEnter Contact No. : ");
	gets(phno);
	
	printf("\nEnter Address : ");
	gets(addr);
	
	FILE *fptr;
    fptr = fopen("std.txt", "a");
	
	//printf("\n%s;%s;%s;%s;%s;%s\n", rollno, name, dob, addr, phno, cgpa);
	fprintf(fptr, "%s;%s;%s;%s;%s;%s\n", rollno, name, dob, addr, phno, cgpa);	
	
	fclose(fptr);
	
	printf("\n	## Record added Successfully ## \n");
	printf("\nPress Any Key to Continue\n");
	_getch(); 
}

//###################################################################################################################

void displayInfo(){
	char line[2000], arr[10][1000];
		
	FILE *fptr;
    fptr = fopen("std.txt", "r");
	
	printf("\nRoll no.\tName\t\tContact no.\tCGPA\n");
	printf("------------------------------------------------------\n");
	
	while (fgets(line, sizeof(line), fptr)) {
		split_func(line, ";", arr);
		printf("\n%s\t%s\t%s\t%s", arr[0], arr[1], arr[4], arr[5]);
    }
	
	fclose(fptr);
	
	printf("\n");
	
	printf("\nPress Any Key to Continue\n");
	_getch();
}

//###################################################################################################################

void split_func(char str[], char dmt[], char arr[10][1000]){
	int i=0;
	
	char * token = strtok(str, dmt);
	while( token != NULL ){
		
		strcpy(arr[i],token); 
		
		token = strtok(NULL, dmt);
		i++;
	}
	
}

//###################################################################################################################

void displayRecord(){
	char line[2000], arr[10][1000], rollno[30];
	int flag=1;
	char c;
		
	FILE *fptr;
    fptr = fopen("std.txt", "r");
	
	printf("\n --- SEARCH RECORD --- \n");
	printf("\nEnter Roll no. : ");
	scanf("%s",rollno);
	
	system("cls");
	
	while (fgets(line, sizeof(line), fptr)) {
		split_func(line, ";", arr);
		if(!strcmp(arr[0],rollno)){
			printf("\n ### RECORD FOUND ### \n");
			
			printf("\nName\t : %s",arr[1]);
			printf("\nRoll no. : %s",arr[0]);			
			printf("\nDOB\t : %s",arr[2]);
			printf("\nContact\t : %s",arr[4]);
			printf("\nCGPA\t : %s",arr[5]);
			printf("Address\t : %s\n",arr[3]);
			
			flag = 0;
			break;
		}
    }
	
	fclose(fptr);
	
	if(flag == 1){
		printf("\n ### NO RECORD FOUND ###\n");
		printf("\nPress Any Key to Continue\n");
		_getch();
	}
	else{
		printf("\nPress \"D\" or \"d\" to delete, Any other key to go to main menu.\n");
		c = getch();
		if(c=='D' || c=='d'){
			int f=0;
			
			system("cls");			
			printf("\nConfirm Deletion ? (Y/n)");
			
			while(c = getch()){
				
				if(c=='Y' || c=='y'){
					deleteRecord(arr[0]);
					return ;
				}
				else if(c=='N' || c=='n'){
					return;
				}
				
				system("cls");			
				printf("\nConfirm Deletion ? (Y/n)");
			}
		}
	}
	
	
	
}

//###################################################################################################################

void deleteRecord(char rollno[]){
	char line[2000], tmp[2000], arr[10][1000];
	int flag=1;
		
	FILE *fptr;
    fptr = fopen("std.txt", "r");

	FILE *fptr1;
    fptr1 = fopen("std1.txt", "w");
	
	while (fgets(line, sizeof(line), fptr)) {
		strcpy(tmp, line);
		split_func(line, ";", arr);
		if(!strcmp(arr[0],rollno)){
			continue;
		}
		else{
			fputs(tmp, fptr1);
		}
    }
	
	fclose(fptr1);	
	fclose(fptr);
	
	
    fptr = fopen("std.txt", "w");
    fptr1 = fopen("std1.txt", "r");
	
	while (fgets(line, sizeof(line), fptr1)) {
		fputs(line, fptr);
    }
	
	fclose(fptr1);	
	fclose(fptr);
	
	printf("\n\n ### SUCCESSFULLY DELETED ### \n");
	printf("\nPress Any Key to Continue\n");
	_getch();
}

//###################################################################################################################

int main(){
	
	char c[5];
	while(strcmp(c,"4")!=0){
       
		printf("\n --- Choose an option --- \n");
		
		printf(" (1) TO ENTER NEW STUDENT INFO.\n");
		printf(" (2) TO DISPLAY ALL THE RECORDS\n");
		printf(" (3) TO SEARCH STUDENT RECORD ( INCLUDES DELETING A RECORD )\n");
		printf(" (4) TO EXIT\n\n-- ");

		scanf("%s",c);
     
		if(!strcmp(c,"1")){
			system("cls");
			newInfo();
			system("cls");
		}
		else if(!strcmp(c,"2")){
			system("cls");
			displayInfo();
			system("cls");
		}
		else if(!strcmp(c,"3")){
			system("cls");
			displayRecord();
			system("cls");
		}
		else if(!strcmp(c,"4")){
			system("cls");
			printf("\n## Exited ##\n");
		}
		else{
			system("cls");
			printf("\n !! Please enter a valid option !!\n");
		}
	}
}