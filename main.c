#include "json_maker.h"
#include <stdio.h>

int main(void) {
	char json[1024] = {0};
	
	json_begin(json);
	{
		json_key(json, "strings");
		json_array_begin(json);
		{
			json_value_string(json, "Foo!");
			json_value_string(json, "Bar!");
			json_value_string(json, "FooBar!");
		}
		json_array_end(json);
		
		json_key(json, "Numbers");
		json_value_number(json, 123456789);
		//TODO: test negative
		
		json_key(json, "special");
		json_array_begin(json);
		{
			json_array_begin(json);
			{
				json_value_null(json);
			}
			json_array_end(json);
			
			json_array_begin(json);
			{
				json_value_bool(json, 1);
			}
			json_array_end(json);
			
			json_array_begin(json);
			{
				json_value_double(json, 1234.567890123);
			}
			json_array_end(json);
		}
		json_array_end(json);
		
		json_key(json, "A");
		json_begin(json);
		json_end(json);
		
		json_key(json, "B");
		json_begin(json);
		json_end(json);
		
		json_key(json, "C");
		json_begin(json);
		json_end(json);
		
		json_key(json, "D");
		json_value_string(json, "Hello, World!");
	}
	json_end(json);
	
	printf("%s\n", json);
	
	return 0;
}