#ifndef JSON_MAKER_H
#define JSON_MAKER_H

#include <stdio.h>

void json_begin(char *json);
void json_end(char *json);
void json_array_begin(char *json);
void json_array_end(char *json);
void json_key(char *json, char *key);
void json_value_string(char *json, char *string);
void json_value_number(char *json, long int number);
void json_value_double(char *json, double d);
void json_value_bool(char *json, char boolean);
void json_value_null(char *json);

static unsigned int jm_strlen(char *str) {
	unsigned int i = 0;
	while (*(str + i)) {
		i++;
	}
	
	return i;
}

static void jm_strcpy(char *dest, char *src) {
	unsigned int i, len;
	
	len = jm_strlen(src);
	
	for (i=0; i<len; i++)
		dest[i] = src[i];
}

static void jm_strcat(char *dest, char *src) {
	jm_strcpy(dest + jm_strlen(dest), src);
}

static void jm_itoa(char *dest, long int src) {
	unsigned int i, digit, digits, is_negative;
	
	i = 0;
	is_negative = 0;
	
	if (src < 0) {
		src -= 2*src;
		is_negative = 1;
		i++;
	}
	
	digits = src;
	
	while (digits) {
		digits /= 10;
		i++;
	}
	
	while (src) {
		digit = src % 10;
		src /= 10;
		
		dest[--i] = digit + 48;
	}
	
	if (is_negative) dest[--i] = '-';
}

extern void jm_ftoa(char *dest, double src) {
	//TODO
	(void)dest;
	(void)src;
}

void json_begin(char *json) {
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
	json += jm_strlen(json);
	
	if (*(json-1) == '}') jm_strcat(json, ",");
	jm_strcat(json, "\"");
	jm_strcat(json, key);
	jm_strcat(json, "\":");
}

void json_value_string(char *json, char *string) {
	jm_strcat(json, "\"");
	jm_strcat(json, string);
	jm_strcat(json, "\",");
}

void json_value_number(char *json, long int number) {
	char buffer[sizeof("INT_MAX=======")];
	
	jm_itoa(buffer, number);
	jm_strcat(json, buffer);
	jm_strcat(json, ",");
}

void json_value_double(char *json, double d) {
	json += jm_strlen(json);
	
	/* TODO: own implementation */
	sprintf(json, "%lf", d);
	
	jm_strcat(json, ",");
}

void json_value_bool(char *json, char boolean) {
	if (boolean) {
		jm_strcat(json, "true,");
	} else {
		jm_strcat(json, "false,");
	}
}

void json_value_null(char *json) {
	jm_strcat(json, "null,");
}

#endif /* JSON_MAKER_H */