#include "../src/hjson.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char input_path[128];
    Json *tail = NULL;
    Json *head;
    FILE *input;

    snprintf(input_path, sizeof(input_path), "/tmp/j_json_test2_%ld.json",
             (long)getpid());
    input = fopen(input_path, "w");
    assert(input != NULL);
    fputs("{\"name\":\"Ada\",\"age\":37,\"active\":true,\"missing\":null}",
          input);
    assert(fclose(input) == 0);

    head = json_parse(input_path, &tail);
    assert(head != NULL);
    assert(tail != NULL);
    assert(head->size == 4);
    assert(tail[1].type == OBJ_STRING);
    assert(strcmp(tail[1].key, "\"name\"") == 0);
    assert(strcmp(tail[1].obj_string, "\"Ada\"") == 0);
    assert(tail[2].type == OBJ_INT);
    assert(tail[2].obj_int == 37);
    assert(strcmp(tail[2].key, "\"age\"") == 0);
    assert(tail[3].type == OBJ_BOOL);
    assert(tail[3].obj_int == 1);
    assert(strcmp(tail[3].key, "\"active\"") == 0);
    assert(tail[4].type == OBJ_NULL);
    assert(strcmp(tail[4].key, "\"missing\"") == 0);

    delete_json(&tail, &head);
    assert(remove(input_path) == 0);
    puts("test2: OK");
    return EXIT_SUCCESS;
}
