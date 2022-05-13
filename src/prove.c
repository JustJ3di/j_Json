#include "hjson.h"

int main()
{

    Json *tail  = NULL;

    Json *head = json_parse("prova.json" , &tail);

    assert(head != tail); //beacause the ara always a push on the linked  

    printf("%s \n",head->obj_string);

    delete_json(&tail, &head);

    return 0;
}
