#include "json_maker.h"

#include <stdio.h>

int main(void) {
	char json[1024] = "";
	
	json_begin(json);
	{
		json_key(json, "Strings");
		json_array_begin(json);
		{
			json_value_string(json, "foo");
			json_value_string(json, "bar");
		}
		json_array_end(json);
		
		json_key(json, "Numbers");
		json_array_begin(json);
		{
			json_value_number(json, 123456789);
			json_value_number(json, -123456789);
			json_value_double(json, 123.456);
			json_value_double(json, -123.12345678);
		}
		json_array_end(json);
		
		json_key(json, "Specials");
		json_array_begin(json);
		{
			json_value_bool(json, 1);
			json_value_bool(json, 0);
			json_value_null(json);
		}
		json_array_end(json);
		
		json_key(json, "Arrays");
		json_array_begin(json);
		{
			json_array_begin(json);
			json_array_end(json);
			json_array_begin(json);
			json_array_end(json);
			json_array_begin(json);
			json_array_end(json);
		}
		json_array_end(json);
		
		json_key(json, "Objects");
		json_array_begin(json);
		{
			json_begin(json);
			json_end(json);
			json_begin(json);
			json_end(json);
			json_begin(json);
			json_end(json);
			json_begin(json);
			json_end(json);
		}
		json_array_end(json);
		
		json_key(json, "A");
		json_begin(json);
		json_end(json);
		
		json_key(json, "B");
		json_begin(json);
		json_end(json);
		
		json_key(json, "C");
		json_value_string(json, "Hello, world!");
	}
	json_end(json);
	
	printf("%s\n", json);
	
	return 0;
}