#include "../src/hjson.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char input_path[128];
    char output_path[128];
    char output[64];
    Json *tail = NULL;
    Json *head;
    FILE *input;
    FILE *serialized;
    FILE *result;
    size_t output_size;

    snprintf(input_path, sizeof(input_path), "/tmp/j_json_test3_in_%ld.json",
             (long)getpid());
    snprintf(output_path, sizeof(output_path), "/tmp/j_json_test3_out_%ld.json",
             (long)getpid());
    input = fopen(input_path, "w");
    assert(input != NULL);
    fputs("[1,2,\"three\"]", input);
    assert(fclose(input) == 0);

    head = json_parse(input_path, &tail);
    assert(head != NULL);
    assert(tail != NULL);
    assert(head->size == 3);
    assert(tail[1].type == OBJ_INT && tail[1].obj_int == 1);
    assert(tail[2].type == OBJ_INT && tail[2].obj_int == 2);
    assert(tail[3].type == OBJ_STRING);
    assert(strcmp(tail[3].obj_string, "\"three\"") == 0);

    serialized = fopen(output_path, "w");
    assert(serialized != NULL);
    serialize(&head, serialized);

    result = fopen(output_path, "r");
    assert(result != NULL);
    output_size = fread(output, 1, sizeof(output) - 1, result);
    output[output_size] = '\0';
    assert(fclose(result) == 0);
    assert(strcmp(output, "[1,2,\"three\"]") == 0);

    delete_json(&tail, &head);
    assert(remove(input_path) == 0);
    assert(remove(output_path) == 0);
    puts("test3: OK");
    return EXIT_SUCCESS;
}
