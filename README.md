# hejson
Json parser.
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
