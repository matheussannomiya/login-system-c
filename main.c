#include <stdio.h>
#include <string.h>   
#include <stdlib.h>
#include <time.h>
#include "hash.h"

int load_txt(Bucket base[]);
void login(Bucket base[], int totalusers);
int registeer(Bucket base[], int totalusers);
void password_login(char correct_password[], Data *base, char user[]);
void syncToFile(Data new);

int main(){
    srand(time(NULL));
    Bucket member[TAM];
    clearTable(member);
    
    int option = 0;
    int totalusers = load_txt(member);

    while(option != 3){
    printf("\n******WELCOME TO THE APP******\n");

    printf("1- Login | 2- Register | 3- Leave\n");
    scanf("%i", &option);

    switch(option){
        case 1: login(member, totalusers); break;
        case 2: totalusers = registeer(member, totalusers); 
                break;
        case 3: break;
        default: printf("Insert a valid value\n"); break;
    }
} 
    return 0;
}

void login(Bucket base[], int totalusers){
    char username_typed[20];
    char password[20];
    char username[20];
    Data *found;

    printf("\nInsert your username: ");
    while(getchar() != '\n');
    fgets(username_typed, 20, stdin);
    username_typed[strcspn(username_typed, "\n")] = '\0';
    found = searchTable(base, username_typed);

    if(found != NULL){
        password_login(found->password, found, found->user);
    }else{
        printf("User not found\n");
    }

}

int registeer(Bucket base[], int totalusers){
    Data new;
    printf("\n********REGISTER********\n");
    Data *result;

    do{
    printf("\nUser: ");
    while(getchar() != '\n');
    fgets(new.user, 20, stdin);
    new.user[strcspn(new.user, "\n")] = '\0';
    result = searchTable(base, new.user);
    if(result != NULL)
        printf("Invalid username (already being used).\n");
    }while(result != NULL);
    
    printf("\nPassword: ");
    fgets(new.password, 20, stdin);
    new.password[strcspn(new.password, "\n")] = '\0';   

    new.id = rand() % (9999 - 1000 + 1) + 1000;

    while(idValidation(base, new.id) == 1)
        new.id = rand() % (9999 - 1000 + 1) + 1000;

    insertTable(base, new);
    syncToFile(new);
    totalusers++;

    return totalusers;
}

void password_login(char correct_password[], Data *base, char user[]){
    char password_typed[20];
    int tries = 0;

    FILE *log = fopen("datalog.txt", "a");

    time_t now = 0;
    time(&now);

    struct tm *cur_time = localtime(&now);
    char s[100];

    strftime(s, 100, "%m-%d-%Y %H:%M:%S", cur_time);

    while(tries < 3){
        printf("\nPassword: ");
        fgets(password_typed, 20, stdin);
        password_typed[strcspn(password_typed, "\n")] = '\0';
        if(strcmp(password_typed, correct_password) == 0){
            printf("\nWelcome Back %s!", user);
            fprintf(log, "[%s] LOGIN SUCCESS | user: %s\n", s, user);
            tries = 0;
            break;
        }else{
            printf("\nWrong password.");
            tries++;
        }
    }
    
    if(tries != 0){
    printf("\nToo many failed attempts, try again later\n");
    }

    fclose(log);
}

int load_txt(Bucket base[]){
    Data aux;
    FILE *file = fopen("datasystem.txt", "a+");

    if(file == NULL){
        printf("File error!\n");
    }

    int i = 0;

    while(fscanf(file, "%s %s %i", &aux.user, &aux.password, &aux.id) == 3){
        insertTable(base, aux);
        i++;
    }
    fclose(file);
    return i;
}

void syncToFile(Data new){
    FILE *file = fopen("datasystem.txt", "a");

    if(file == NULL){
        printf("Sync to file error.\n");
    }

    fprintf(file,"%s %s %i\n", new.user, new.password, new.id);

    fclose(file);
}

