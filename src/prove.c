#include "hjson.h"

int main()
{

    Json *tail  = NULL;

    Json *head = json_parse("prova.json" , &tail);

    assert(head != tail); //beacause the is  at least one  push on the linked.  
    printf("%d\n",get_size(&head));
    Json *curr = head;

    //printf("(%s)\n", head->obj_string);

    while(curr)
    {

        printf("%d \n",curr->type);
        
        (curr) = curr->next;
    }

   
    //free(head->obj_json->key);
   //printf("%s \n",(head)->obj_json->key);
   
    
    printf_json(&tail,&head);

    delete_json(&tail, &head);

    return 0;
}
