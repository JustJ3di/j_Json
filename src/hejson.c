#include "hejson.h"

//only debug fgetc2 definition
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

//SOLO PER DEBUG
inline static void print_token(char *token){printf("catturato (%s)\n",token);}

//check memory call it after every malloc
inline static void check_memory(void *pointer){

    if (pointer == NULL)
        out_of_memory();

}

//SET A SIMPLE VALUE IN A DICT
static void set_simple_in_dict(Dict *new_object , int type_element , void *value ){

    new_object->type = SIMPLE;

    new_object->element.type = type_element;

    switch (new_object->element.type)
    {
    case INT:
        {
            int *value_int = (int *)value;
            new_object->element.obj_integer = *value_int;
        }
        break;
    case BOOL:
        {
            boolean *value_bool = (boolean *)value;
            new_object->element.obj_integer = *value_bool;
        }
        break;
    case DOUBLE:
        {
            double *value_double = (double *)value;
            new_object->element.obj_double = *value_double;
        }
        break;
    case NULL_:
        break;
    case STRING://i tipi string devon oessere deallocati apparte
        {
            new_object->element.obj_string = (char *)malloc(strlen((char *)value) + 1);
            strcpy(new_object->element.obj_string,(char *)value);
        }
        break;
    default:
        
        fprintf(stderr,"error in set_simple line\n");
        
        break;
    }

}

//SET A SIMPLE VALUE IN AN ARRAY
static void set_simple_in_array(Array *new_object , int type_element , void *value )
{

    new_object->type = SIMPLE;

    new_object->element.type = type_element;

    switch (new_object->element.type)
    {
    case INT:
        {
            int *value_int = (int *)value;
            new_object->element.obj_integer = *value_int;
        }
        break;
    case BOOL:
        {
            boolean *value_bool = (boolean *)value;
            new_object->element.obj_integer = *value_bool;
        }
        break;
    case DOUBLE:
        {
            double *value_double = value;
            new_object->element.obj_double = *value_double;

        }
        break;
    case NULL_:
        break;
    case STRING://i tipi string devon oessere deallocati apparte
        {
            new_object->element.obj_string = (char *)malloc(strlen((char *)value) + 1);
            
            strcpy(new_object->element.obj_string,(char *)value);
        }
        break;
    default:
        
        fprintf(stderr,"error in set_simple line\n");
        
        break;
    }

}

//SET THE KEY IN A DICT
inline static void set_key(Dict *new_object,const char *key)
{

    size_t i = 0;
    while (i  < strlen(key) + 1)
    {
        new_object->key[i] = key[i];
        i++;
    }

}

//SET GENERIC SIMPLE IN A GENERIC STRUCTURE
static void set_simple(void *new_object_generic , int type_element , void *value , int type_structure)
{

    switch (type_structure)
    {
    case DICT:
        
        set_simple_in_dict((Dict *)new_object_generic, type_element , value);
        
        break;

    case ARRAY:
        
        set_simple_in_array((Array *)new_object_generic, type_element , value);
        
        break;
    }

}

//push_on_a_dict_a_simple_value
Dict *push_on_dict_a_simple(Dict **head , void *value , const char *key , int type_simple)
{

    Dict *new_object = (Dict *)malloc(sizeof(Dict) + strlen(key) + 1);    
    
    check_memory((void *)new_object);
    
    set_simple((void *)new_object  , type_simple , value , DICT);

    set_key(new_object , key);

    new_object->next_element = *head;
    
    if (*head != NULL)
    {
        (*head)->previous_element = new_object;
    }
    
    *head = new_object;

    return *head;

}

//push on dicy a struct object
Dict *push_on_dict_struct(Dict **head, const char *key ,int type)
{

    Dict *new_object = (Dict *)malloc(sizeof(Dict)+ strlen(key) + 1);

    check_memory(new_object);

    switch (type)
    {
    case ARRAY:
        new_object->new_array = NULL;
        new_object->type = ARRAY;
        break;
    
    case DICT:
        new_object->new_head = NULL;
        new_object->type = DICT;
        break;
    }


    new_object->next_element = (*head);

    for (size_t i = 0; i < strlen(key)+1; i++)
    {
        new_object->key[i] = key[i];
    }
    

    if (*head != NULL)
        (*head)->previous_element = new_object;
    
    (*head) = new_object;


    return *head;

}

//push_on_array_a_simple_value
Array *push_on_array_simple(Array **head , void *value , int type_simple)
{

    Array *new_object = (Array *)malloc(sizeof(Array));    
    
    check_memory((void *)new_object);

    set_simple(new_object, type_simple , value , ARRAY);    

    new_object->next_element = *head;
    
    new_object->previous_element = NULL;

    if (*head != NULL)
    {
        (*head)->previous_element = new_object;
    }
    
    *head = new_object;

    return *head;


}

//PUSH on array struct object
Array *push_on_array_a_struct(Array **head , int type)
{

    Array *new_object = (Array *)malloc(sizeof(Array));    
    
    check_memory(new_object);
    
    switch (type)
    {
    case ARRAY:
        new_object->new_head = NULL;
        new_object->type = ARRAY;
        break;
    
    case DICT:
        new_object->new_dict_head = NULL;
        new_object->type = DICT;
        break;
    }


    new_object->next_element = (*head);

    if (*head != NULL)
        (*head)->previous_element = new_object;

    (*head) = new_object;

    return *head;

}


Json *alloc_simple(int type)
{
    Json *new = (Json *)malloc(sizeof(Json));
    check_memory((void *)new);

    new->type =SIMPLE;
    
    switch (type)
    {
    case STRING:
        new->new_simple_object.type = STRING;
        break;
    case INT:
        new->new_simple_object.type = INT;
        break;
    case DOUBLE:
        new->new_simple_object.type = DOUBLE;
        break;
    case NULL_:
        new->new_simple_object.type = NULL_;
        break;
    case BOOL:
        new->new_simple_object.type = BOOL;
        break;
    default:
        printf("error in alloc_simple type not correct\n");
        exit(EXIT_FAILURE);
    }
    return new;

}

Json *alloc_struct_object(int type)
{

    Json *new = (Json *)malloc(sizeof(Json));

    switch (type)
    {
    case ARRAY:
        new->type = ARRAY;
        new->new_array = NULL;
        break;
    
    case STRING:
        new->type = DICT;
        new->new_dict = NULL;
        break;
    }
    
    return new;

}

//dealloc of a array
void dealloc_array(Array **array_head_ref)
{

    Array *current = *array_head_ref;
    Array *tmp = current;

    while (current!=NULL)
    {

        current = tmp->next_element;
        
        if (tmp->type == SIMPLE)
        {   
            if((*tmp).element.type == STRING)  
                free((*tmp).element.obj_string);
        }
        else if(tmp->type == DICT){

            dealloc_dict(&(tmp->new_dict_head));

        }
            
        else if(tmp->type == ARRAY)
        {
         
            dealloc_array(&(tmp->new_head));
        
        }   
        
        free(tmp);
        
        tmp = current;
    }

}

//dealloc of a dict
void dealloc_dict(Dict **dict_head_ref)
{

    Dict *current = *dict_head_ref;
    Dict *tmp = current;
    
    while (current!=NULL)
    {

        current = tmp->next_element;
        
        if (tmp->type == SIMPLE)
        {
            if((*tmp).element.type == STRING)  
                free((*tmp).element.obj_string);
        }
        else if(tmp->type == DICT)
            dealloc_dict(&(tmp->new_head));
        else if(tmp->type == ARRAY)
            dealloc_array(&(tmp->new_array));
            
        
        free(tmp);
        
        tmp = current;
    }
    

}


void dealloc(Json **json_head_ref)
{
    if ((*json_head_ref) == NULL)
    {
        return;
    }
    
    switch ((*json_head_ref)->type)
    {
        case SIMPLE:
            
            if((*json_head_ref)->new_simple_object.type == STRING)  
                free((*json_head_ref)->new_simple_object.obj_string);

            break;

        case DICT:

            dealloc_dict(&((*json_head_ref)->new_dict));

            break;

        case ARRAY:

            dealloc_array(&((*json_head_ref)->new_array));

            break;
    }

    free(*json_head_ref);

}


inline static FILE *open_file(const char *filename)
{

    FILE *pr = fopen(filename,"r");
    if (pr == NULL)
    {
        perror("Error file not found\n");
        exit(EXIT_FAILURE);
    }
    return pr;
}

static void get_null(FILE *pr)
{

    char token[5];
    token[0] = 'n';
    for (size_t i = 1; i < 4; i++)
    {
        token[i] = fgetc(pr);
    }
    token[4] ='\0';
    if (strcmp("null",token))
    {
        parse_error(token,pr);
        
    }

    return;
}

static Json *parse_null(FILE *pr)
{

    get_null(pr);
        

    return alloc_simple(NULL_);
    
}

static boolean get_bool(FILE *pr,char first)
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

#if DEBUG
    print_token(token);
#endif

    if (!strcmp(token,"true"))
        return true;
    else if (!strcmp(token,"false"))
        return false;
    else
        return -1;
    
    

}

static Json *parse_boolean(FILE *pr,Json **json,char first)
{
    boolean value =  get_bool(pr,first);
    if (value == true || value == false)
    {
        *json = alloc_simple(BOOL);
        (*json)->new_simple_object.obj_bool = value;
    }else
        parse_char_error(first,pr);
    return *json;
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


#if DEBUG
        print_token(number);
#endif

    }

}

static  Json *parse_numeric(FILE *pr,Json **json,char first)
{
    char number[MAX_INPUT];
    
    int dot = 0;

    get_num(pr,first,number,&dot);

    //push on json object a 
    if (dot == 0)
    {
        *json = alloc_simple(INT);

        (*json)->new_simple_object.obj_integer = atoi(number);    
    }else
    {
        *json = alloc_simple(DOUBLE);

        (*json)->new_simple_object.obj_double = atof(number);  
    }
    

    return *json;


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
    
#if DEBUG
    print_token(token);
#endif


}

static Json *parse_string(FILE *pr,Json **json,char first)
{
    char *token = malloc(63566);

    get_string(pr,first,token);


    *json = alloc_simple(STRING);
    (*json)->new_simple_object.obj_string = malloc(strlen(token) + 1);
    strcpy((*json)->new_simple_object.obj_string,token);


    //free the token
    free(token);
    
    return *json;

}

static Json *parse_array(FILE *pr,Json **json,Array **head)
{

    Array **head_ref = NULL;
    if(head == NULL){

        *json = alloc_struct_object(ARRAY);
        head_ref = &(*json)->new_array;

    }else
        head_ref = head;
    char c;

    while (true)
    {

        c = fgetc(pr);
        
        switch (c)
        {
        case ':':
            parse_char_error(c,pr);   
        case ',':
            break;
        case '{':
            /* code */
            break;
        case '[':
            push_on_array_a_struct((head_ref),ARRAY);
            parse_array(pr,json,&(*head_ref)->new_head);
            break;
        case 'n':
            get_null(pr);
            push_on_array_simple((head_ref),NULL,NULL_);
            break;
        case '"':
            {
                char *token = malloc(10000);
                get_string(pr,c,token);
                push_on_array_simple((head_ref),(void *)token,STRING);
                free(token);
            }
            break;
        case 't':
        case 'f':
            {
                boolean n = get_bool(pr,c);
                boolean *value  = &n;
                push_on_array_simple(head_ref,(void *)value,BOOL);
            }
            break;

        case ']':
        case EOF:

            return *json;

        default:
            if(isspace(c))
                goto ignore;
            else if (isdigit(c)>0 || c =='-')
            {   
                int dot = 0;
                char *number = malloc(MAX_INPUT);
                get_num(pr,c,number,&dot);

                if (dot == 0)
                {
                    int value = atoi(number);
                    push_on_array_simple((head_ref),(void *)&value,INT);
                }else if (dot == 1)
                {
                    
                    double value = atof(number);
                    double *c = &value;
                    push_on_array_simple(head_ref,(void *)c,DOUBLE);
                }
                free(number);
                
            }
ignore:
           break;
        }
        
    }

}

static Json *parse_dict(FILE *pr,Json **json,Dict **head)
{

    Dict **head_ref;
    if (head == NULL)
    {

        *json = alloc_struct_object(DICT);
        head_ref = &(*json)->new_dict;

    }else
        head_ref = head;
    
    char c ;
    char *key = malloc(400);
    
    boolean key_found = false;
    while(true)
    {
        c = fgetc(pr);

        switch(c)
        {
            case ',':
                            
                key_found = false;
                break;
            case ':':
                if (key_found != true)
                    exit(EXIT_FAILURE);
                else
                    key_found = true;
                    
                break;
                
            case '{':
                if (key_found == false){
                    printf("key not found\n");
                    exit(EXIT_FAILURE);
                }else
                    key_found = true;

                push_on_dict_struct(head_ref,key,DICT);    
                parse_dict(pr,json,&(*head_ref)->new_head);
                break;
            case '[':
                if (key_found == false){
                    printf("key not found\n");
                    exit(EXIT_FAILURE);
                }else
                    key_found = true;
                push_on_dict_struct(head_ref , key,ARRAY);       
               
                parse_array(pr,json,&(*head_ref)->new_array);
                break;
            case 'n':
                if (key_found == false){
                    printf("key not found\n");
                    exit(EXIT_FAILURE);
                }
                get_null(pr);
                push_on_dict_a_simple((head_ref),NULL,key,NULL_);
                break;
            case '"':
                if(key_found == false)
                {
               
                    get_string(pr,c,key); 
                    key_found = true ;
                }
                else   
                {
                    char *token = malloc(10000);
                    get_string(pr,c,token);
                    push_on_dict_a_simple((head_ref),(void *)token,key,STRING);
                    free(token);
                }

                break;
            case 't':
            case 'f':
                {

                    boolean n = get_bool(pr,c);
                    boolean *value  = &n;
                    push_on_dict_a_simple(head_ref,(void *)value,key,BOOL);

                }
                break;
           case EOF:
           case '}':
            free(key);
            return *json;
        default:
            if(isspace(c))
                goto ignore;
            else if (isdigit(c)>0 || c =='-')
            {   
                int dot = 0;
                char *number = malloc(MAX_INPUT);
                get_num(pr,c,number,&dot);

                if (dot == 0)
                {
#if DEBUG
                printf("key = (%s)\n",key);
#endif
                    int value = atoi(number);
                    push_on_dict_a_simple((head_ref),(void *)&value,key,INT);
                
                }else if (dot == 1)
                {
                    
                    double value = atof(number);
                    push_on_dict_a_simple(head_ref,(void *)&value,key,DOUBLE);
                
                }
                free(number);
                
                
            }
ignore:
           break;            

        }

        

    } 
    
    return *json;

}


Json *Json_parse(const char *filename){
    
    Json *json = NULL;
    
    FILE *pr = open_file(filename);
    
    char c = fgetc(pr);
    switch (c)
    {
    case '{':
        json = parse_dict(pr,&json,NULL);
        break;
    case '[':
        json = parse_array(pr,&json,NULL);
        break;
    case 'n':
        json = parse_null(pr);
        break;
    case '"':
        parse_string(pr,&json,c);
        break;
    case 't':
    case 'f':
        parse_boolean(pr, &json, c);
        break;
    case EOF:
        json = (Json *)malloc(sizeof(Json));
        break;
    default:
        if(isspace(c))
            break;
        else if (isdigit(c)>0 || c =='-')
        {
            parse_numeric(pr,&json,c);
            break;
        }
        else
        {
            parse_char_error(c,pr);
            break; 
        }


        
    }
    
    fclose(pr);

    return json;

}


static void print_array(Array **head)
{

    Array *current = *head;
    printf("[");
    if (current == NULL)
    {
        return;
    }
    
    while(current)
    {
        switch (current->type)
        {
            case SIMPLE:

                
                    switch ((current)->element.type)
                    {
                    case STRING:
                        printf("%s, ",(current)->element.obj_string);
                        break;
                    case BOOL:
                        printf("%d, ",(current)->element.obj_bool);
                        break;
                    case NULL_:
                        printf("null, ");
                        break;
                    case DOUBLE:
                        printf("%f, ",(current)->element.obj_double);
                        break;
                    case INT:
                        printf("%d, ",(current)->element.obj_integer);
                        break;
                    default:
                        break;
                    }

                break;
            case ARRAY:
                
                print_array(&(*head)->new_head);
                
  
        }
        current = current->next_element;

    }

    
    printf("]");

}

void print_json(Json **json_head_ref){


    if ((*json_head_ref) == NULL)
    {
        return;
    }
    
    switch ((*json_head_ref)->type)
    {
        case SIMPLE:
            
                switch ((*json_head_ref)->new_simple_object.type)
                {
                case STRING:
                    printf("%s\n",(*json_head_ref)->new_simple_object.obj_string);
                    break;
                case BOOL:
                    printf("%d\n",(*json_head_ref)->new_simple_object.obj_bool);
                    break;
                case NULL_:
                    printf("null\n");
                    break;
                case DOUBLE:
                    printf("%f\n",(*json_head_ref)->new_simple_object.obj_double);
                    break;
                case INT:
                    printf("%d\n",(*json_head_ref)->new_simple_object.obj_integer);
                    break;
                default:
                    break;
                }

            break;

        case DICT:


            break;

        case ARRAY:
            print_array(&(*json_head_ref)->new_array);

            break;
    }

}


