/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:57:06 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/21 08:59:37 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

typedef int	(*t_test_fn)(void);

typedef struct s_test_case
{
	const char	*name;
	t_test_fn	std_fn;
	t_test_fn	ft_fn;
}t_test_case;

static int		g_num = 42;
static int		g_neg = -42;
static int		g_zero = 0;
static char		*g_str = "Hello";
static char		*g_empty = "";
static char		*g_null = NULL;
static void		*g_ptr = &g_num;

static void	print_escaped(const unsigned char *buf, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (buf[i] == '\n')
			printf("\\n");
		else if (buf[i] == '\t')
			printf("\\t");
		else if (buf[i] == '\0')
			printf("\\0");
		else if (buf[i] < 32 || buf[i] > 126)
			printf("\\x%02X", buf[i]);
		else
			printf("%c", buf[i]);
		i++;
	}
}

static int	capture_output(t_test_fn fn, unsigned char *buf, size_t *len, int *ret)
{
	int		fd[2];
	int		saved_stdout;
	ssize_t	bytes;
	size_t	total;

	if (pipe(fd) == -1)
		return (-1);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		return (close(fd[0]), close(fd[1]), -1);
	fflush(stdout);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (close(fd[0]), close(fd[1]), close(saved_stdout), -1);
	close(fd[1]);
	*ret = fn();
	fflush(stdout);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (close(fd[0]), close(saved_stdout), -1);
	close(saved_stdout);
	total = 0;
	bytes = read(fd[0], buf + total, BUFFER_SIZE - total);
	while (bytes > 0)
	{
		total += (size_t)bytes;
		if (total == BUFFER_SIZE)
			break ;
		bytes = read(fd[0], buf + total, BUFFER_SIZE - total);
	}
	close(fd[0]);
	if (bytes < 0)
		return (-1);
	*len = total;
	return (0);
}

#define DEFINE_TEST(ID, FORMAT, ...) \
static int std_##ID(void) { return (printf(FORMAT, ##__VA_ARGS__)); } \
static int ft_##ID(void) { return (ft_printf(FORMAT, ##__VA_ARGS__)); }

DEFINE_TEST(t01_literal, "Hello world")
DEFINE_TEST(t02_newline, "Hello\nWorld\n")
DEFINE_TEST(t03_percent, "100%%")
DEFINE_TEST(t04_char_a, "%c", 'A')
DEFINE_TEST(t05_char_null, "A%cB", '\0')
DEFINE_TEST(t06_string, "%s", g_str)
DEFINE_TEST(t07_empty_string, "%s", g_empty)
DEFINE_TEST(t08_null_string, "%s", g_null)
DEFINE_TEST(t09_decimal_zero, "%d", g_zero)
DEFINE_TEST(t10_decimal_pos, "%d", g_num)
DEFINE_TEST(t11_decimal_neg, "%d", g_neg)
DEFINE_TEST(t12_decimal_intmax, "%d", INT_MAX)
DEFINE_TEST(t13_decimal_intmin, "%d", INT_MIN)
DEFINE_TEST(t14_int_i, "%i", -123456)
DEFINE_TEST(t15_unsigned_zero, "%u", 0U)
DEFINE_TEST(t16_unsigned_max, "%u", UINT_MAX)
DEFINE_TEST(t17_unsigned_random, "%u", 4294967U)
DEFINE_TEST(t18_hex_zero, "%x", 0U)
DEFINE_TEST(t19_hex_small, "%x", 48879U)
DEFINE_TEST(t20_hex_max, "%x", UINT_MAX)
DEFINE_TEST(t21_HEX_small, "%X", 48879U)
DEFINE_TEST(t22_HEX_max, "%X", UINT_MAX)
DEFINE_TEST(t23_ptr_null, "%p", NULL)
DEFINE_TEST(t24_ptr_var, "%p", g_ptr)
DEFINE_TEST(t25_mix_basic, "c:%c s:%s d:%d i:%i u:%u x:%x X:%X p:%p %%", \
'Z', "ok", -12, 34, 56U, 0x1a2bU, 0x1a2bU, g_ptr)
DEFINE_TEST(t26_mix_many, "[%d][%d][%u][%x][%X][%s]", -1, 0, UINT_MAX, 0U, UINT_MAX,
"mix")
DEFINE_TEST(t27_long_string, "%s", "Lorem ipsum dolor sit amet, consectetur adipiscing elit.")
DEFINE_TEST(t28_multi_line, "Line1\nLine2\n%d\n%s", 123, "done")
DEFINE_TEST(t29_zero_combo, "%d %i %u %x %X", 0, 0, 0U, 0U, 0U)
DEFINE_TEST(t30_percent_chain, "%%%%%%")

static int	run_one_test(const t_test_case *test)
{
	unsigned char	std_buf[BUFFER_SIZE];
	unsigned char	ft_buf[BUFFER_SIZE];
	size_t			std_len;
	size_t			ft_len;
	int				std_ret;
	int				ft_ret;
	int				ok;

	if (capture_output(test->std_fn, std_buf, &std_len, &std_ret) == -1)
		return (printf("[ERROR] %s: capture std failed\n", test->name), 0);
	if (capture_output(test->ft_fn, ft_buf, &ft_len, &ft_ret) == -1)
		return (printf("[ERROR] %s: capture ft failed\n", test->name), 0);
	ok = (std_ret == ft_ret) && (std_len == ft_len)
		&& (memcmp(std_buf, ft_buf, std_len) == 0);
	if (ok)
		printf("[OK]   %s\n", test->name);
	else
	{
		printf("[FAIL] %s\n", test->name);
		printf("  return: printf=%d | ft_printf=%d\n", std_ret, ft_ret);
		printf("  size  : printf=%zu | ft_printf=%zu\n", std_len, ft_len);
		printf("  printf   : ");
		print_escaped(std_buf, std_len);
		printf("\n");
		printf("  ft_printf: ");
		print_escaped(ft_buf, ft_len);
		printf("\n");
	}
	return (ok);
}

int	main(void)
{
	const t_test_case	tests[] = {
		{"literal", std_t01_literal, ft_t01_literal},
		{"newline", std_t02_newline, ft_t02_newline},
		{"percent", std_t03_percent, ft_t03_percent},
		{"char A", std_t04_char_a, ft_t04_char_a},
		{"char null", std_t05_char_null, ft_t05_char_null},
		{"string", std_t06_string, ft_t06_string},
		{"empty string", std_t07_empty_string, ft_t07_empty_string},
		{"null string", std_t08_null_string, ft_t08_null_string},
		{"decimal zero", std_t09_decimal_zero, ft_t09_decimal_zero},
		{"decimal positive", std_t10_decimal_pos, ft_t10_decimal_pos},
		{"decimal negative", std_t11_decimal_neg, ft_t11_decimal_neg},
		{"decimal int max", std_t12_decimal_intmax, ft_t12_decimal_intmax},
		{"decimal int min", std_t13_decimal_intmin, ft_t13_decimal_intmin},
		{"integer i", std_t14_int_i, ft_t14_int_i},
		{"unsigned zero", std_t15_unsigned_zero, ft_t15_unsigned_zero},
		{"unsigned max", std_t16_unsigned_max, ft_t16_unsigned_max},
		{"unsigned random", std_t17_unsigned_random, ft_t17_unsigned_random},
		{"hex lower zero", std_t18_hex_zero, ft_t18_hex_zero},
		{"hex lower small", std_t19_hex_small, ft_t19_hex_small},
		{"hex lower max", std_t20_hex_max, ft_t20_hex_max},
		{"hex upper small", std_t21_HEX_small, ft_t21_HEX_small},
		{"hex upper max", std_t22_HEX_max, ft_t22_HEX_max},
		{"pointer null", std_t23_ptr_null, ft_t23_ptr_null},
		{"pointer variable", std_t24_ptr_var, ft_t24_ptr_var},
		{"mixed basic", std_t25_mix_basic, ft_t25_mix_basic},
		{"mixed many", std_t26_mix_many, ft_t26_mix_many},
		{"long string", std_t27_long_string, ft_t27_long_string},
		{"multi line", std_t28_multi_line, ft_t28_multi_line},
		{"all zeros", std_t29_zero_combo, ft_t29_zero_combo},
		{"percent chain", std_t30_percent_chain, ft_t30_percent_chain}
	};
	int					pass;
	int					fail;
	size_t				i;

	pass = 0;
	fail = 0;
	i = 0;
	printf("=== ft_printf vs printf test suite ===\n");
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		if (run_one_test(&tests[i]))
			pass++;
		else
			fail++;
		i++;
	}
	printf("=====================================\n");
	printf("Total: %zu | Pass: %d | Fail: %d\n", sizeof(tests) / sizeof(tests[0]),
		pass, fail);
	if (fail == 0)
		printf("Result: ALL TESTS PASSED ✅\n");
	else
		printf("Result: SOME TESTS FAILED ❌\n");
	return (fail != 0);
}
