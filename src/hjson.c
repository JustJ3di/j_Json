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

static void get_null(FILE *pr){

    char token[10000];
    token[0] = 'n';
    for (size_t i = 1; i < 4; i++)
    {
        token[i] = fgetc(pr);
    }
    token[4] ='\0';
    if (strcmp("null",token))
    {
        printf("Error null value not found\n");
        
    }

    return;

}

static bool get_boolean(FILE *pr, char first) //first is the first char to parse
{
    size_t size;

    char token[6];

    token[0] = first;

    if (first == 't')
        size = 4;
    else
        size = 5;

    for (size_t i = 1; i < size; i++)
        token[i] = fgetc(pr);

    token[size] = '\0';

    if (!strcmp(token,"true"))
        return true;
    else if (!strcmp(token,"false"))
        return false;
    else
        return -1;
    
}

static void get_string(FILE *pr,char first,char *token)
{

    int i = 0;
    token[i] = first;
    i = 1;

    do
    {
        first = fgetc(pr);
        token[i] = first;
        i++;
        if (first == EOF){

            free(token);
            parse_char_error(first,pr);
        }
        

    } while (first != '"');
    
    token[i] = '\0';
}

static void get_num(FILE *pr,char first,char *number,int *dot)
{

    int i = 0;    

    if (isdigit(first) || first == '-')
    {   
        number[0] = first;
        *dot = 0;
        i = 1;

        first = fgetc(pr);

     
        number[1] = first;
        i++;
        
        while (isdigit(first))
        {

            first = fgetc(pr);
            number[i] = first;
            i++;
            if (first == '.')//case float
            {
                *dot = 1;
                first = fgetc(pr);
                number[i] = first;
                i++;
                continue;
            }
        }
        
      
        number[i-1] = '\0';

    }

}

Json *json_simple_parse(Json **head_ref, FILE *pr)
{

    char c = fgetc(pr);
    char value[255];
    for (size_t i = 0; i < 255; i++)
    {
        value[i] = 'a'; //*(value + i) = 'a'
    }
    
    

    while(isspace(c))
        c = fgetc(pr);
    
    if (c == 'n') // parse null
    {
        get_null(pr);
        push_json_null(head_ref, NULL);
    }    
    else if(c== 't' || c== 'f')//parse boolean
    {
        bool value = get_boolean(pr, c);

    }else if (c == '"') // parse string
    {
        get_string(pr, c, value);
        push_json_string(head_ref,value, NULL);
        
    }
    else if(c == '[' || c == '{') // parse array
    {
        //parse_struct una func
    }
    else if(isdigit(c)) // parser number
    {
        int dot = 0;
        get_num(pr,c,value,&dot);

        //push on json object a 
        if (dot == 0)
        {
            push_json_int(head_ref, atoi(value), NULL);
        }else
        {
            push_json_double(head_ref, atof(value), NULL);
        }
        

    }



}
