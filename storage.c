#include "storage.h"
#include "types.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

int load_txt(Bucket base[]){
    Data aux;
    FILE *file = fopen("datasystem.txt", "a+");

    if(file == NULL){
        printf("File error!\n");
    }

    int i = 0;

    while(fscanf(file, "%s %s %i", aux.user, aux.password, &aux.id) == 3){
        insertTable(base, aux);
        i++;
    }
    fclose(file);
    return i;
}

void syncToFile(Data new_user){
    FILE *file = fopen("datasystem.txt", "a");

    if(file == NULL){
        printf("Sync to file error.\n");
    }

    fprintf(file,"%s %s %i\n", new_user.user, new_user.password, new_user.id);

    fclose(file);
}
