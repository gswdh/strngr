#include "unity.h"

// Forward declarations of test functions
extern void setUp(void);
extern void tearDown(void);

// strngr_new tests
void test_strngr_new_null_str_pointer(void);
void test_strngr_new_null_mem_pointer(void);
void test_strngr_new_zero_length(void);
void test_strngr_new_valid_initialization(void);

// strngr_new_s tests
void test_strngr_new_s_null_str_pointer(void);
void test_strngr_new_s_null_mem_pointer(void);
void test_strngr_new_s_null_string_pointer(void);
void test_strngr_new_s_zero_length(void);
void test_strngr_new_s_valid_string_copy(void);
void test_strngr_new_s_string_longer_than_buffer(void);

// strngr_strlen tests
void test_strngr_strlen_null_string(void);
void test_strngr_strlen_valid_length(void);
void test_strngr_strlen_zero_length(void);

// strngr_strcspn tests
void test_strngr_strcspn_null_string(void);
void test_strngr_strcspn_character_found(void);
void test_strngr_strcspn_character_not_found(void);
void test_strngr_strcspn_empty_string(void);

// strngr_strchr tests
void test_strngr_strchr_null_string(void);
void test_strngr_strchr_character_found(void);
void test_strngr_strchr_character_not_found(void);
void test_strngr_strchr_first_character(void);

// strngr_strncpy tests
void test_strngr_strncpy_null_src_string(void);
void test_strngr_strncpy_null_dst_string(void);
void test_strngr_strncpy_normal_copy(void);
void test_strngr_strncpy_n_larger_than_src_len(void);
void test_strngr_strncpy_n_larger_than_dst_max_len(void);
void test_strngr_strncpy_zero_n(void);

// strngr_strcpy tests
void test_strngr_strcpy_null_src_string(void);
void test_strngr_strcpy_null_dst_string(void);
void test_strngr_strcpy_normal_copy(void);
void test_strngr_strcpy_src_longer_than_dst_max_len(void);

// strngr_strncat tests
void test_strngr_strncat_null_dst_string(void);
void test_strngr_strncat_null_src_string(void);
void test_strngr_strncat_normal_concatenation(void);
void test_strngr_strncat_n_larger_than_src_len(void);
void test_strngr_strncat_buffer_overflow_protection(void);
void test_strngr_strncat_exact_fit(void);

// strngr_strcat tests
void test_strngr_strcat_null_dst_string(void);
void test_strngr_strcat_null_src_string(void);
void test_strngr_strcat_normal_concatenation(void);
void test_strngr_strcat_buffer_overflow_protection(void);

// strngr_strncmp tests
void test_strngr_strncmp_null_a_string(void);
void test_strngr_strncmp_null_b_string(void);
void test_strngr_strncmp_empty_strings(void);
void test_strngr_strncmp_equal_strings(void);
void test_strngr_strncmp_unequal_strings_a_less(void);
void test_strngr_strncmp_unequal_strings_a_greater(void);
void test_strngr_strncmp_n_larger_than_a_len(void);
void test_strngr_strncmp_n_larger_than_b_len(void);
void test_strngr_strncmp_partial_match(void);

// strngr_strstr tests
void test_strngr_strstr_null_haystack(void);
void test_strngr_strstr_null_needle(void);
void test_strngr_strstr_needle_found(void);
void test_strngr_strstr_needle_not_found(void);
void test_strngr_strstr_needle_at_start(void);
void test_strngr_strstr_needle_longer_than_haystack(void);
void test_strngr_strstr_needle_equal_length_haystack(void);
void test_strngr_strstr_needle_longer_than_haystack_by_one(void);
void test_strngr_strstr_partial_match_not_found(void);

// strngr_strsub tests
void test_strngr_strsub_null_src_string(void);
void test_strngr_strsub_null_dst_string(void);
void test_strngr_strsub_positive_start_normal(void);
void test_strngr_strsub_positive_start_at_beginning(void);
void test_strngr_strsub_positive_start_partial(void);
void test_strngr_strsub_positive_start_single_char(void);
void test_strngr_strsub_positive_start_out_of_bounds(void);
void test_strngr_strsub_positive_start_length_exceeds_remaining(void);
void test_strngr_strsub_negative_start_minus_one(void);
void test_strngr_strsub_negative_start_minus_two(void);
void test_strngr_strsub_negative_start_from_end(void);
void test_strngr_strsub_negative_start_entire_string(void);
void test_strngr_strsub_negative_start_too_negative(void);
void test_strngr_strsub_negative_start_length_exceeds_remaining(void);
void test_strngr_strsub_length_exceeds_dst_max_len(void);
void test_strngr_strsub_zero_length(void);
void test_strngr_strsub_exact_fit(void);
void test_strngr_strsub_negative_start_exact_fit(void);
void test_strngr_strsub_positive_start_at_end(void);
void test_strngr_strsub_negative_start_single_char_at_end(void);
void test_strngr_strsub_middle_substring(void);
void test_strngr_strsub_negative_start_middle_substring(void);

int main(void)
{
    UNITY_BEGIN();

    // strngr_new tests
    RUN_TEST(test_strngr_new_null_str_pointer);
    RUN_TEST(test_strngr_new_null_mem_pointer);
    RUN_TEST(test_strngr_new_zero_length);
    RUN_TEST(test_strngr_new_valid_initialization);

    // strngr_new_s tests
    RUN_TEST(test_strngr_new_s_null_str_pointer);
    RUN_TEST(test_strngr_new_s_null_mem_pointer);
    RUN_TEST(test_strngr_new_s_null_string_pointer);
    RUN_TEST(test_strngr_new_s_zero_length);
    RUN_TEST(test_strngr_new_s_valid_string_copy);
    RUN_TEST(test_strngr_new_s_string_longer_than_buffer);

    // strngr_strlen tests
    RUN_TEST(test_strngr_strlen_null_string);
    RUN_TEST(test_strngr_strlen_valid_length);
    RUN_TEST(test_strngr_strlen_zero_length);

    // strngr_strcspn tests
    RUN_TEST(test_strngr_strcspn_null_string);
    RUN_TEST(test_strngr_strcspn_character_found);
    RUN_TEST(test_strngr_strcspn_character_not_found);
    RUN_TEST(test_strngr_strcspn_empty_string);

    // strngr_strchr tests
    RUN_TEST(test_strngr_strchr_null_string);
    RUN_TEST(test_strngr_strchr_character_found);
    RUN_TEST(test_strngr_strchr_character_not_found);
    RUN_TEST(test_strngr_strchr_first_character);

    // strngr_strncpy tests
    RUN_TEST(test_strngr_strncpy_null_src_string);
    RUN_TEST(test_strngr_strncpy_null_dst_string);
    RUN_TEST(test_strngr_strncpy_normal_copy);
    RUN_TEST(test_strngr_strncpy_n_larger_than_src_len);
    RUN_TEST(test_strngr_strncpy_n_larger_than_dst_max_len);
    RUN_TEST(test_strngr_strncpy_zero_n);

    // strngr_strcpy tests
    RUN_TEST(test_strngr_strcpy_null_src_string);
    RUN_TEST(test_strngr_strcpy_null_dst_string);
    RUN_TEST(test_strngr_strcpy_normal_copy);
    RUN_TEST(test_strngr_strcpy_src_longer_than_dst_max_len);

    // strngr_strncat tests
    RUN_TEST(test_strngr_strncat_null_dst_string);
    RUN_TEST(test_strngr_strncat_null_src_string);
    RUN_TEST(test_strngr_strncat_normal_concatenation);
    RUN_TEST(test_strngr_strncat_n_larger_than_src_len);
    RUN_TEST(test_strngr_strncat_buffer_overflow_protection);
    RUN_TEST(test_strngr_strncat_exact_fit);

    // strngr_strcat tests
    RUN_TEST(test_strngr_strcat_null_dst_string);
    RUN_TEST(test_strngr_strcat_null_src_string);
    RUN_TEST(test_strngr_strcat_normal_concatenation);
    RUN_TEST(test_strngr_strcat_buffer_overflow_protection);

    // strngr_strncmp tests
    RUN_TEST(test_strngr_strncmp_null_a_string);
    RUN_TEST(test_strngr_strncmp_null_b_string);
    RUN_TEST(test_strngr_strncmp_empty_strings);
    RUN_TEST(test_strngr_strncmp_equal_strings);
    RUN_TEST(test_strngr_strncmp_unequal_strings_a_less);
    RUN_TEST(test_strngr_strncmp_unequal_strings_a_greater);
    RUN_TEST(test_strngr_strncmp_n_larger_than_a_len);
    RUN_TEST(test_strngr_strncmp_n_larger_than_b_len);
    RUN_TEST(test_strngr_strncmp_partial_match);

    // strngr_strstr tests
    RUN_TEST(test_strngr_strstr_null_haystack);
    RUN_TEST(test_strngr_strstr_null_needle);
    RUN_TEST(test_strngr_strstr_needle_found);
    RUN_TEST(test_strngr_strstr_needle_not_found);
    RUN_TEST(test_strngr_strstr_needle_at_start);
    RUN_TEST(test_strngr_strstr_needle_longer_than_haystack);
    RUN_TEST(test_strngr_strstr_needle_equal_length_haystack);
    RUN_TEST(test_strngr_strstr_needle_longer_than_haystack_by_one);
    RUN_TEST(test_strngr_strstr_partial_match_not_found);

    // strngr_strsub tests
    RUN_TEST(test_strngr_strsub_null_src_string);
    RUN_TEST(test_strngr_strsub_null_dst_string);
    RUN_TEST(test_strngr_strsub_positive_start_normal);
    RUN_TEST(test_strngr_strsub_positive_start_at_beginning);
    RUN_TEST(test_strngr_strsub_positive_start_partial);
    RUN_TEST(test_strngr_strsub_positive_start_single_char);
    RUN_TEST(test_strngr_strsub_positive_start_out_of_bounds);
    RUN_TEST(test_strngr_strsub_positive_start_length_exceeds_remaining);
    RUN_TEST(test_strngr_strsub_negative_start_minus_one);
    RUN_TEST(test_strngr_strsub_negative_start_minus_two);
    RUN_TEST(test_strngr_strsub_negative_start_from_end);
    RUN_TEST(test_strngr_strsub_negative_start_entire_string);
    RUN_TEST(test_strngr_strsub_negative_start_too_negative);
    RUN_TEST(test_strngr_strsub_negative_start_length_exceeds_remaining);
    RUN_TEST(test_strngr_strsub_length_exceeds_dst_max_len);
    RUN_TEST(test_strngr_strsub_zero_length);
    RUN_TEST(test_strngr_strsub_exact_fit);
    RUN_TEST(test_strngr_strsub_negative_start_exact_fit);
    RUN_TEST(test_strngr_strsub_positive_start_at_end);
    RUN_TEST(test_strngr_strsub_negative_start_single_char_at_end);
    RUN_TEST(test_strngr_strsub_middle_substring);
    RUN_TEST(test_strngr_strsub_negative_start_middle_substring);

    return UNITY_END();
}

