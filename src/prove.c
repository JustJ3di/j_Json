#include "hjson.h"

int main()
{

    Json *tail  = NULL;

    Json *head = json_parse("prova.json" , &tail);

    assert(head != tail); //beacause the ara always a push on the linked  

    printf("%f \n",head->obj_double);

    delete_json(&tail, &head);

    return 0;
}
