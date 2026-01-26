#ifndef __STRNGR__
#define __STRNGR__

#include <stdint.h>

typedef struct
{
    uint32_t max_len;
    uint32_t len;
    char    *str;
    uint32_t term;
} str_t;

#define STR_T_FROM_CHAR(char_str) \
    ((str_t){.str = char_str, .len = strlen(char_str), .max_len = strlen(char_str), .term = 0U})

char *strngr_new(str_t *str, char *mem, const uint32_t mem_len);
str_t strngr_new_s(char *mem, const uint32_t mem_len, const char *string);

void     strngr_reset_to_empty(str_t *str);
void     strngr_strcat(str_t *dst, const str_t src);
char    *strngr_strchr(const str_t src, const char matcher);
void     strngr_strcpy(const str_t src, str_t *dst);
uint32_t strngr_strcspn(const str_t src, const char matcher);
uint32_t strngr_strlen(const str_t src);
void     strngr_strncat(str_t *dst, const str_t src, uint32_t n);
int32_t  strngr_strncmp(const str_t a, const str_t b, uint32_t n);
void     strngr_strncpy(const str_t src, str_t *dst, uint32_t n);
str_t    strngr_strstr(const str_t hay, const str_t needle);
str_t    strngr_strsub(const str_t src, const int32_t start, const int32_t end);

#endif
