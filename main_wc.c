#define JM_WIDECHAR
#include "json_maker.h"

#include <stdio.h>

int main(void) {
	wchar_t json[1024] = L"";
	
	json_begin_wc(json);
	{
		json_key_wc(json, L"Strings");
		json_array_begin_wc(json);
		{
			json_value_string_wc(json, L"foo");
			json_value_string_wc(json, L"bar");
		}
		json_array_end_wc(json);
		
		json_key_wc(json, L"Numbers");
		json_array_begin_wc(json);
		{
			json_value_number_wc(json, 123456789);
			json_value_number_wc(json, -123456789);
			json_value_double_wc(json, 123.456);
			json_value_double_wc(json, -123.12345678);
		}
		json_array_end_wc(json);
		
		json_key_wc(json, L"Specials");
		json_array_begin_wc(json);
		{
			json_value_bool_wc(json, 1);
			json_value_bool_wc(json, 0);
			json_value_null_wc(json);
		}
		json_array_end_wc(json);
		
		json_key_wc(json, L"Arrays");
		json_array_begin_wc(json);
		{
			json_array_begin_wc(json);
			json_array_end_wc(json);
			json_array_begin_wc(json);
			json_array_end_wc(json);
			json_array_begin_wc(json);
			json_array_end_wc(json);
		}
		json_array_end_wc(json);
		
		json_key_wc(json, L"Objects");
		json_array_begin_wc(json);
		{
			json_begin_wc(json);
			json_end_wc(json);
			json_begin_wc(json);
			json_end_wc(json);
			json_begin_wc(json);
			json_end_wc(json);
			json_begin_wc(json);
			json_end_wc(json);
		}
		json_array_end_wc(json);
		
		json_key_wc(json, L"A");
		json_begin_wc(json);
		json_end_wc(json);
		
		json_key_wc(json, L"B");
		json_begin_wc(json);
		json_end_wc(json);
		
		json_key_wc(json, L"C");
		json_value_string_wc(json, L"Hello, world!");
	}
	json_end_wc(json);
	
	wprintf(L"%ls\n", json);
	
	return 0;
}