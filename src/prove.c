#include "hjson.h"

int main()
{

    Json *tail  = NULL;

    Json *head = json_parse("prova.json" , &tail);

    assert(head != tail); //beacause the ara always a push on the linked  

    Json *curr = head;

    printf("(%s)\n", head->obj_string);

    while(curr)
    {

        printf("%d \n",curr->type);
        (curr) = curr->next;
    }
    
    

    delete_json(&tail, &head);

    return 0;
}
