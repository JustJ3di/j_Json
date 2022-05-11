#ifndef HSON
#define HSON


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

enum{
    OBJ_INT,
    OBJ_DOUBLE,
    OBJ_STRING,
    OBJ_JSON,
    OBJ_NULL,
    OBJ_BOOL,
    START //STAR LINKED :)
};

enum{
	ARRAY,
	SIMPLE,
	DICT
};

typedef struct json{

    char *key; // key for the dict object
    int type; // 8 byte
    struct json *next; //8 byte
    union{  
        int obj_int;
        double obj_double;
        char *obj_string;
        struct json *obj_json;
    };


}Json;

Json  *json_init();

void push_json_int(Json **head_ref, int value, char *eventualy_key);

void push_json_double(Json **head_ref, double value, char *eventualy_key);

void push_json_string(Json **head_ref, char *value, char *eventualy_key);

void push_json_bool(Json **head_ref, bool value, char *eventualy_key);

void push_json_null(Json **head_ref, char *eventualy_key);

void push_json_json(Json **head_ref, char *eventualy_key);

Json *json_parse(Json **head_ref, FILE *pr);





#endif