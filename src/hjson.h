#ifndef HSON
#define HSON


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

//initial size for the list or the dict(object)
#ifndef INITIAL_INIT_SIZE
    #define INITIAL_INIT_SIZE 100
#endif

//simple size for a value object
#ifndef SIMPLE_SIZE
    #define SIMPLE_SIZE 2
#endif




enum{
    OBJ_INT,
    OBJ_DOUBLE,
    OBJ_STRING,
    OBJ_JSON,
    OBJ_NULL,
    OBJ_BOOL,
	OBJ_DICT,
    OBJ_ARRAY,
    OBJ_SIMPLE
     //STAR LINKED :)
};


typedef struct json{

    char *key; // key for the dict object
    int type; // 8 byte
    struct json *next; //8 byte
    union{  
        int obj_int; //is also bool
        double obj_double;
        char *obj_string;
        struct json *obj_json; //new head 
    };


}Json;


void push_json_int(Json **head_ref, int value, char *eventualy_key);

void push_json_double(Json **head_ref, double value, char *eventualy_key);

void push_json_string(Json **head_ref, char *value, char *eventualy_key);

void push_json_bool(Json **head_ref, bool value, char *eventualy_key);

void push_json_null(Json **head_ref, char *eventualy_key);

void push_json_json(Json **head_ref, char *eventualy_key);


Json *json_parse(const char *, Json **);

void json_parse_value(Json **head_ref, FILE *pr, char first);

void json_parse_array(Json **head_ref, FILE *pr);

void json_parse_dict(Json **head_ref, FILE *pr);

void delete_json(Json **, Json **);



#endif