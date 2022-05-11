#ifndef HSON
#define HSON


#include <stdlib.h>
#include <string.h>

enum{
    OBJ_INT,
    OBJ_FLOAT,
    OBJ_STRING,
    OBJ_JSON,
    START //STAR LINKED :)
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

Json  *alloc(){

    Json *json = (Json *)malloc(sizeof(Json)*1000); //MAGIC NUMBER I NEED TO FIX IT
    if (json == NULL) //malloc failed
    {

        exit(EXIT_FAILURE);

    }
    

    //initialize value
    json->next = NULL;
    json->type = START; //magic number of init
    json->obj_string = NULL;

    return json;

}   

void push_json_int(Json **head_ref, int value, char *eventualy_key)
{

    Json *new_json = (*head_ref) + 1;
    //i need to append a memeorys'control
    
    new_json->obj_int = value;

    if (eventualy_key != NULL)
    {
        new_json->obj_string = (char *)malloc(strlen(eventualy_key) + 1);
        strcpy(new_json->key, eventualy_key);
    }
    else
        new_json->key = NULL;
    
    new_json->next = (*head_ref);

    (*head_ref) = new_json;

}

void push_json_double(Json **head_ref, double value, char *eventualy_key)
{

    Json *new_json = (*head_ref) + 1;
    //i need to append a memeorys'control
    
    
    new_json->obj_int = value;


    if (eventualy_key != NULL) //set a key if we need it!
    {
        new_json->obj_string = (char *)malloc(strlen(eventualy_key) + 1);
        strcpy(new_json->key, eventualy_key);
    }
    else
        new_json->key = NULL;
    

    new_json->next = (*head_ref);

    (*head_ref) = new_json;

}

void push_json_string(Json **head_ref, char *valyue)

#endif