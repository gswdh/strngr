#include "unity.h"
#include "../strngr.h"
#include <string.h>
#include <stdint.h>

// Test fixtures
static char buffer1[100];
static char buffer2[100];
static char buffer3[100];
static str_t str1;
static str_t str2;
static str_t str3;

void setUp(void)
{
    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));
    memset(buffer3, 0, sizeof(buffer3));
    memset(&str1, 0, sizeof(str_t));
    memset(&str2, 0, sizeof(str_t));
    memset(&str3, 0, sizeof(str_t));
}

void tearDown(void)
{
    // Cleanup if needed
}

// ============================================================================
// Tests for strngr_new
// ============================================================================

void test_strngr_new_null_str_pointer(void)
{
    char mem[10];
    TEST_ASSERT_NULL(strngr_new(NULL, mem, 10));
}

void test_strngr_new_null_mem_pointer(void)
{
    str_t str;
    TEST_ASSERT_NULL(strngr_new(&str, NULL, 10));
}

void test_strngr_new_zero_length(void)
{
    char mem[10];
    str_t str;
    TEST_ASSERT_NULL(strngr_new(&str, mem, 0));
}

void test_strngr_new_valid_initialization(void)
{
    char mem[10];
    str_t str;
    char *result = strngr_new(&str, mem, 10);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(mem, result);
    TEST_ASSERT_EQUAL_UINT32(0, str.len);
    TEST_ASSERT_EQUAL_UINT32(10, str.max_len);
    TEST_ASSERT_EQUAL_PTR(mem, str.str);
    TEST_ASSERT_EQUAL_UINT32(0, str.term);
    
    // Verify memory is zeroed
    for (uint32_t i = 0; i < 10; i++)
    {
        TEST_ASSERT_EQUAL(0, mem[i]);
    }
}

// ============================================================================
// Tests for strngr_new_s
// ============================================================================

void test_strngr_new_s_null_str_pointer(void)
{
    char mem[10];
    TEST_ASSERT_NULL(strngr_new_s(NULL, mem, 10, "test"));
}

void test_strngr_new_s_null_mem_pointer(void)
{
    str_t str;
    TEST_ASSERT_NULL(strngr_new_s(&str, NULL, 10, "test"));
}

void test_strngr_new_s_null_string_pointer(void)
{
    char mem[10];
    str_t str;
    TEST_ASSERT_NULL(strngr_new_s(&str, mem, 10, NULL));
}

void test_strngr_new_s_zero_length(void)
{
    char mem[10];
    str_t str;
    TEST_ASSERT_NULL(strngr_new_s(&str, mem, 0, "test"));
}

void test_strngr_new_s_valid_string_copy(void)
{
    char mem[20];
    str_t str;
    const char *input = "Hello";
    char *result = strngr_new_s(&str, mem, 20, input);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(mem, result);
    TEST_ASSERT_EQUAL_UINT32(strlen(input), str.len);
    TEST_ASSERT_EQUAL_UINT32(20, str.max_len);
    TEST_ASSERT_EQUAL_PTR(mem, str.str);
    TEST_ASSERT_EQUAL_UINT32(0, str.term);
    
    // Verify string was copied
    TEST_ASSERT_EQUAL_MEMORY(input, mem, strlen(input));
}

void test_strngr_new_s_string_longer_than_buffer(void)
{
    char mem[5];
    str_t str;
    const char *input = "Hello World";
    char *result = strngr_new_s(&str, mem, 5, input);
    
    TEST_ASSERT_NOT_NULL(result);
    // Should only copy first 5 characters
    TEST_ASSERT_EQUAL_UINT32(5, str.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", mem, 5);
}

// ============================================================================
// Tests for strngr_strlen
// ============================================================================

void test_strngr_strlen_null_string(void)
{
    str_t str;
    str.str = NULL;
    str.len = 0;
    TEST_ASSERT_EQUAL_UINT32(0, strngr_strlen(str));
}

void test_strngr_strlen_valid_length(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str1.len = 5;
    TEST_ASSERT_EQUAL_UINT32(5, strngr_strlen(str1));
}

void test_strngr_strlen_zero_length(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str1.len = 0;
    TEST_ASSERT_EQUAL_UINT32(0, strngr_strlen(str1));
}

// ============================================================================
// Tests for strngr_strcspn
// ============================================================================

void test_strngr_strcspn_null_string(void)
{
    str_t str;
    str.str = NULL;
    str.len = 0;
    TEST_ASSERT_EQUAL_UINT32(0, strngr_strcspn(str, 'a'));
}

void test_strngr_strcspn_character_found(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    TEST_ASSERT_EQUAL_UINT32(1, strngr_strcspn(str1, 'e'));
    TEST_ASSERT_EQUAL_UINT32(0, strngr_strcspn(str1, 'H'));
    TEST_ASSERT_EQUAL_UINT32(4, strngr_strcspn(str1, 'o'));
}

void test_strngr_strcspn_character_not_found(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    TEST_ASSERT_EQUAL_UINT32(5, strngr_strcspn(str1, 'x'));
}

void test_strngr_strcspn_empty_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str1.len = 0;
    TEST_ASSERT_EQUAL_UINT32(0, strngr_strcspn(str1, 'a'));
}

// ============================================================================
// Tests for strngr_strchr
// ============================================================================

void test_strngr_strchr_null_string(void)
{
    str_t str;
    str.str = NULL;
    str.len = 0;
    TEST_ASSERT_NULL(strngr_strchr(str, 'a'));
}

void test_strngr_strchr_character_found(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    char *result = strngr_strchr(str1, 'e');
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(&buffer1[1], result);
    TEST_ASSERT_EQUAL('e', *result);
}

void test_strngr_strchr_character_not_found(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    TEST_ASSERT_NULL(strngr_strchr(str1, 'x'));
}

void test_strngr_strchr_first_character(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    char *result = strngr_strchr(str1, 'H');
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(&buffer1[0], result);
}

// ============================================================================
// Tests for strngr_strncpy
// ============================================================================

void test_strngr_strncpy_null_src_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str_t src;
    src.str = NULL;
    src.len = 0;
    
    strngr_strncpy(src, &str1, 5);
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(0, str1.len);
}

void test_strngr_strncpy_null_dst_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    str_t dst;
    dst.str = NULL;
    
    strngr_strncpy(str1, &dst, 5);
    // Should not crash, but dst remains unchanged
}

void test_strngr_strncpy_normal_copy(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strncpy(str1, &str2, 5);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

void test_strngr_strncpy_n_larger_than_src_len(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strncpy(str1, &str2, 10);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

void test_strngr_strncpy_n_larger_than_dst_max_len(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, 5);
    
    strngr_strncpy(str1, &str2, 10);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

void test_strngr_strncpy_zero_n(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strncpy(str1, &str2, 0);
    
    TEST_ASSERT_EQUAL_UINT32(0, str2.len);
}

// ============================================================================
// Tests for strngr_strcpy
// ============================================================================

void test_strngr_strcpy_null_src_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str_t src;
    src.str = NULL;
    src.len = 0;
    
    strngr_strcpy(src, &str1);
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(0, str1.len);
}

void test_strngr_strcpy_null_dst_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    str_t dst;
    dst.str = NULL;
    
    strngr_strcpy(str1, &dst);
    // Should not crash
}

void test_strngr_strcpy_normal_copy(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strcpy(str1, &str2);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

void test_strngr_strcpy_src_longer_than_dst_max_len(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, 5);
    
    strngr_strcpy(str1, &str2);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

// ============================================================================
// Tests for strngr_strncat
// ============================================================================

void test_strngr_strncat_null_dst_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    str_t dst;
    dst.str = NULL;
    
    strngr_strncat(&dst, str1, 5);
    // Should not crash
}

void test_strngr_strncat_null_src_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str_t src;
    src.str = NULL;
    src.len = 0;
    
    strngr_strncat(&str1, src, 5);
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(0, str1.len);
}

void test_strngr_strncat_normal_concatenation(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "World");
    str2.len = 5;
    
    strngr_strncat(&str1, str2, 5);
    
    TEST_ASSERT_EQUAL_UINT32(10, str1.len);
    TEST_ASSERT_EQUAL_MEMORY("HelloWorld", buffer1, 10);
}

void test_strngr_strncat_n_larger_than_src_len(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hi");
    str2.len = 2;
    
    strngr_strncat(&str1, str2, 10);
    
    TEST_ASSERT_EQUAL_UINT32(7, str1.len);
    TEST_ASSERT_EQUAL_MEMORY("HelloHi", buffer1, 7);
}

void test_strngr_strncat_buffer_overflow_protection(void)
{
    strngr_new(&str1, buffer1, 9); // max_len=9, so 5+5=10 would overflow
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "World");
    str2.len = 5;
    
    strngr_strncat(&str1, str2, 5); // Would exceed max_len (5+5=10 > 9)
    
    // Should not modify since it would overflow
    TEST_ASSERT_EQUAL_UINT32(5, str1.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer1, 5);
}

void test_strngr_strncat_exact_fit(void)
{
    strngr_new(&str1, buffer1, 10);
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "World");
    str2.len = 5;
    
    strngr_strncat(&str1, str2, 5);
    
    TEST_ASSERT_EQUAL_UINT32(10, str1.len);
    TEST_ASSERT_EQUAL_MEMORY("HelloWorld", buffer1, 10);
}

// ============================================================================
// Tests for strngr_strcat
// ============================================================================

void test_strngr_strcat_null_dst_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    str_t dst;
    dst.str = NULL;
    
    strngr_strcat(&dst, str1);
    // Should not crash
}

void test_strngr_strcat_null_src_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str_t src;
    src.str = NULL;
    src.len = 0;
    
    strngr_strcat(&str1, src);
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(0, str1.len);
}

void test_strngr_strcat_normal_concatenation(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "World");
    str2.len = 5;
    
    strngr_strcat(&str1, str2);
    
    TEST_ASSERT_EQUAL_UINT32(10, str1.len);
    TEST_ASSERT_EQUAL_MEMORY("HelloWorld", buffer1, 10);
}

void test_strngr_strcat_buffer_overflow_protection(void)
{
    strngr_new(&str1, buffer1, 9); // max_len=9, so 5+5=10 would overflow
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "World");
    str2.len = 5;
    
    strngr_strcat(&str1, str2); // Would exceed max_len (5+5=10 > 9)
    
    // Should not modify since it would overflow
    TEST_ASSERT_EQUAL_UINT32(5, str1.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer1, 5);
}

// ============================================================================
// Tests for strngr_strncmp
// ============================================================================

void test_strngr_strncmp_null_a_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    str_t a;
    a.str = NULL;
    a.len = 0;
    
    TEST_ASSERT_EQUAL_INT32(0, strngr_strncmp(a, str1, 5));
}

void test_strngr_strncmp_null_b_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    str_t b;
    b.str = NULL;
    b.len = 0;
    
    TEST_ASSERT_EQUAL_INT32(0, strngr_strncmp(str1, b, 5));
}

void test_strngr_strncmp_empty_strings(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str1.len = 0;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    str2.len = 0;
    
    TEST_ASSERT_EQUAL_INT32(0, strngr_strncmp(str1, str2, 5));
}

void test_strngr_strncmp_equal_strings(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hello");
    str2.len = 5;
    
    TEST_ASSERT_EQUAL_INT32(0, strngr_strncmp(str1, str2, 5));
}

void test_strngr_strncmp_unequal_strings_a_less(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "World");
    str2.len = 5;
    
    int32_t result = strngr_strncmp(str1, str2, 5);
    TEST_ASSERT_LESS_THAN_INT32(0, result);
}

void test_strngr_strncmp_unequal_strings_a_greater(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "World");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hello");
    str2.len = 5;
    
    int32_t result = strngr_strncmp(str1, str2, 5);
    TEST_ASSERT_GREATER_THAN_INT32(0, result);
}

void test_strngr_strncmp_n_larger_than_a_len(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hi");
    str1.len = 2;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hello");
    str2.len = 5;
    
    // Should compare only 2 characters
    TEST_ASSERT_NOT_EQUAL_INT32(0, strngr_strncmp(str1, str2, 5));
}

void test_strngr_strncmp_n_larger_than_b_len(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hi");
    str2.len = 2;
    
    // Should compare only 2 characters
    TEST_ASSERT_NOT_EQUAL_INT32(0, strngr_strncmp(str1, str2, 5));
}

void test_strngr_strncmp_partial_match(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Help");
    str2.len = 4;
    
    // First 3 characters match
    TEST_ASSERT_EQUAL_INT32(0, strngr_strncmp(str1, str2, 3));
    // 4th character differs
    TEST_ASSERT_NOT_EQUAL_INT32(0, strngr_strncmp(str1, str2, 4));
}

// ============================================================================
// Tests for strngr_strstr
// ============================================================================

void test_strngr_strstr_null_haystack(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "needle");
    str1.len = 6;
    
    str_t hay;
    hay.str = NULL;
    hay.len = 0;
    
    TEST_ASSERT_NULL(strngr_strstr(hay, str1));
}

void test_strngr_strstr_null_needle(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "haystack");
    str1.len = 8;
    
    str_t needle;
    needle.str = NULL;
    needle.len = 0;
    
    TEST_ASSERT_NULL(strngr_strstr(str1, needle));
}

void test_strngr_strstr_needle_found(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "World");
    str2.len = 5;
    
    char *result = strngr_strstr(str1, str2);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(&buffer1[6], result);
    TEST_ASSERT_EQUAL_MEMORY("World", result, 5);
}

void test_strngr_strstr_needle_not_found(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Test");
    str2.len = 4;
    
    TEST_ASSERT_NULL(strngr_strstr(str1, str2));
}

void test_strngr_strstr_needle_at_start(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hello");
    str2.len = 5;
    
    char *result = strngr_strstr(str1, str2);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(&buffer1[0], result);
}

void test_strngr_strstr_needle_longer_than_haystack(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hi");
    str1.len = 2;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hello");
    str2.len = 5;
    
    TEST_ASSERT_NULL(strngr_strstr(str1, str2));
}

void test_strngr_strstr_needle_equal_length_haystack(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hello");
    str2.len = 5;
    
    char *result = strngr_strstr(str1, str2);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(&buffer1[0], result);
}

void test_strngr_strstr_needle_longer_than_haystack_by_one(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Hello!");
    str2.len = 6;
    
    TEST_ASSERT_NULL(strngr_strstr(str1, str2));
}

void test_strngr_strstr_partial_match_not_found(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "Worlx");
    str2.len = 5;
    
    TEST_ASSERT_NULL(strngr_strstr(str1, str2));
}

// ============================================================================
// Tests for strngr_strsub
// ============================================================================

void test_strngr_strsub_null_src_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    str_t src;
    src.str = NULL;
    src.len = 0;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "test");
    str2.len = 4;
    
    strngr_strsub(&str2, src, 0, 2);
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(4, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("test", buffer2, 4);
}

void test_strngr_strsub_null_dst_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    str_t dst;
    dst.str = NULL;
    
    strngr_strsub(&dst, str1, 0, 2);
    // Should not crash
}

void test_strngr_strsub_positive_start_normal(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, 6, 5);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("World", buffer2, 5);
}

void test_strngr_strsub_positive_start_at_beginning(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, 0, 5);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

void test_strngr_strsub_positive_start_partial(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, 0, 5);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

void test_strngr_strsub_positive_start_single_char(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, 2, 1);
    
    TEST_ASSERT_EQUAL_UINT32(1, str2.len);
    TEST_ASSERT_EQUAL('l', buffer2[0]);
}

void test_strngr_strsub_positive_start_out_of_bounds(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "test");
    str2.len = 4;
    
    strngr_strsub(&str2, str1, 10, 2);
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(4, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("test", buffer2, 4);
}

void test_strngr_strsub_positive_start_length_exceeds_remaining(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "test");
    str2.len = 4;
    
    strngr_strsub(&str2, str1, 3, 5); // length 5 but only 2 chars remain
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(4, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("test", buffer2, 4);
}

void test_strngr_strsub_negative_start_minus_one(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, -1, 1);
    
    TEST_ASSERT_EQUAL_UINT32(1, str2.len);
    TEST_ASSERT_EQUAL('o', buffer2[0]);
}

void test_strngr_strsub_negative_start_minus_two(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, -2, 2);
    
    TEST_ASSERT_EQUAL_UINT32(2, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("lo", buffer2, 2);
}

void test_strngr_strsub_negative_start_from_end(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, -5, 5);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("World", buffer2, 5);
}

void test_strngr_strsub_negative_start_entire_string(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, -5, 5);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

void test_strngr_strsub_negative_start_too_negative(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "test");
    str2.len = 4;
    
    strngr_strsub(&str2, str1, -10, 2);
    // Should not modify destination (start would be -5, invalid)
    TEST_ASSERT_EQUAL_UINT32(4, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("test", buffer2, 4);
}

void test_strngr_strsub_negative_start_length_exceeds_remaining(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "test");
    str2.len = 4;
    
    strngr_strsub(&str2, str1, -3, 5); // length 5 but only 3 chars remain
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(4, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("test", buffer2, 4);
}

void test_strngr_strsub_length_exceeds_dst_max_len(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, 5); // max_len = 5
    
    strcpy(buffer2, "test");
    str2.len = 4;
    
    strngr_strsub(&str2, str1, 0, 10); // length 10 > dst max_len 5
    // Should not modify destination
    TEST_ASSERT_EQUAL_UINT32(4, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("test", buffer2, 4);
}

void test_strngr_strsub_zero_length(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "test");
    str2.len = 4;
    
    strngr_strsub(&str2, str1, 0, 0);
    
    TEST_ASSERT_EQUAL_UINT32(0, str2.len);
}

void test_strngr_strsub_exact_fit(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, 5); // max_len = 5
    
    strngr_strsub(&str2, str1, 0, 5);
    
    TEST_ASSERT_EQUAL_UINT32(5, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("Hello", buffer2, 5);
}

void test_strngr_strsub_negative_start_exact_fit(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, 3); // max_len = 3
    
    strngr_strsub(&str2, str1, -3, 3);
    
    TEST_ASSERT_EQUAL_UINT32(3, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("llo", buffer2, 3);
}

void test_strngr_strsub_positive_start_at_end(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    strcpy(buffer2, "test");
    str2.len = 4;
    
    strngr_strsub(&str2, str1, 5, 1);
    // Should not modify (start equals length, out of bounds)
    TEST_ASSERT_EQUAL_UINT32(4, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("test", buffer2, 4);
}

void test_strngr_strsub_negative_start_single_char_at_end(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello");
    str1.len = 5;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, -1, 1);
    
    TEST_ASSERT_EQUAL_UINT32(1, str2.len);
    TEST_ASSERT_EQUAL('o', buffer2[0]);
}

void test_strngr_strsub_middle_substring(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, 2, 3);
    
    TEST_ASSERT_EQUAL_UINT32(3, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("llo", buffer2, 3);
}

void test_strngr_strsub_negative_start_middle_substring(void)
{
    strngr_new(&str1, buffer1, sizeof(buffer1));
    strcpy(buffer1, "Hello World");
    str1.len = 11;
    
    strngr_new(&str2, buffer2, sizeof(buffer2));
    
    strngr_strsub(&str2, str1, -9, 3);
    
    TEST_ASSERT_EQUAL_UINT32(3, str2.len);
    TEST_ASSERT_EQUAL_MEMORY("llo", buffer2, 3);
}

