#include "hjson.h"
#if DEBUG

    int fgect2(FILE *pr,int line,const char *fun)
    {
        char c = fgetc(pr);
        if (isspace(c)==0)
        {
            printf("(%c) trovato in fun (%s) alla line %d \n",c,fun,line);
        }
        return c;

    }

#define fgetc(ch) fgect2(ch,__LINE__,__func__);
#endif

#define newnodo(pointer) {pointer + 1};

static int get_size(Json **json) {return (*json)->size;}

static Json *get_tail(Json **head){

    Json *tail = *head;
    while (tail->next)
    {
        tail = tail->next;
    }
    
    return tail;

}

static Json  *json_init(int type){

    //select the correct size for the memory
    size_t size;
    Json *json;

    if (type == OBJ_SIMPLE)
        size = SIMPLE_SIZE;
    else
        size = INITIAL_INIT_SIZE;

    json = (Json *)malloc(sizeof(Json)*size); //MAGIC NUMBER I NEED TO FIX IT
    
    if (json == NULL) //malloc failed
        exit(EXIT_FAILURE);

    
    for (int i = 0; i < (int )size; i++)
    {
        /*initialize value*/
        json[i].next = NULL;
        json[i].type = type; 
        json[i].size = i;
        json[i].obj_string = NULL;
        json[i].key = NULL;

    }
    

    return json;

}   

void push_json_int(Json **head_ref, int value, char *eventualy_key)
{

    Json *new_json = newnodo(*head_ref);
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

    Json *new_json = newnodo(*head_ref);
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

    Json *new_json = newnodo(*head_ref);
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

    Json *new_json = newnodo(*head_ref);
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

    Json *new_json = newnodo(*head_ref);
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

    Json *new_json = newnodo(*head_ref);
    //i need to append a memeorys'control
    
    //alloc list
    new_json->obj_json = json_init(OBJ_ARRAY);

    

    

    //start new linked list

    if (eventualy_key != NULL) //set a key if we need it!
    {
        new_json->type = OBJ_DICT;
        new_json->key = (char *)malloc(strlen(eventualy_key) + 1);
        strcpy(new_json->key, eventualy_key);
    }
    else  //push array.
    {
        new_json->type = OBJ_ARRAY;
        new_json->key = NULL;
        new_json->obj_json->next = NULL;
    }
   
    new_json->next = (*head_ref);

    (*head_ref) = new_json;

}

static void get_null(FILE *pr, char *first){

    char token[10000];
    token[0] = *first;
    for (size_t i = 1; i < 4; i++)
    {
        *first = fgetc(pr);
        token[i] = *first;
    }
    token[4] ='\0';
    if (strcmp("null",token))
    {
        printf("Error null value not found\n");
        exit(1);        
    }


}

static bool get_boolean(FILE *pr, char *first) //first is the first char to parse
{
    size_t size;

    char token[6];

    token[0] = *first;

    if (*first == 't')
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

static void get_string(FILE *pr,char *first,char *token)
{

    int i = 0;
    token[i] = *first;
    i = 1;

    do
    {
        *first = fgetc(pr);
        token[i] = *first;
        i++;

    }while (*first != '"');

    token[i] = '\0';
}

static void get_num(FILE *pr,char *first,char *number,int *dot)
{

    int i;    
 
    number[0] = *first;
    *dot = 0;
    i = 1;

    *first = fgetc(pr);
    if(number[0] == '-' ) 
    {//error i need to handle the error in a better way
        if ( !isdigit(*first))
        {
                exit(EXIT_FAILURE);    
        }
    }
    
    number[1] = *first;
    
    i++;
    
    while (isdigit(*first) || *first == '.')
    {
        if (*first == '.')//case float
        {
            *dot = 1;
            *first = fgetc(pr);
            number[i] = *first;
            i++;
            continue;
        }

        *first = fgetc(pr);
        number[i] = *first;
        i++;

    }
      
    
    number[i-1] = '\0';


}


Json *json_parse(const char *filename, Json **tail){

    FILE *pr;
    Json *json = NULL;
    char c;

    pr = fopen(filename,"r");

    c = fgetc(pr);

    while(isspace(c) > 0)
        c = fgetc(pr);

    if(c == '"' || c == 'n' || c == 'f' || c == 't' || isdigit(c) > 0 || c == '-')
    {

        json = json_init(OBJ_SIMPLE);
        *tail = json;
        json =  json_parse_value(&json, pr, &c, NULL);

    }
    else if (c == '[')
    {
        
        json = json_init(OBJ_ARRAY);
        *tail = json;
        json = json_parse_array(&json, pr);

    }
    else if(c == '{')
    {

        json = json_init(OBJ_DICT);
        *tail = json;
        json = json_parse_dict(&json, pr);

    }
    
    fclose(pr);

    return json;

}

Json *json_parse_value(Json **head_ref, FILE *pr, char *first, char *key)
{

    char  value[255];


    if (*first == 'n') // parse null
    {
        get_null(pr, first);
        push_json_null(head_ref, key);
    } 
    else if( *first == 't' || *first == 'f')//parse boolean
    {
        bool value = get_boolean(pr, first);
        push_json_bool(head_ref, value, key);

    }
    else if (*first == EOF)
    {   
        return (*head_ref);
    }
    else if (*first == '"') // parse string
    {
        get_string(pr, first, value);
        push_json_string(head_ref, value, key);

    }
    else if(isdigit(*first) || *first == '-') // parser number
    {
        int dot = 0;

        get_num(pr, first, value, &dot);

        //push on json object a 
        if (dot == 0)
        {
            push_json_int(head_ref, atoi(value), key);
        }else
        {
            push_json_double(head_ref, atof(value), key);
        }
        
    }

    return (*head_ref);

}


Json *json_parse_array(Json **head_ref, FILE *pr )
{

    char c = '\0';    


    while (c != ']')
    {
        c = fgetc(pr);

        while(isspace(c))
            c = fgetc(pr);
         
        if (c == ']'|| c== EOF)
        {   
            return (*head_ref);
        }
        if (c == ',')
        {
            continue;
        }

        if (c == 'n' || c == 't' || c == '"' || c =='f' || (isdigit(c))|| c == '-') // parse null
        {

            (*head_ref) = json_parse_value(head_ref, pr, &c , NULL);
            
        } 
        else if(c == '[')
        {

            push_json_json(head_ref, NULL);
            
            (*head_ref)->obj_json = json_parse_array(&(*head_ref)->obj_json, pr);    
            
        }
        else if(c == '{')
        {
            push_json_json(head_ref, NULL);

            (*head_ref)->obj_json = json_parse_dict(&(*head_ref)->obj_json, pr);

        }
        

    }

    return (*head_ref);

}


Json *json_parse_dict(Json **head_ref, FILE *pr ){

    char c = '\0';    

    bool value = false; 

    char key[128];

    while (c != '}')
    {
        c = fgetc(pr);

        while(isspace(c))
            c = fgetc(pr);
         
        if (c == '}'|| c== EOF)
        {   
            return (*head_ref);
        }
        if (c == ',')
        {
            value = false;
            continue;
        }


        if (value == true 
        && (c == 'n' 
        || c == 't' 
        || c == '"' 
        || c =='f' 
        || (isdigit(c))
        || c == '-')) // parse null
        {
            printf("key0 (%s)\n", key);
            (*head_ref) = json_parse_value(head_ref, pr, &c , key);
            value = false;
            
        } 
        else if(c == '"' 
	    && value == false) //find key
       	{
            get_string(pr, &c, key);

            value = true;

        }
        else if(c == '[')
        {
            push_json_json(head_ref, key);

            (*head_ref)->obj_json = json_parse_array(&(*head_ref)->obj_json, pr);
            
        }else if(c== '{')
        {
            push_json_json(head_ref, key);
            (*head_ref)->obj_json = json_parse_array(&(*head_ref)->obj_json, pr);
        
        }
        

    }

    return (*head_ref);  


}

void delete_dict(Json **head)
{
    while((*head)->next)
        {
            if ((*head)->type == OBJ_STRING)
            {
                free((*head)->obj_string);
            }
            else if ((*head)->type == OBJ_ARRAY )
            {   
                Json *curr = (*head)->obj_json; 
                delete_array(&curr);
            }
            else if ((*head)->type == OBJ_DICT)
            {
                Json *curr = (*head)->obj_json; 
                delete_dict(&curr);
            }
            
            free((*head)->key);
            (*head) = (*head)->next;
        }   

        free(*head);

}

void delete_array(Json **head)
{   

    while((*head)->next)
        {
                           
            if((*head)->key)
                free((*head)->key);
            

        
            if ((*head)->type == OBJ_STRING)
            {
                free((*head)->obj_string);
            }else if ((*head)->type == OBJ_ARRAY)
            {   

                
                Json *curr = (*head)->obj_json; 
                delete_array(&curr);
            }
            else if ((*head)->type == OBJ_DICT)
            {
                Json *curr = (*head)->obj_json;
                delete_dict(&curr);
            }


            (*head) = (*head)->next;    

        }          

        free(*head);
}


void delete_json(Json **tail,Json  **head)
{

    if ((*tail)->type == OBJ_SIMPLE)
    {
        if ((*head)->type == OBJ_STRING)
        {
            free((*head)->obj_string);
        }
        
        free(*tail);
    }
    else if ((*tail)->type == OBJ_ARRAY)
    {        
        while(*head)
        {
            if ((*head)->type == OBJ_STRING)
            {
                free((*head)->obj_string);
            }
            else if ((*head)->type == OBJ_ARRAY && (*head)!= *tail)
            {   
                Json *curr = (*head)->obj_json; 
                delete_array(&curr);                    
            }
            
            (*head) = (*head)->next;
        }   

        free(*tail);

    }
    else if((*tail)->type == OBJ_DICT)
    {
        while(*head)
        {
            if ((*head)->type == OBJ_STRING)
            {
                free((*head)->obj_string);
            }
            else if ((*head)->type ==OBJ_DICT && (*head)!= *tail)
            {   
                Json *curr = (*head)->obj_json;  
                delete_dict(&curr);  
            }
            
            free((*head)->key);
            (*head) = (*head)->next;
        }   

        free(*tail);
    }
    

}




void printf_obj(Json **head)
{



    while((*head)->next)
    {
                
        if ((*head)->type == OBJ_ARRAY)
        {   
            
            Json *curr = (*head)->obj_json; 
            if(curr->key)
            {
                printf("{");
                
            }
            else
                printf("[");

            printf_obj(&curr);

            printf("],");


        }
        else if ((*head)->type == OBJ_DICT)
        {
            Json *curr = (*head)->obj_json;
            printf_obj(&curr);
        }   
        else
        {
            if((*head)->key)
                printf("%s:",(*head)->key);
            printf_value(head);
            
            if((*head)->key)
                printf("}");
            
        }        
        (*head) = (*head)->next;    

    }
}


void printf_value(Json **head)
{

    if ((*head)->type == OBJ_STRING)
    {
        printf("%s, ",(*head)->obj_string);
    }
    else if((*head)->type == OBJ_INT)
    {
        printf("%d, ",(*head)->obj_int);
    }
    else if((*head)->type == OBJ_DOUBLE)
    {
        printf("%f, ",(*head)->obj_double);
    }
    else if((*head)->type == OBJ_NULL)
    {
        printf("null");
    }
    else if ((*head)->type == OBJ_BOOL)
    {
        printf("%d, ",(*head)->obj_int);
    }

}



void printf_json(Json **tail, Json **head){

    Json *t = *tail;
    Json *h = *head;
        
    if ((t)->type == OBJ_SIMPLE)
    {   
        printf_value(&h);
    }
    else if ((t)->type == OBJ_ARRAY)
    {   
        printf("[");
        printf_obj(&h);
        printf("]\n");
    }
    else if((*tail)->type == OBJ_DICT)
    {
        printf("{");
        printf_obj(&h);
        printf("}");

    }

    
}


static void serialize_value(FILE *pr, Json head)
{

    switch (head.type)
    {
    case OBJ_NULL:
        fprintf(pr, "null");
        break;
    case OBJ_BOOL:
        if (head.obj_int == 1)
            fprintf(pr , "true");
        else
            fprintf(pr,"false") ;
        break; 
    case OBJ_INT:
        fprintf(pr, "%d", head.obj_int);
        break;
    case OBJ_STRING:
        fprintf(pr ,"%s", head.obj_string);
        break;
    }
    

}

void serialize_array(FILE *pr, Json *tail, int size)
{

    fprintf(pr,"[");
    for (int i = 1; i < size+1; i++)
    {
        switch (tail[i].type)
        {
        case OBJ_ARRAY:
            
            serialize_array(pr, get_tail(&tail[i].obj_json), get_size(&tail[i].obj_json)); 

            break;
        
        default:
            if (tail[i].key)
            {
                fprintf(pr, "%s", tail[i].key);
                fprintf(pr, ":");    
            }
            
            serialize_value(pr, tail[i]);
            break;
        }
        
        if (i != size)
        {
            fprintf(pr,",");
        }
        
    }
    fprintf(pr,"]");

}

void serialize_dict(FILE *pr, Json *tail, int size)
{

    fprintf(pr, "{");
    for (int i = 1; i < size+1; i++)
    {
        switch (tail[i].type)
        {
        case OBJ_DICT:
            
            fprintf(pr, "%s", tail[i].key);
            fprintf(pr, ":");
            serialize_array(pr, get_tail(&tail[i].obj_json), get_size(&tail[i].obj_json));

            break;
        
        default:
            fprintf(pr, "%s", tail[i].key);
            fprintf(pr, ":");
            serialize_value(pr, tail[i]);
            break;
        }
        
        if (i != size)
        {
            fprintf(pr,",");
        }
        
    }
    fprintf(pr,"}");    


}


void serialize(Json **head)
{

    int size = get_size(head);

    Json *tail = get_tail(head);
    FILE *pr = fopen("new.json","w");

    if (tail->type == OBJ_ARRAY)
    {
        serialize_array(pr, tail, size);
    }else if (tail->type == OBJ_DICT)
    {
        serialize_dict(pr , tail, size);
    }
    
    

    fclose(pr);

}