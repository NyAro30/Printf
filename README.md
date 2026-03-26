*This project has been created as part of the 42 curriculum by mny-aro-.*

# ft_printf

## Description
`ft_printf` is a reimplementation of the standard C `printf` function from libc.

### Goal
The goal is to reproduce the behavior of `printf` with:

### Mandatory conversions
- `%c`
- `%s`
- `%p`
- `%d`
- `%i`
- `%u`
- `%x`
- `%X`
- `%%`

### Bonus features
- Flags: `-`, `0`, `.`, `#`, `+`, ` ` (space)
- Field minimum width
- Combination handling of bonus flags under supported conversions

This project focuses on:
- variadic argument handling (`stdarg.h`),
- numeric type conversion,
- accurate counting of written characters,
- writing robust and modular C functions.

## Features
- Supports all mandatory conversions.
- Supports bonus flags and width handling.
- Returns the exact number of printed characters.
- Handles common edge cases:
  - `NULL` string for `%s` → `(null)`,
  - `NULL` pointer for `%p` → `(nil)`,
  - `INT_MIN` for `%d` / `%i`.

## Instructions

### Build the library
From the project root:
- `make`: compiles and creates `libftprintf.a`
- `make bonus`: compiles the bonus implementation into `libftprintf.a`
- `make clean`: removes object files
- `make fclean`: removes object files and the library
- `make re`: full rebuild

### Use in another project
1. Build the library: `make`
2. Include the header: `#include "ft_printf.h"`
3. Link the library when compiling, for example:
   - `cc main.c libftprintf.a -o my_program`

### Quick local test
A test `main.c` is available at the root to compare `ft_printf` and `printf` on multiple cases.
Example:
- `cc -Wall -Wextra -Werror main.c libftprintf.a -o printf_tests`
- `./printf_tests`

### Recommended checks before evaluation
- `norminette ft_*.c ft_*.h`
- `make bonus`
- (optional) run your local tester / valgrind checks

## Detailed Algorithm and Data Structure Explanation

### Algorithm overview
The `ft_printf` implementation uses a **linear parser** over the format string.

1. Initialize a variadic list with `va_start`.
2. Iterate through the format string character by character.
3. If the current character is not `%`, print it directly and increment the global count.
4. If the current character is `%`, parse flags/width/precision (bonus path), then dispatch to the matching conversion handler.
5. Add the number of characters returned by each helper function.
6. Finalize with `va_end` and return the global count.

Time complexity:
- Format parsing is `O(n)` where `n` is the format length,
- plus numeric conversion cost (proportional to the number of digits, i.e. logarithmic in the conversion base).

Space complexity:
- `O(1)` extra memory, excluding recursion call stack for number printing.

### Design choices and justification
- **Specialized helper functions** (`ft_putnbr`, `ft_putnbr_hex`, `ft_putptr`, etc.):
  - better readability,
  - easier targeted testing,
  - safer maintenance.
- **Recursion for numeric conversions**:
  - naturally prints digits in correct order,
  - avoids temporary buffers.
- **Per-function character count return value**:
  - ensures precise, centralized total return value computation.

### Data structures used
This project intentionally avoids complex runtime data structures (no linked lists, dynamic arrays, etc.).
Core elements are:
- C primitive types (`int`, `unsigned int`, `unsigned long`, `uintptr_t`),
- the standard variadic type `va_list`,
- the format string (`const char *`) scanned sequentially.
- for bonus parsing: a compact `t_fmt` struct that stores parsed formatting options.

This minimal approach is appropriate for the subject requirements: parse, convert, print.

## Project structure (main files)
- `ft_printf.c`: mandatory parser and conversion dispatch.
- `ft_printf.h`: prototypes and required headers.
- `ft_putchar.c`: character output.
- `ft_putstr.c`: string output.
- `ft_putnbr.c`: signed base-10 output.
- `ft_putnbr_unsigned.c`: unsigned base-10 output.
- `ft_putnbr_hex.c`: hexadecimal output.
- `ft_putptr.c`: pointer output.
- `ft_printf_bonus.c`, `ft_printf_bonus.h`: bonus entry point + format context.
- `ft_parse_bonus.c`: bonus format parser.
- `ft_print_bonus_part*.c`: bonus conversion handlers.
- `ft_utils_bonus*.c`: bonus helper functions.
- `Makefile`: build rules.
- `explication.txt`: short oral preparation notes for evaluation.

## Resources

### Classic references
- `man 3 printf`
- `man 3 stdarg`
- GNU C Library documentation (glibc): `printf` family
- The Open Group Base Specifications (format string functions)

### AI usage
AI was used as a **support tool** for:
- review/checklist guidance,
- refactoring suggestions,
- README structuring,
- and preparation notes for oral evaluation.

The project was validated with compilation checks, Norminette, and runtime tests.

## Notes
- Mandatory and bonus parts are both implemented in this repository.
