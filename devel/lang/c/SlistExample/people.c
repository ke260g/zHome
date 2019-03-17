#include<stdarg.h>
#include<string.h>

#include"people.h"
#include"slist.h"

People *PeopleNew(const int high,
        const int weight,
        char *name){
    People *new = (People *)malloc(sizeof(People));
    new->high = high;
    new->weight = weight;
    new->name = name;
    return new;
}

void PeopleDestroy(void *people){
    free(people);
}

int find_people_by_name(void *data, const void *attribute) {
    char *target_name = (char *)attribute;
    People *target_people = (People *)data;

    if(strcmp(target_people->name, target_name) == 0){
        return 0; /* successfully find */
    }
    else{
        return -1;
    }
}

void display_people(void *data){
    if(data == NULL)
        fprintf(stderr, "invalid people input, can't display\n");
    People *people = (People *)data;
    printf("[ name   :: %s\n", people->name);
    printf("  high   :: %d\n", people->high);
    printf("  weight :: %d  ]\n\n", people->weight);
}
