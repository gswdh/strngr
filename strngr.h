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

char *strngr_new(str_t *str, char *mem, const uint32_t mem_len);
char *strngr_new_s(str_t *str, char *mem, const uint32_t mem_len, const char *string);

void     strngr_strcat(str_t *dst, const str_t src);
char    *strngr_strchr(const str_t src, const char matcher);
void     strngr_strcpy(const str_t src, str_t *dst);
uint32_t strngr_strcspn(const str_t src, const char matcher);
uint32_t strngr_strlen(const str_t src);
void     strngr_strncat(str_t *dst, const str_t src, uint32_t n);
int32_t  strngr_strncmp(const str_t a, const str_t b, uint32_t n);
void     strngr_strncpy(const str_t src, str_t *dst, uint32_t n);
char    *strngr_strstr(const str_t hay, const str_t needle);

#endif
