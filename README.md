# hejson
Json parser.

## TO start
include "hjson.h" in your projects and run make

## the main struct
```c
typedef struct json{

    char *key; // key for the dict object
    int type; // 8 byte
    struct json *next; //8 byte
    int size; // 8 byte recod the size
    union{  
        int obj_int; //is also bool
        double obj_double;
        char *obj_string;
        struct json *obj_json; //new head 
    };

}Json;

```

## the push funcs

```c
void push_json_int(Json **head_ref, int value, char *eventualy_key);
void push_json_double(Json **head_ref, double value, char *eventualy_key);
void push_json_string(Json **head_ref, char *value, char *eventualy_key);
void push_json_bool(Json **head_ref, bool value, char *eventualy_key);
void push_json_null(Json **head_ref, char *eventualy_key);
void push_json_json(Json **head_ref, char *eventualy_key);

```
