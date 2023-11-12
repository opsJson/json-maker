#ifndef JSON_MAKER_H
#define JSON_MAKER_H

/* MACROS */

#ifndef JM_DOUBLE_PRECISION
#define JM_DOUBLE_PRECISION 10000000
#endif /* JM_DOUBLE_PRECISION */

/* PUBLIC FUNCTIONS DECLARATION */

void json_begin(char *json);
void json_end(char *json);
void json_array_begin(char *json);
void json_array_end(char *json);
void json_key(char *json, const char *key);
void json_value_string(char *json, const char *string);
void json_value_number(char *json, long int number);
void json_value_double(char *json, double number);
void json_value_bool(char *json, int boolean);
void json_value_null(char *json);
void json_value_raw(char *json, const char *raw);

/* PRIVATE FUNCTIONS DECLARATION */

static unsigned int jm_strlen(const char *src);
static void jm_strcpy(char *dest, const char *src);
static void jm_strcat(char *dest, const char *src);
static void jm_number_to_str(char *dest, long int number);
static void jm_strcat_escaped(char *json, const char *string);

/* PRIVATE FUNCTIONS IMPLEMENTATION */

static unsigned int jm_strlen(const char *src) {
	unsigned int i = 0;
	while (*(src + i)) {
		i++;
	}
	
	return i;
}

static void jm_strcpy(char *dest, const char *src) {
	unsigned int i, length;
	
	length = jm_strlen(src);
	
	for (i=0; i<length; i++)
		dest[i] = src[i];
	
	dest[i] = 0;
}

static void jm_strcat(char *dest, const char *src) {
	jm_strcpy(dest + jm_strlen(dest), src);
}

static void jm_number_to_str(char *dest, long int number) {
	unsigned int is_negative, digit, save;
	unsigned int digits = 0, length = jm_strlen(dest);
	
	if (number < 0) {
		number -= 2*number;
		is_negative = 1;
	}
	else if (number == 0) {
	    is_negative = 0;
	    digits++;
	}
	else {
	    is_negative = 0;
	}
	
	if (is_negative) digits++;
	
	save = number;
	while (save) {
		save /= 10;
		digits++;
	}
	
	dest[length + digits] = 0;
	
	while (digits--) {
		digit = number % 10;
		number /= 10;
		
		dest[length + digits] = digit + 48;
	}
	
	if (is_negative) dest[length] = '-';
}

static void jm_strcat_escaped(char *json, const char *string) {
	int i, j, length;
	
	j = jm_strlen(json);
	length = jm_strlen(string);
	
	for (i=0; i<length; i++) {
		if (string[i] == '\"') {
			json[j++] = '\\';
			json[j++] = '\"';
		}
		else if (string[i] == '\n') {
			json[j++] = '\\';
			json[j++] = 'n';
		}
		else {
			json[j++] = string[i];
		}
	}
	
	json[j++] = 0;
}

/* PUBLIC FUNCTIONS IMPLEMENTATION */

void json_begin(char *json) {
	json += jm_strlen(json);
	
	if (*(json-1) == '}')  jm_strcat(json, ",");
	
	jm_strcat(json, "{");
}

void json_end(char *json) {
	json += jm_strlen(json) -1;
	
	if (*json != ',') json++;
	
	jm_strcpy(json, "}");
}

void json_array_begin(char *json) {
	json += jm_strlen(json);
	
	if (*(json-1) == ']')  jm_strcat(json, ",");
	
	jm_strcat(json, "[");
}

void json_array_end(char *json) {
	json += jm_strlen(json) -1;
	
	if (*json != ',') json++;
	
	jm_strcpy(json, "]");
}

void json_key(char *json, const char *key) {
	json += jm_strlen(json) -1;
	
	if (*json == '}') {
		jm_strcat(json, ",");
	}
	
	jm_strcat(json, "\"");
	jm_strcat(json, key);
	jm_strcat(json, "\"");
	jm_strcat(json, ":");
}

void json_value_string(char *json, const char *string) {
	jm_strcat(json, "\"");
	jm_strcat_escaped(json, string);
	jm_strcat(json, "\"");
	jm_strcat(json, ",");
}

void json_value_number(char *json, long int number) {
	jm_number_to_str(json, number);
	jm_strcat(json, ",");
}

void json_value_double(char *json, double number) {
	long int integer, decimal;
	
	if (number < 0) number -= 2*number;
	
	integer = (long int)number;
	decimal = (long int)(number * JM_DOUBLE_PRECISION) % JM_DOUBLE_PRECISION;
	
	while (decimal % 10 == 0) decimal /= 10;
	
	jm_number_to_str(json, integer);
	
	jm_strcat(json, ".");
	
	jm_number_to_str(json, decimal);
	
	jm_strcat(json, ",");
}

void json_value_bool(char *json, int boolean) {
	if (boolean) {
		jm_strcat(json, "true,");
	}
	else {
		jm_strcat(json, "false,");
	}
}

void json_value_null(char *json) {
	jm_strcat(json, "null,");
}

void json_value_raw(char *json, const char *raw) {
	jm_strcat(json, raw);
	jm_strcat(json, ",");
}

#endif /* JSON_MAKER_H */

#ifdef JM_WIDECHAR
#include <wchar.h>

/* MACROS */

#ifndef JM_DOUBLE_PRECISION
#define JM_DOUBLE_PRECISION 10000000
#endif /* JM_DOUBLE_PRECISION */

/* PUBLIC FUNCTIONS DECLARATION */

void json_begin_wc(wchar_t *json);
void json_end_wc(wchar_t *json);
void json_array_begin_wc(wchar_t *json);
void json_array_end_wc(wchar_t *json);
void json_key_wc(wchar_t *json, const wchar_t *key);
void json_value_string_wc(wchar_t *json, const wchar_t *string);
void json_value_number_wc(wchar_t *json, long int number);
void json_value_double_wc(wchar_t *json, double number);
void json_value_bool_wc(wchar_t *json, int boolean);
void json_value_null_wc(wchar_t *json);
void json_value_raw_wc(wchar_t *json, const wchar_t *raw);

/* PRIVATE FUNCTIONS DECLARATION */

static unsigned int jm_strlen_wc(const wchar_t *src);
static void jm_strcpy_wc(wchar_t *dest, const wchar_t *src);
static void jm_strcat_wc(wchar_t *dest, const wchar_t *src);
static void jm_number_to_str_wc(wchar_t *dest, long int number);
static void jm_strcat_escaped_wc(wchar_t *json, const wchar_t *string);

/* PRIVATE FUNCTIONS IMPLEMENTATION */

static unsigned int jm_strlen_wc(const wchar_t *src) {
	unsigned int i = 0;
	while (*(src + i)) {
		i++;
	}
	
	return i;
}

static void jm_strcpy_wc(wchar_t *dest, wchar_t *src) {
	unsigned int i, length;
	
	length = jm_strlen_wc(src);
	
	for (i=0; i<length; i++)
		dest[i] = src[i];
	
	dest[i] = 0;
}

static void jm_strcat_wc(wchar_t *dest, wchar_t *src) {
	jm_strcpy_wc(dest + jm_strlen_wc(dest), src);
}

static void jm_number_to_str_wc(wchar_t *dest, long int number) {
	unsigned int is_negative, digit, save;
	unsigned int digits = 0, length = jm_strlen_wc(dest);
	
	if (number < 0) {
		number -= 2*number;
		is_negative = 1;
	}
	else if (number == 0) {
		is_negative = 0;
		digits++;
	}
	else {
		is_negative = 0;
	}
	
	if (is_negative) digits++;
	
	save = number;
	while (save) {
		save /= 10;
		digits++;
	}
	
	dest[length + digits] = 0;
	
	while (digits--) {
		digit = number % 10;
		number /= 10;
		
		dest[length + digits] = digit + 48;
	}
	
	if (is_negative) dest[length] = '-';
}

static void jm_strcat_escaped_wc(wchar_t *json, wchar_t *string) {
	int i, j, length;
	
	j = wcslen(json);
	length = wcslen(string);
	
	for (i=0; i<length; i++) {
		if (string[i] == '\n' || string[i] == '\"') {
			json[j++] = '\\';
			json[j++] = string[i];
		}
		else {
			json[j++] = string[i];
		}
	}
	
	json[j++] = 0;
}

/* PUBLIC FUNCTIONS IMPLEMENTATION */

void json_begin_wc(wchar_t *json) {
	json += jm_strlen_wc(json);
	
	if (*(json-1) == L'}')  jm_strcat_wc(json, L",");
	
	jm_strcat_wc(json, L"{");
}

void json_end_wc(wchar_t *json) {
	json += jm_strlen_wc(json) -1;
	
	if (*json != L',') json++;
	
	jm_strcpy_wc(json, L"}");
}

void json_array_begin_wc(wchar_t *json) {
	json += jm_strlen_wc(json);
	
	if (*(json-1) == L']')  jm_strcat_wc(json, L",");
	
	jm_strcat_wc(json, L"[");
}

void json_array_end_wc(wchar_t *json) {
	json += jm_strlen_wc(json) -1;
	
	if (*json != L',') json++;
	
	jm_strcpy_wc(json, L"]");
}

void json_key_wc(wchar_t *json, wchar_t *key) {
	json += jm_strlen_wc(json) -1;
	
	if (*json == L'}') {
		jm_strcat_wc(json, L",");
	}
	
	jm_strcat_wc(json, L"\"");
	jm_strcat_wc(json, key);
	jm_strcat_wc(json, L"\"");
	jm_strcat_wc(json, L":");
}

void json_value_string_wc(wchar_t *json, wchar_t *string) {
	jm_strcat_wc(json, L"\"");
	jm_strcat_escaped_wc(json, string);
	jm_strcat_wc(json, L"\"");
	jm_strcat_wc(json, L",");
}

void json_value_number_wc(wchar_t *json, long int number) {
	jm_number_to_str_wc(json, number);
	jm_strcat_wc(json, L",");
}

void json_value_double_wc(wchar_t *json, double number) {
	long int integer, decimal;
	
	if (number < 0) number -= 2*number;
	
	integer = (long int)number;
	decimal = (long int)(number * JM_DOUBLE_PRECISION) % JM_DOUBLE_PRECISION;
	
	while (decimal % 10 == 0) decimal /= 10;
	
	jm_number_to_str_wc(json, integer);
	
	jm_strcat_wc(json, L".");
	
	jm_number_to_str_wc(json, decimal);
	
	jm_strcat_wc(json, L",");
}

void json_value_bool_wc(wchar_t *json, int boolean) {
	if (boolean) {
		jm_strcat_wc(json, L"true,");
	}
	else {
		jm_strcat_wc(json, L"false,");
	}
}

void json_value_null_wc(wchar_t *json) {
	jm_strcat_wc(json, L"null,");
}

void json_value_raw_wc(wchar_t *json, const wchar_t *raw) {
	jm_strcat_wc(json, raw);
	jm_strcat_wc(json, ",");
}

#endif /* JM_WIDECHAR */
