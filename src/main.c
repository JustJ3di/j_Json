#include <stdio.h>
#include "hejson.h"

int main()
{   
    Json *tail = NULL;
    Json *new = json_parse("prova.json", &tail);

    printf("%d,\n",new->next->obj_int);

    //printf("(%s), (%d)\n",new->new_dict->new_head->key, new->new_dict->new_head->element.obj_integer);
    
    //printf("\n");

/*
    char *value = "ciao";

    push_on_array_simple(&(new->new_array) , value  , STRING);

    push_on_array_a_struct(&(new->new_array),ARRAY);
    
    printf("ciao\n");

    push_on_array_simple(&(new->new_array->new_head) ,value , STRING);
    
    push_on_array_a_struct(&(new->new_array),DICT);

    push_on_dict_a_simple(&(new->new_array->new_dict_head),"ciao","ciasss", STRING);

    printf("ciao\n");
*/

    

 

    return 0;
}



