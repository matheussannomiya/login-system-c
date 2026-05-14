#ifndef TYPES_H
#define TYPES_H

typedef struct data{
    char user[20];
    char password[20];
    int id;
    struct data *next;
}Data;

typedef struct{
    Data *head;
}Bucket;

#endif