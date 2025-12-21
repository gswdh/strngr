# Strngr - MISRA-Compliant C String Library

A lightweight, mission-critical string library for embedded systems and microcontroller applications. Strngr provides safe, bounds-checked string operations that are compatible with MISRA C guidelines and designed for both desktop development and embedded deployment.

## Overview

Strngr is a C string library that uses a length-based string representation (`str_t`) instead of null-terminated strings. This design provides:

- **Buffer overflow protection** - All operations check bounds before execution
- **MISRA compliance** - Designed for mission-critical and safety-critical systems
- **Cross-platform** - Compiles and runs on desktop (for testing) and embedded targets
- **Deterministic behavior** - No reliance on null terminators or undefined behavior
- **Memory safety** - Explicit length tracking prevents buffer overruns

## Features

- ✅ MISRA C compliant design
- ✅ Bounds checking on all operations
- ✅ 100% test coverage with Unity testing framework
- ✅ Standard `string.h` equivalent behavior
- ✅ Zero dynamic memory allocation
- ✅ Suitable for embedded/microcontroller targets
- ✅ Comprehensive unit test suite (59 tests)

## Project Structure

```
strngr/
├── strngr.h          # Library header file
├── strngr.c          # Library implementation
├── Makefile            # Build system with test and coverage targets
├── README.md           # This file
└── tests/
    ├── AllTests.c      # Test runner
    ├── test_strngr.c # Comprehensive test suite
    └── unity/          # Unity testing framework
        ├── unity.h
        ├── unity.c
        └── unity_internals.h
```

## API Reference

### Data Structure

```c
typedef struct
{
    uint32_t max_len;  // Maximum buffer size
    uint32_t len;      // Current string length
    char    *str;      // Pointer to string buffer
    uint32_t term;     // Reserved for future use
} str_t;
```

### Initialization Functions

#### `strngr_new`
Initialize an empty string structure.

```c
char *strngr_new(str_t *str, char *mem, const uint32_t mem_len);
```

- **Parameters:**
  - `str` - Pointer to `str_t` structure to initialize
  - `mem` - Pointer to pre-allocated memory buffer
  - `mem_len` - Size of the memory buffer
- **Returns:** Pointer to the string buffer on success, `NULL` on error
- **Behavior:** Initializes the string structure and zeros the buffer

#### `strngr_new_s`
Initialize a string structure with a C string.

```c
char *strngr_new_s(str_t *str, char *mem, const uint32_t mem_len, const char *string);
```

- **Parameters:**
  - `str` - Pointer to `str_t` structure to initialize
  - `mem` - Pointer to pre-allocated memory buffer
  - `mem_len` - Size of the memory buffer
  - `string` - Null-terminated C string to copy
- **Returns:** Pointer to the string buffer on success, `NULL` on error
- **Behavior:** Copies the C string into the buffer (truncated if too long) and sets the length

### String Operations

#### `strngr_strlen`
Get the length of a string.

```c
uint32_t strngr_strlen(const str_t src);
```

- **Returns:** Length of the string, or 0 if `src.str` is NULL

#### `strngr_strcpy`
Copy a string (equivalent to `strcpy`).

```c
void strngr_strcpy(const str_t src, str_t *dst);
```

- **Behavior:** Copies the entire source string to destination, truncated if destination buffer is too small

#### `strngr_strncpy`
Copy up to `n` characters (equivalent to `strncpy`).

```c
void strngr_strncpy(const str_t src, str_t *dst, uint32_t n);
```

- **Behavior:** Copies up to `n` characters, pads with zeros if source is shorter than `n`

#### `strngr_strcat`
Concatenate strings (equivalent to `strcat`).

```c
void strngr_strcat(str_t *dst, const str_t src);
```

- **Behavior:** Appends source to destination, returns early if buffer would overflow

#### `strngr_strncat`
Concatenate up to `n` characters (equivalent to `strncat`).

```c
void strngr_strncat(str_t *dst, const str_t src, uint32_t n);
```

- **Behavior:** Appends up to `n` characters from source to destination

#### `strngr_strcmp` / `strngr_strncmp`
Compare strings (equivalent to `strncmp`).

```c
int32_t strngr_strncmp(const str_t a, const str_t b, uint32_t n);
```

- **Returns:** 
  - `0` if strings are equal
  - Negative value if `a < b`
  - Positive value if `a > b`

#### `strngr_strchr`
Find first occurrence of a character (equivalent to `strchr`).

```c
char *strngr_strchr(const str_t src, const char matcher);
```

- **Returns:** Pointer to first occurrence, or `NULL` if not found

#### `strngr_strcspn`
Find position of first occurrence of a character.

```c
uint32_t strngr_strcspn(const str_t src, const char matcher);
```

- **Returns:** Index of first occurrence, or `src.len` if not found

#### `strngr_strstr`
Find substring (equivalent to `strstr`).

```c
char *strngr_strstr(const str_t hay, const str_t needle);
```

- **Returns:** Pointer to first occurrence of `needle` in `hay`, or `NULL` if not found

## Usage Example

```c
#include "strngr.h"
#include <stdio.h>

int main(void)
{
    // Allocate buffers
    char buffer1[100];
    char buffer2[100];
    str_t str1, str2;
    
    // Initialize strings
    strngr_new_s(&str1, buffer1, sizeof(buffer1), "Hello");
    strngr_new_s(&str2, buffer2, sizeof(buffer2), " World");
    
    // Concatenate
    strngr_strcat(&str1, str2);
    
    // Get length
    uint32_t len = strngr_strlen(str1);
    printf("Length: %u\n", len);
    
    // Compare strings
    str_t str3;
    char buffer3[100];
    strngr_new_s(&str3, buffer3, sizeof(buffer3), "Hello World");
    
    if (strngr_strncmp(str1, str3, len) == 0)
    {
        printf("Strings match!\n");
    }
    
    return 0;
}
```

## Building

### Prerequisites

- GCC or Clang compiler
- Make
- (Optional) lcov for coverage reports

### Build Targets

```bash
# Build test executable
make

# Run tests
make test

# Generate coverage report (requires lcov)
make coverage

# Clean build artifacts
make clean

# Show help
make help
```

### Compilation Flags

The Makefile uses:
- `-std=c99` - C99 standard
- `-Wall -Wextra -Wpedantic` - Strict warnings
- `-fprofile-arcs -ftest-coverage` - Coverage instrumentation
- `-g -O0` - Debug symbols, no optimization

## Testing

The project includes a comprehensive test suite using the Unity testing framework:

- **59 test cases** covering all functions
- **100% code coverage** target
- Tests run on desktop environment
- Library compiles for both desktop and embedded targets

### Running Tests

```bash
make test
```

### Coverage Report

```bash
make coverage
```

This generates an HTML coverage report in `coverage_report/index.html`.

## MISRA Compliance

This library is designed with MISRA C guidelines in mind:

- ✅ No dynamic memory allocation
- ✅ Bounds checking on all operations
- ✅ No reliance on undefined behavior
- ✅ Explicit length tracking (no null terminator dependencies)
- ✅ Safe string operations for mission-critical systems

## Cross-Platform Support

- **Desktop Development:** Linux, macOS, Windows (with GCC/Clang)
- **Embedded Targets:** Microcontrollers, RTOS environments
- **Testing:** Performed on desktop, library portable to embedded

## License

[Specify your license here]

## Contributing

[Contributing guidelines if applicable]

## Author

[Your name/contact information]

