# json-maker
ANSCI C Json Maker

## Features
- ANSI C (C89).
- Easy set of functions.
- Simple, small and fast.
- Don't need libc.
- 0 allocations.
- 0 dependencies.
- 0 obfuscated custom types.  
- Supports widechars (add the "_wc" prefix to any of the functions in this library)

## Functions
### objects:
`json_begin(char *json);`

`json_end(char *json);`

### arrays:
`json_array_begin(char *json);`

`json_array_end(char *json);`

### keys:
`json_key(char *json, char *key);`


### values:
`json_value_string(char *json, char *string);`

`json_value_number(char *json, long int number);`

`void json_value_double(char *json, double number);`

`json_value_bool(char *json, char boolean);`

`json_value_null(char *json);`
