#include "src/hjson.h"

int main()
{

    Json *tail  = NULL;

    Json *head = json_parse("prova.json" , &tail);

    assert(head != tail); //beacause the is  at least one  push on the linked.  
    
    Json *curr = head;


    serialize(&curr, stdout);
   

    delete_json(&tail, &head);

    return 0;
}
