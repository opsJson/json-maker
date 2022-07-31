#ifndef JSON_MAKER_H
#define JSON_MAKER_H

/* MACROS */

#ifndef JM_DOUBLE_PRECISION
#define JM_DOUBLE_PRECISION 10000000
#endif

/* PUBLIC FUNCTIONS DECLARATION */

void json_begin(char *json);
void json_end(char *json);
void json_array_begin(char *json);
void json_array_end(char *json);
void json_key(char *json, char *key);
void json_value_string(char *json, char *string);
void json_value_number(char *json, long int number);
void json_value_double(char *json, double number);
void json_value_bool(char *json, int boolean);
void json_value_null(char *json);

/* PRIVATE FUNCTIONS DECLARATION */

static unsigned int jm_strlen(char *src);
static void jm_strcpy(char *dest, char *src);
static void jm_strcat(char *dest, char *src);
static void jm_number_to_str(char *dest, long int number);

/* PRIVATE FUNCTIONS IMPLEMENTATION */

static unsigned int jm_strlen(char *src) {
	unsigned int i = 0;
	while (*(src + i)) {
		i++;
	}
	
	return i;
}

static void jm_strcpy(char *dest, char *src) {
	unsigned int i, length;
	
	length = jm_strlen(src);
	
	for (i=0; i<length; i++)
		dest[i] = src[i];
	
	dest[i] = 0;
}

static void jm_strcat(char *dest, char *src) {
	jm_strcpy(dest + jm_strlen(dest), src);
}

static void jm_number_to_str(char *dest, long int number) {
	unsigned int is_negative, digit, save;
	unsigned int digits = 0, length = jm_strlen(dest);
	
	if (number < 0) {
		number -= 2*number;
		is_negative = 1;
	}
	else is_negative = 0;
	
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
	jm_strcat(json, "[");
}

void json_array_end(char *json) {
	json += jm_strlen(json) -1;
	
	if (*json != ',') json++;
	
	jm_strcpy(json, "],");
}

void json_key(char *json, char *key) {
	json += jm_strlen(json) -1;
	
	if (*json == '}') {
		jm_strcat(json, ",");
	}
	
	jm_strcat(json, "\"");
	jm_strcat(json, key);
	jm_strcat(json, "\"");
	jm_strcat(json, ":");
}

void json_value_string(char *json, char *string) {
	jm_strcat(json, "\"");
	jm_strcat(json, string);
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

#endif /* JSON_MAKER_H */