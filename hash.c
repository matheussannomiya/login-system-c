#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void clearTable(Bucket member[]){
    for(int i = 0; i < TAM; i++)
        clearList(&member[i]);
}

void insertTable(Bucket member[], Data u){
    int id = hashString(u.user);
    insertList(&member[id], u);
}

int idValidation(Bucket member[], int iduser){
    for(int x = 0; x < TAM; x++){
        Data *aux = member[x].head;
        while(aux != NULL && aux->id != iduser)
            aux = aux->next;
        if(aux != NULL)
            return 1;
    }
    return 0;
}

Data *searchTable(Bucket member[], char user[]){
    int index = hashString(user);
    return searchList(&member[index], user);
}

void clearList(Bucket *l){
    l->head = NULL;
}

void insertList(Bucket *l, Data user){
    Data *new = malloc(sizeof(Data));
    if(new != NULL){
        strcpy(new->user, user.user);
        strcpy(new->password, user.password);
        new->id = user.id;
        new->next = l->head;
        l->head = new;
    }else{
        printf("Malloc failed.\n");
    }
}

Data *searchList(Bucket *l, char user[]){
    Data *aux = l->head;
    while(aux != NULL && strcmp(aux->user, user) != 0)
        aux = aux->next;
    if(aux != NULL){
        return aux;
    }
    return NULL;
}
