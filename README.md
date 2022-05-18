# J-json
Json parser.

## TO start
include "hjson.h" in your projects and run ```make```

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

## the push functions

```c
void push_json_int(Json **head_ref, int value, char *eventualy_key);
void push_json_double(Json **head_ref, double value, char *eventualy_key);
void push_json_string(Json **head_ref, char *value, char *eventualy_key);
void push_json_bool(Json **head_ref, bool value, char *eventualy_key);
void push_json_null(Json **head_ref, char *eventualy_key);
void push_json_json(Json **head_ref, char *eventualy_key);

```
## the parse functions 
```c
Json *json_parse(const char *, Json **);
Json *json_parse_value(Json **head_ref, FILE *pr, char *first, char *key);
Json *json_parse_array(Json **head_ref, FILE *pr);
Json *json_parse_dict(Json **head_ref, FILE *pr);
```

## serialize

```c
void serialize(Json **head, FILE *);
void serialize_array(FILE *pr, Json *tail, int size);
void serialize_dict(FILE *pr, Json *tail, int size);
```

## the main idea 
The idea is to initialize everything with a statically managed linked-list , 
and later have the possibility then to serialize the possibly modified content, 
handling it in a simpler way as an array thanks to the get_tail function that returns me the pointer to the first element of the list.
```c
static Json *get_tail(Json **head){

    Json *tail = *head;
    while (tail->next)
    {
        tail = tail->next;
    }
    
    return tail;

}
```