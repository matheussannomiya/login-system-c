#include <stdio.h>
#include <string.h>   
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "hash.h"
#include "storage.h"


void login(Bucket base[], int totalusers);
int registeer(Bucket base[], int totalusers);
void password_login(unsigned int correct_hash, Data *base, char user[]);
void maskpassword(char *password);
unsigned int fnv1a(const char *str);

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
        password_login(found->password_hash, found, found->user);
    }else{
        printf("User not found\n");
    }

}

int registeer(Bucket base[], int totalusers){
    Data new;
    printf("\n********REGISTER********\n");
    Data *result;
    char password[20];

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
    maskpassword(password);
    password[strcspn(password, "\n")] = '\0';
    new.password_hash = fnv1a(password);   

    new.id = rand() % (9999 - 1000 + 1) + 1000;

    while(idValidation(base, new.id) == 1)
        new.id = rand() % (9999 - 1000 + 1) + 1000;

    insertTable(base, new);
    syncToFile(new);
    totalusers++;

    return totalusers;
}

void password_login(unsigned int correct_hash, Data *base, char user[]){
    char password_typed[20];
    unsigned int hash;
    int tries = 0;

    FILE *log = fopen("datalog.txt", "a");

    time_t now = 0;
    time(&now);

    struct tm *cur_time = localtime(&now);
    char s[100];

    strftime(s, 100, "%m-%d-%Y %H:%M:%S", cur_time);

    while(tries < 3){
        printf("\nPassword: ");
        maskpassword(password_typed);
        password_typed[strcspn(password_typed, "\n")] = '\0';
        hash = fnv1a(password_typed);

        if(hash == correct_hash){
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

void maskpassword(char *password){
    char ch;
    int i = 0;

    while(1){
        ch = getch();

        if(ch == 13){               // treating the enter (enter = 13)
            password[i] = '\0';
            break;
        }
        if(ch == 8){                // treating the backspace
            if(i > 0){                 
                i--;
                printf("\b \b");        // removing '*' from the terminal
            }
        }else{
            password[i] = ch;
            printf("*");
            i++;
        }
    }
}

unsigned int fnv1a(const char *str){        // basic crypto fnv-1a
    unsigned int hash = 2166136261u;        
    while(*str != '\0'){                        // while the last string's letter
        hash ^= (const char)*str;               //  bitwise XOR
        hash *= 16777619u;                      
        str++;                                  // next string's letter
    }
    return hash;                                
}