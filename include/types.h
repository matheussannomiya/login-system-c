#ifndef TYPES_H
#define TYPES_H

typedef struct data{
    char user[20];
    unsigned int password_hash;
    int id;
    struct data *next;
}Data;

typedef struct{
    Data *head;
}Bucket;

#endif