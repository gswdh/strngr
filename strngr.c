#include "strngr.h"

#include <stddef.h>
#include <string.h>

char *strngr_new(str_t *str, char *mem, const uint32_t mem_len)
{
    if ((str == NULL) || (mem == NULL))
    {
        return NULL;
    }

    if (mem_len == 0U)
    {
        return NULL;
    }

    str->len     = 0U;
    str->max_len = mem_len;
    str->str     = mem;
    str->term    = 0U;

    memset((void *)str->str, 0U, str->max_len);

    return str->str;
}

char *strngr_new_s(str_t *str, char *mem, const uint32_t mem_len, const char *string)
{
    if ((str == NULL) || (mem == NULL) || (string == NULL))
    {
        return NULL;
    }

    if (mem_len == 0U)
    {
        return NULL;
    }

    str->len     = 0U;
    str->max_len = mem_len;
    str->str     = mem;
    str->term    = 0U;

    /* Get the incoming string length and minimise it */
    uint32_t cpy_len = (uint32_t)strlen(string);
    if (cpy_len > str->max_len)
    {
        cpy_len = str->max_len;
    }

    memset((void *)str->str, 0U, str->max_len);
    memcpy((void *)str->str, (const void *)string, (size_t)cpy_len);

    /* Set the length to match the copied data */
    str->len = cpy_len;

    return str->str;
}

void strngr_reset_to_empty(str_t *str)
{
    if (str == NULL)
    {
        return;
    }

    str->len = 0U;
    memset((void *)str->str, 0U, str->max_len);
}

void strngr_strcat(str_t *dst, const str_t src)
{
    if ((dst->str == NULL) || (src.str == NULL))
    {
        return;
    }

    /* Check for space in the destination */
    if (dst->max_len < (dst->len + src.len))
    {
        return;
    }

    strngr_strncat(dst, src, (const uint32_t)src.len);
}

char *strngr_strchr(const str_t src, const char matcher)
{
    if (src.str == NULL)
    {
        return NULL;
    }

    uint32_t pos = strngr_strcspn(src, matcher);

    /* By defintion of the strcspn behaviour, the string length is returned if nothing is found */
    if (pos >= src.len)
    {
        return NULL;
    }

    return &src.str[pos];
}

void strngr_strcpy(const str_t src, str_t *dst)
{
    if ((src.str == NULL) || (dst->str == NULL))
    {
        return;
    }

    uint32_t l = src.len;
    if (l > dst->max_len)
    {
        l = dst->max_len;
    }

    strngr_strncpy(src, dst, l);
}

uint32_t strngr_strcspn(const str_t src, const char matcher)
{
    if (src.str == NULL)
    {
        return 0U;
    }

    for (uint32_t i = 0U; i < src.len; i++)
    {
        if (src.str[i] == matcher)
        {
            return i;
        }
    }

    /* Nothing found so return the length of the input string */
    return src.len;
}

uint32_t strngr_strlen(const str_t src)
{
    if (src.str == NULL)
    {
        return 0U;
    }

    return src.len;
}

void strngr_strncat(str_t *dst, const str_t src, uint32_t n)
{
    if ((dst->str == NULL) || (src.str == NULL))
    {
        return;
    }

    if (n > src.len)
    {
        n = src.len;
    }

    /* Check for space in the destination */
    if (dst->max_len < (dst->len + n))
    {
        return;
    }

    /* Do the mem copy */
    memcpy((void *)(dst->str + dst->len), (void *)src.str, (size_t)n);

    /* Update the string length */
    dst->len = dst->len + n;
}

int32_t strngr_strncmp(const str_t a, const str_t b, uint32_t n)
{
    if ((a.str == NULL) || (b.str == NULL))
    {
        return 0L;
    }

    /* Compare up to n characters, stopping at the shorter string's length */
    uint32_t min_len = a.len;
    if (b.len < min_len)
    {
        min_len = b.len;
    }

    if (n > min_len)
    {
        n = min_len;
    }

    /* Compare the characters */
    for (uint32_t i = 0U; i < n; i++)
    {
        int32_t d = (int32_t)a.str[i] - (int32_t)b.str[i];

        if (d != 0L)
        {
            return d;
        }
    }

    /* All compared characters match - return 0 (standard strncmp behavior) */
    return 0L;
}

void strngr_strncpy(const str_t src, str_t *dst, uint32_t n)
{
    if ((src.str == NULL) || (dst->str == NULL))
    {
        return;
    }

    /* Limit n to available space */
    if (dst->max_len < n)
    {
        n = dst->max_len;
    }

    /* Determine how many characters to copy */
    uint32_t copy_len = src.len;
    if (copy_len > n)
    {
        copy_len = n;
    }

    /* Copy the characters */
    memcpy((void *)dst->str, (void *)src.str, (size_t)copy_len);

    /* If source is shorter than n, pad with zeros (like standard strncpy) */
    if (copy_len < n)
    {
        memset((void *)(dst->str + copy_len), 0U, (size_t)(n - copy_len));
    }

    /* Update the length */
    dst->len = copy_len;
}

char *strngr_strstr(const str_t hay, const str_t needle)
{
    if ((hay.str == NULL) || (needle.str == NULL))
    {
        return NULL;
    }

    if (hay.len < needle.len)
    {
        return NULL;
    }

    const uint32_t search_len = hay.len - needle.len;
    for (uint32_t i = 0U; i <= search_len; i++)
    {
        uint32_t j = 0U;
        for (j = 0U; j < needle.len; j++)
        {
            if (needle.str[j] != hay.str[i + j])
            {
                break;
            }
        }

        if (j == needle.len)
        {
            return &hay.str[i];
        }
    }

    return NULL;
}

void strngr_strsub(str_t *dst, const str_t src, const int32_t start, const uint32_t length)
{
    if ((src.str == NULL) || (dst->str == NULL))
    {
        return;
    }

    /* Convert negative start to offset from end */
    int32_t actual_start = start;
    if (start < 0)
    {
        actual_start = (int32_t)src.len + start;
    }

    /* Validate start position */
    if ((actual_start < 0) || ((uint32_t)actual_start >= src.len))
    {
        return;
    }

    /* Check that length doesn't exceed remaining string from start position */
    if (length > (src.len - (uint32_t)actual_start))
    {
        return;
    }

    /* Check that length doesn't exceed destination capacity */
    if (length > dst->max_len)
    {
        return;
    }

    memcpy((void *)dst->str, (void *)(src.str + actual_start), (size_t)length);
    dst->len = length;
}
