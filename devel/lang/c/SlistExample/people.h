#include"slist.h"
#include<stdarg.h>
#include<string.h>

typedef struct _People {
    int high;
    int weight;
    char *name;
} People;


People *PeopleNew(const int high,
        const int weight,
        char *name);
void PeopleDestroy(void *people);

enum {People_Attribute_Weight, People_Attribute_Height, People_Attribute_Name};

int find_people_by_name(void *data, const void *attribute);
void display_people(void *data);
