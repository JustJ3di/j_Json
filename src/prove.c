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

    while(head->next->obj_json)
    {
        printf("%d ##### \n", head->next->obj_json->type);   
        head->next->obj_json = head->next->obj_json->next;
    }
    
  //  printf("%d \n",(head)->next->next->obj_int);
   
    
    

    //delete_json(&tail, &head);

    return 0;
}
