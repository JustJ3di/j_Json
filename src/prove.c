#include "hjson.h"

int main()
{

    Json *tail  = NULL;

    Json *head = json_parse("prova.json" , &tail);

    assert(head != tail); //beacause the is  at least one  push on the linked.  

    Json *curr = head;

    //printf("(%s)\n", head->obj_string);

    while(curr)
    {

        printf("%d \n",curr->type);
        
        (curr) = curr->next;
    }

    printf("jeu %s\n",head->obj_json->key);
    
    //free(head->obj_json->key);
   //printf("%s \n",(head)->obj_json->key);
   
    
    

    delete_json(&tail, &head);

    return 0;
}
