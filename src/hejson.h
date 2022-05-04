#ifndef HESON
#define HESON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define DEBUG 1

//DEFINE THE BOOLEAN TYPE:
typedef enum {false,true}boolean;
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
typedef enum{
	INT,
	STRING,
	NULL_,
	BOOL,
	DOUBLE

}type_simple;
//type of generic object json
typedef enum{

	ARRAY,
	SIMPLE,
	DICT

}type_object;

//struct for the simple object
typedef struct{

	//type of the simple object (INT,STRING,NULL,DOUBLE)
	type_simple type;

	union{
		int obj_integer;
		char *obj_string;
		double obj_double;
		boolean obj_bool;
	};
	
}simple_obj;

//the array_object is doubled linked list of simple_object
typedef struct array_obj{

	type_object type;

	union{
		simple_obj element;
		struct array_obj *new_head;
		struct dict_obj *new_dict_head;
	};
	struct array_obj *next_element;
	struct array_obj *previous_element;

}Array;

//the dict_object is like array object but there is also a key
typedef struct dict_obj{

	type_object type;

	union{
		simple_obj element;
		Array *new_array;
		struct dict_obj *new_head;
	};
	
	struct dict_obj *next_element;
	struct dict_obj *previous_element;

	char key[];

}Dict;

//DEFINE THE ROOT OBJECT ! the parser working only with this !
typedef struct json{

	int type;
	
	union{

		simple_obj new_simple_object;
		struct array_obj *new_array;
		struct dict_obj *new_dict;

	};

}Json;

//alloc json type simple
Json *alloc_simple(int type);
//alloc array or dict
Json *alloc_struct_object(int type);


//METHOD FOR THE DICT OBJECT
Dict *push_on_dict_a_simple(Dict **head_dict , void *value , const char *key , int type);
Dict *push_on_dict_a_struct(Dict **head_dict , int type);

//METHOD FOR THE ARRAY OBJECT
Array *push_on_array_simple(Array **head_array , void *value , int type);
Array *push_on_array_a_struct(Array **head_array, int type);


//generic push;
void json_push_object_on_object(Json ** , int type_object , int type_simple , void *);


//DEALLOC OF JSON OBJECT
void dealloc(Json **);

//dealloc of dict object
void dealloc_dict(Dict **json_head_ref);

//dealloc of array object
void dealloc_array(Array **json_head_ref);

Json *Json_parse(const char *filename);

Json *parse_object(FILE *pr);

int Json_dump(FILE *pr,Json **);



#endif