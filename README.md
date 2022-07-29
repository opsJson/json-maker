# json-maker
ANSCI C Json Maker

## Features
- ANSI C (C89).
- Easy set of functions.
- Simple, small and fast.
- 0 allocations.
- 0 dependencies. (for now, only libc.)
- 0 obfuscated custom types.

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

`json_value_double(char *json, double d);`

`json_value_bool(char *json, char boolean);`

`json_value_null(char *json);`
