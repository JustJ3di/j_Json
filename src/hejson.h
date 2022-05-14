#ifndef HESON
#define HESON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define DEBUG 1

//DEFINE THE BOOLEAN TYPE:
#include <stdbool.h>
/*
	I define the standard errors that a json parser can give me
*/

//OUT OF MEMORY ERROR
#define out_of_memory(){ \
	fprintf(stderr, "out memory in %s at line %d\n",__func__,__LINE__ );\
	exit(EXIT_FAILURE);\
}


//BAD token TO PARSE
#define parse_error(ch,pr){\
	fprintf(stderr, "value = (%s) is not possible to parse\n",ch);\
	fclose(pr);\
	exit(EXIT_FAILURE);\
}

//BAD CHAR TO PARSE
#define parse_char_error(ch,pr){ \
	fprintf(stderr, "value = (%c) is not possible to parse\n",ch);\
	fclose(pr); \
	exit(EXIT_FAILURE);\
}


/*
	Now I have to define the structure that will manage the parser.

*/

//type simple object
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
Json *json_parse_value(Json **head_ref, FILE *pr, char *first);
Json *json_parse_array(Json **head_ref, FILE *pr);
Json *json_parse_dict(Json **head_ref, FILE *pr);
void delete_json(Json **, Json **);




#endif