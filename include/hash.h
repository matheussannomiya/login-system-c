#ifndef HASH_H
#define HASH_H

#include "types.h"

#define TAM 31

int hash(int key);
int hashString(char s[]);

void clearTable(Bucket member[]);
void insertTable(Bucket member[], Data u);
int idValidation(Bucket member[], int iduser);
Data *searchTable(Bucket member[], char user[]);

void clearList(Bucket *l);
void insertList(Bucket *l, Data user);
Data *searchList(Bucket *l, char user[]);

#endif