#include <stdio.h>
#include "hejson.h"

int main()
{
    Json *new = Json_parse("prova.json");

    printf("%d\n",new->new_simple_object.type);

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

    dealloc(&new);

 

    return 0;
}



