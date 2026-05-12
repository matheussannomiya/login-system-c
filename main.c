#include <stdio.h>
#include <string.h>   
#include <stdlib.h>
#include <time.h>

#define TAM 31

typedef struct{
    char user[20];
    char password[20];
    int id;
}Data;

int load_txt(Data base[]);
void login(Data base[], int totalusers);
int registeer(Data base[], int totalusers);
void password_login(char correct_password[], Data base[], char user[]);
void syncToFile(Data new);
int hash(int key);
int hashString(char s[]);
void clearTable(Data member[]);
int idValidation(Data member[], int iduser);
void insertTable(Data member[], Data u);
Data *searchTable(Data member[], char user[]);

int main(){
    srand(time(NULL));
    Data member[TAM];
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

void login(Data base[], int totalusers){
    char username_typed[20];
    char password[20];
    char username[20];
    int flag = 0;

    printf("\nInsert your username: ");
    while(getchar() != '\n');
    fgets(username_typed, 20, stdin);
    username_typed[strcspn(username_typed, "\n")] = '\0';
    int index = hashString(username_typed);

    if(strcmp(username_typed, base[index].user) == 0){
        flag = 0;
        password_login(base[index].password, base, base[index].user);
    }else{
        printf("User not found\n");
    }

}

int registeer(Data base[], int totalusers){
    Data new;
    printf("\n********REGISTER********\n");

    do{
    printf("\nUser: ");
    while(getchar() != '\n');
    fgets(new.user, 20, stdin);
    new.user[strcspn(new.user, "\n")] = '\0';
    if(searchTable(base, new.user) != NULL)
        printf("Invalid username (already being used).\n");
    }while(searchTable(base, new.user) != NULL);
    
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

void password_login(char correct_password[], Data base[], char user[]){
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

int load_txt(Data base[]){
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

int hash(int key){
    return key % TAM;
}

int hashString(char s[]){
    int sizeS = strlen(s);
    unsigned int hash = 0;
    for(int i = 0; i < sizeS; i++)
        hash+= s[i] * (i+1);
    return hash % TAM;
}

void clearTable(Data member[]){
    for(int i = 0; i < TAM; i++){
        strcpy(member[i].user, "");
    }
}

void insertTable(Data member[], Data u){
    int id = hashString(u.user);
    /*while(strlen(member[id].user) > 0)
        id = hash(id + 1);*/
    member[id] = u;
}

int idValidation(Data member[], int iduser){
    for(int x = 0; x < TAM; x++){
        if(member[x].id == iduser)
            return 1;
    }
    return 0;
}

Data *searchTable(Data member[], char user[]){
    int index = hashString(user);

    if(strcmp(member[index].user, user) == 0)
        return &member[index];
    else{
        return NULL;
    }
    
}