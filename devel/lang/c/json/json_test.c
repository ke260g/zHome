#include<stdio.h>
#include<json.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

void json_object_foreach(json_object *jobj) {
    enum json_type type;
    struct array_list* arrlist;
    int i;
    json_object_object_foreach(jobj, key, val) {
        printf("type: ",type);
        type = json_object_get_type(val);
        printf("%s : " , key);
        switch (type) {
            case json_type_null:
                printf("null;\t");
                printf("json_type_null\n");
                //json_object_object_del(jobj, key);
                // json_object_object_add(jobj, key, json_object_new_string("null string"));
                break;
            case json_type_boolean:
                printf("%d;\t", json_object_get_boolean(val));
                printf("json_type_boolean\n");
                break;
            case json_type_double:
                printf("%lf;\t", json_object_get_double(val));
                printf("json_type_double\n");
                break;
            case json_type_int:
                printf("%d;\t", json_object_get_int(val));
                printf("json_type_int\n");
                break;
            case json_type_object:
                printf("{\n");
                json_object_foreach(val);
                printf("}\n");
                printf("json_type_object\n");
                break;
            case json_type_array:
                arrlist = json_object_get_array(val);
                printf("[");
                printf("]");
                printf("json_type_array\n");
                break;
            case json_type_string:
                printf("%s;\t", json_object_get_string(val));
                printf("json_type_string\n");
                break;
        }
    }
}

int entry_func(void) {
    int i;
    json_object * jobj;
        int fd = open("./test.json", O_RDONLY);
        int file_size = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        char *json_string = (char *)malloc(file_size);
        printf("#> malloc json_string: %p\n", json_string);
        read(fd, json_string, file_size);
        close(fd);
        // json_string[file_size] = '\0';
        // printf("%s", json_string);

        jobj = json_tokener_parse(json_string);
        free(json_string);
        printf("#> jobj returned from json_tokener_parse: %p\n", jobj);
        if(jobj == NULL)
            return -1;
        json_object_foreach(jobj);
        printf("=========\n");
        const char *new_json_string =
            json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PRETTY);
        printf("%s", new_json_string);
        json_object_put(jobj);
}

int main( int argc, char **argv ) {
    entry_func();
    return 0;
}
