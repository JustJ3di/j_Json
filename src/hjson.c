#include "hjson.h"


Json  *json_init(){

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
    
    //set the value
    new_json->obj_int = value;

    new_json->type = OBJ_INT;

    if (eventualy_key != NULL)
    {
        new_json->key = (char *)malloc(strlen(eventualy_key) + 1);
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
    
    //set_the value
    new_json->obj_double = value;

    new_json->type = OBJ_DOUBLE;

    if (eventualy_key != NULL) //set a key if we need it!
    {
        new_json->key = (char *)malloc(strlen(eventualy_key) + 1);
        strcpy(new_json->key, eventualy_key);
    }
    else
        new_json->key = NULL;
    

    new_json->next = (*head_ref);

    (*head_ref) = new_json;

}

void push_json_string(Json **head_ref, char *value, char *eventualy_key)
{

    Json *new_json = (*head_ref) + 1;
    //i need to append a memeorys'control
    
    //set_the value
    new_json->obj_string = (char *)malloc(strlen(value) + 1);
    if (new_json->obj_string == NULL)
    {
        exit(EXIT_FAILURE);
    }

    strcpy(new_json->obj_string,value);

    new_json->type = OBJ_STRING;
    

    if (eventualy_key != NULL) //set a key if we need it!
    {
        new_json->key = (char *)malloc(strlen(eventualy_key) + 1);
        if(new_json->key == NULL)exit(EXIT_FAILURE);
        
        strcpy(new_json->key, eventualy_key);
    }
    else
        new_json->key = NULL;
    

    new_json->next = (*head_ref);

    (*head_ref) = new_json;


}

void push_json_bool(Json **head_ref, bool value, char *eventualy_key)
{

    Json *new_json = (*head_ref) + 1;
    //i need to append a memeorys'control
    
    //set_the value
    new_json->obj_int = value;

    new_json->type = OBJ_BOOL;


    if (eventualy_key != NULL) //set a key if we need it!
    {
        new_json->key = (char *)malloc(strlen(eventualy_key) + 1);
        strcpy(new_json->key, eventualy_key);
    }
    else
        new_json->key = NULL;
    

    new_json->next = (*head_ref);

    (*head_ref) = new_json;

}

void push_json_null(Json **head_ref, char *eventualy_key)
{

    Json *new_json = (*head_ref) + 1;
    //i need to append a memeorys'control
    
    //set_the value

    new_json->type = OBJ_NULL;


    if (eventualy_key != NULL) //set a key if we need it!
    {
        new_json->key = (char *)malloc(strlen(eventualy_key) + 1);
        strcpy(new_json->key, eventualy_key);
    }
    else
        new_json->key = NULL;
    

    new_json->next = (*head_ref);

    (*head_ref) = new_json;

}


void push_json_json(Json **head_ref, char *eventualy_key)
{

    Json *new_json = (*head_ref) + 1;
    //i need to append a memeorys'control
    
    //start new linked list
    new_json->obj_json = NULL;

    new_json->type = OBJ_JSON;


    if (eventualy_key != NULL) //set a key if we need it!
    {
        new_json->key = (char *)malloc(strlen(eventualy_key) + 1);
        strcpy(new_json->key, eventualy_key);
    }
    else
        new_json->key = NULL;
    

    new_json->next = (*head_ref);

    (*head_ref) = new_json;

}


void json_parse(Json **head_ref, FILE *pr)
{

    char c = fgetc(pr);
    char *token = malloc(5000);


    while(isspace(c))
        c = fgetc(pr);
    
    if (c == 'n') // parse null
    {
        token[0] = c; // token[0] = 'n';
        for (size_t i = 1; i < 4; i++)
        {
            token[i] = fgetc(pr);
        }
        token[4] ='\0';
        push_json_null(head_ref, NULL);
    }    
    else if(c== 't' || c== 'f')//parse boolean
    {
        

    }else if (c == '"') // parse string
    {

    }
    else if(c == '[') // parse array
    {

    }
    else if(c == '{')
    {

        

    }
    else if(isdigit(c)) // parser number
    {

    }

    free(token);

}
