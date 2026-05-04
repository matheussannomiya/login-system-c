#include <stdio.h>
#include <string.h>   
#include <stdlib.h>

typedef struct{
    char user[20];
    char password[20];
}Data;

int load_txt(Data *base, int capacity);
void login(Data *base, int totalusers);
int registeer(Data **base, int totalusers, int *capacity);
void password_login(char correct_password[], Data *base, char user[]);
void syncToFile(Data *base, int totalusers);

int main(){
    int capacity = 100;
    Data *member = (Data*) malloc(capacity * sizeof(Data));
    int option = 0;
    int totalusers = load_txt(member, capacity);

    while(option != 3){
    printf("\n******WELCOME TO THE APP******\n");

    printf("1- Login | 2- Register | 3- Leave\n");
    scanf("%i", &option);

    switch(option){
        case 1: login(member, totalusers); break;
        case 2: totalusers = registeer(&member, totalusers, &capacity); 
                syncToFile(member, totalusers); break;
        case 3: break;
        default: printf("Insert a valid value\n"); break;
    }
}
    free(member);
    return 0;
}

void login(Data *base, int totalusers){
    char username_typed[20];
    char password[20];
    char username[20];
    int flag = 0;

    printf("\nInsert your username: ");
    while(getchar() != '\n');
    fgets(username_typed, 20, stdin);
    username_typed[strcspn(username_typed, "\n")] = '\0';

    for(int x = 0; x < totalusers; x++){
        if(strcmp(username_typed, base[x].user) == 0){
            flag = 0;
            password_login(base[x].password, base, base[x].user);
            break;
        }
        else{
            flag = -1;
        }
    }

    if(flag == -1){
        printf("User not found\n");
    }
    
}

int registeer(Data **base, int totalusers, int *capacity){
    int cap;
    printf("\n********REGISTER********\n");
    printf("\nUser: ");

    cap - *capacity;
    if(totalusers == cap){
        *capacity = (*capacity) * 2;
        cap = *capacity;
        Data *temp = realloc(*base, cap * sizeof(Data));
        if(temp == NULL){
            printf("\nRealocation error.\n");
        }
        *base = temp;
        temp = NULL;
    }

    while(getchar() != '\n');
    fgets((*base)[totalusers].user, 20, stdin);
    (*base)[totalusers].user[strcspn((*base)[totalusers].user, "\n")] = '\0';

    printf("\nPassword: ");
    fgets((*base)[totalusers].password, 20, stdin);
    (*base)[totalusers].password[strcspn((*base)[totalusers].password, "\n")] = '\0';
    totalusers++;
    

    return totalusers;
}

void password_login(char correct_password[], Data *base, char user[]){
    char password_typed[20];
    int tries = 0;

    FILE *log = fopen("datalog.txt", "a");

    while(tries < 3){
        printf("\nPassword: ");
        fgets(password_typed, 20, stdin);
        password_typed[strcspn(password_typed, "\n")] = '\0';
        if(strcmp(password_typed, correct_password) == 0){
            printf("\nWelcome Back %s!", user);
            fprintf(log, "%s logged\n", user);
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

int load_txt(Data *base, int capacity){
    FILE *file = fopen("datasystem.txt", "a+");

    if(file == NULL){
        printf("File error!\n");
    }

    int i = 0;

    while(i < capacity && fscanf(file, "%s %s", base[i].user, base[i].password) == 2){
        i++;
    }
    fclose(file);
    return i;
}

void syncToFile(Data *base, int totalusers){
    FILE *file = fopen("datasystem.txt", "a");

    if(file == NULL){
        printf("Sync to file error.\n");
    }

    fprintf(file,"%s %s\n", base[totalusers - 1].user, base[totalusers - 1].password);

    fclose(file);
}