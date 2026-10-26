#include "../src/hjson.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char input_path[128];
    Json *tail = NULL;
    Json *head;
    FILE *input;

    snprintf(input_path, sizeof(input_path), "/tmp/j_json_test1_%ld.json",
             (long)getpid());
    input = fopen(input_path, "w");
    assert(input != NULL);
    fputs("-42", input);
    assert(fclose(input) == 0);

    head = json_parse(input_path, &tail);
    assert(head != NULL);
    assert(tail != NULL);
    assert(head->type == OBJ_INT);
    assert(head->obj_int == -42);

    delete_json(&tail, &head);
    assert(remove(input_path) == 0);
    puts("test1: OK");
    return EXIT_SUCCESS;
}
