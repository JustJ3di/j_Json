#ifndef HSON
#define HSON

/*

###############################################################


Copyright (c) 2022 Emanuele d'Ajello

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


  888888        888888  .d8888b.   .d88888b.  888b    888 
    "88b          "88b d88P  Y88b d88P" "Y88b 8888b   888 
     888           888 Y88b.      888     888 88888b  888 
     888           888  "Y888b.   888     888 888Y88b 888 
     888           888     "Y88b. 888     888 888 Y88b888 
     888 888888    888       "888 888     888 888  Y88888 
     88P           88P Y88b  d88P Y88b. .d88P 888   Y8888 
     888           888  "Y8888P"   "Y88888P"  888    Y888 
   .d88P         .d88P                                    
 .d88P"        .d88P"                                     
888P"         888P"                                       



################################################################

*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>

#define DEBUG 0

//simple size for a value object
#ifndef SIMPLE_SIZE
    #define SIMPLE_SIZE 2
#endif

//initial size for the list or the dict(object)
#ifndef INITIAL_INIT_SIZE
    #define INITIAL_INIT_SIZE 200
#endif

#ifndef INIT_SIZE_2
    #define INIT_SIZE_2 400 
#endif

#ifndef INIT_SIZE_3
    #define INIT_SIZE_3 800
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
};




typedef struct json{

    /*key for the dict object*/
    char *key; 
    int type; /* 8 byte */
    struct json *next; //8 byte
    int size; // 8 byte recod the size
    union{  
        int32_t obj_int; //is also bool
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
Json *json_parse_value(Json **head_ref, FILE *pr, char *first, char *key);
Json *json_parse_array(Json **head_ref, FILE *pr);
Json *json_parse_dict(Json **head_ref, FILE *pr);

void delete_json(Json **, Json **);
void delete_dict(Json **head);
void delete_array(Json **head);



void serialize(Json **head, FILE *);
void serialize_array(FILE *pr, Json *tail, int size);
void serialize_dict(FILE *pr, Json *tail, int size);


#endif
