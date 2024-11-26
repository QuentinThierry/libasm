#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "BIG_STRINGS.h"

#define assert_equal(x, y) (x) == (y) ? "\e[32mTrue\e[0m" : "\e[31mFalse\e[0m"
#define assert_equal_str(x, y) (strcmp(x, y) == 0) ? "\e[32mTrue\e[0m" : "\e[31mFalse\e[0m"
#define assert_equal_str3(x, y, z) (strcmp(x, y) == 0) && (strcmp(y, z) == 0) ? "\e[32mTrue\e[0m" : "\e[31mFalse\e[0m"

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *dest, const char *src);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *s);

extern int ft_atoi_base(char *str, char *base);

void test_strlen()
{
	const char *ptr_strlen = "hello";
	long expected = 0;
	long my_ret = 0;

	expected = strlen(ptr_strlen);
	my_ret = ft_strlen(ptr_strlen);
	printf("expected : %lu, got : %lu | %s\n", expected, my_ret, assert_equal(expected, my_ret));

	ptr_strlen = "world!";
	expected = strlen(ptr_strlen);
	my_ret = ft_strlen(ptr_strlen);
	printf("expected : %lu, got : %lu | %s\n", expected, my_ret, assert_equal(expected, my_ret));

	ptr_strlen = "a";
	expected = strlen(ptr_strlen);
	my_ret = ft_strlen(ptr_strlen);
	printf("expected : %lu, got : %lu | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	ptr_strlen = "";

	expected = strlen(ptr_strlen);
	my_ret = ft_strlen(ptr_strlen);
	printf("expected : %lu, got : %lu | %s\n", expected, my_ret, assert_equal(expected, my_ret));

	ptr_strlen = "\0\0\0";
	expected = strlen(ptr_strlen);
	my_ret = ft_strlen(ptr_strlen);
	printf("expected : %lu, got : %lu | %s\n", expected, my_ret, assert_equal(expected, my_ret));

	ptr_strlen = STR_100000_CHAR;
	expected = strlen(ptr_strlen);
	my_ret = ft_strlen(ptr_strlen);
	printf("expected : %lu, got : %lu | %s\n", expected, my_ret, assert_equal(expected, my_ret));
}

void test_strcpy()
{
	{
		char src_ori[10] = "diff_size";
		char dest_ori[16] = "replaced string";
		char src_mine[10] = "diff_size";
		char dest_mine[16] = "replaced string";

		strcpy(dest_ori, src_ori);
		printf("expected : `%s`", dest_ori);
		char *ret_mine = ft_strcpy(dest_mine, src_mine);
		printf(", got : `%s` (`%s`) | %s\n", dest_mine, ret_mine, assert_equal_str3(dest_ori, dest_mine, ret_mine));
	}
	{
		char src_ori[10] = "same_size";
		char dest_ori[10] = "123456789";
		char src_mine[10] = "same_size";
		char dest_mine[10] = "123456789";

		strcpy(dest_ori, src_ori);
		printf("expected : `%s`", dest_ori);
		char *ret_mine = ft_strcpy(dest_mine, src_mine);
		printf(", got : `%s` (`%s`) | %s\n", dest_mine, ret_mine, assert_equal_str3(dest_ori, dest_mine, ret_mine));
	}
	{
		char src_ori[1] = "";
		char dest_ori[1] = "";
		char src_mine[1] = "";
		char dest_mine[1] = "";

		strcpy(dest_ori, src_ori);
		printf("expected : `%s`", dest_ori);
		char *ret_mine = ft_strcpy(dest_mine, src_mine);
		printf(", got : `%s` (`%s`) | %s\n", dest_mine, ret_mine, assert_equal_str3(dest_ori, dest_mine, ret_mine));
	}
}

void test_strcmp()
{
	{
		char *str_ori; str_ori = "coucoa";
		char *str_mine; str_mine = "coucob";
		int res_ori = strcmp(str_ori, str_mine);
		int res_mine = ft_strcmp(str_ori, str_mine);

		printf("expected : %d, got : %d | %s\n", res_ori, res_mine, assert_equal(res_ori, res_mine));
	}
	{
		char *str_ori; str_ori = "coucob";
		char *str_mine; str_mine = "coucoa";
		int res_ori = strcmp(str_ori, str_mine);
		int res_mine = ft_strcmp(str_ori, str_mine);

		printf("expected : %d, got : %d | %s\n", res_ori, res_mine, assert_equal(res_ori, res_mine));
	}
	{
		char *str_ori; str_ori = "a";
		char *str_mine; str_mine = "a";
		int res_ori = strcmp(str_ori, str_mine);
		int res_mine = ft_strcmp(str_ori, str_mine);

		printf("expected : %d, got : %d | %s\n", res_ori, res_mine, assert_equal(res_ori, res_mine));
	}
	{
		char *str_ori; str_ori = "";
		char *str_mine; str_mine = "";
		int res_ori = strcmp(str_ori, str_mine);
		int res_mine = ft_strcmp(str_ori, str_mine);

		printf("expected : %d, got : %d | %s\n", res_ori, res_mine, assert_equal(res_ori, res_mine));
	}
	{
		char *str_ori; str_ori = "string";
		char *str_mine; str_mine = "strin2";
		int res_ori = strcmp(str_ori, str_mine);
		int res_mine = ft_strcmp(str_ori, str_mine);

		printf("expected : %d, got : %d | %s\n", res_ori, res_mine, assert_equal(res_ori, res_mine));
	}
	{
		char *str_ori; str_ori = "strin2";
		char *str_mine; str_mine = "string";
		int res_ori = strcmp(str_ori, str_mine);
		int res_mine = ft_strcmp(str_ori, str_mine);

		printf("expected : %d, got : %d | %s\n", res_ori, res_mine, assert_equal(res_ori, res_mine));
	}
}

void test_write()
{
	{
		// ON STDOUT / SUCCESS
		errno = 0;
		int res_expect = write(1, "hello\n", 6);
		int errno_expect = errno;
		errno = 0;
		int res_mine = ft_write(1, "hello\n", 6);
		int errno_mine = errno;
		printf("expected : %d, got : %d | %s\n", res_expect, res_mine, assert_equal(res_expect, res_mine));
		printf("expected errno : `%s`, my errno : `%s` | %s\n", strerror(errno_expect), strerror(errno_mine), assert_equal_str(strerror(errno_expect), strerror(errno_mine)));
	}
	{
		// BAD FILE DESCRIPTOR / EBADF
		errno = 0;
		int res_expect = write(13, "hello\n", 6);
		int errno_expect = errno;
		errno = 0;
		int res_mine = ft_write(13, "hello\n", 6);
		int errno_mine = errno;
		printf("expected : %d, got : %d | %s\n", res_expect, res_mine, assert_equal(res_expect, res_mine));
		printf("expected errno : `%s`, my errno : `%s` | %s\n", strerror(errno_expect), strerror(errno_mine), assert_equal_str(strerror(errno_expect), strerror(errno_mine)));
	}
	{
		// BAD BUFFER / EFAULT
		int fd_file = open("file_name", O_CREAT | O_RDWR, 0777);

		errno = 0;
		int res_expect = write(fd_file, NULL, 6);
		int errno_expect = errno;
		errno = 0;
		int res_mine = ft_write(fd_file, NULL, 6);
		int errno_mine = errno;
		printf("expected : %d, got : %d | %s\n", res_expect, res_mine, assert_equal(res_expect, res_mine));
		printf("expected errno : `%s`, my errno : `%s` | %s\n", strerror(errno_expect), strerror(errno_mine), assert_equal_str(strerror(errno_expect), strerror(errno_mine)));
		close(fd_file);
		unlink("file_name");
	}
}

void test_read()
{
	{
		// ON 'file_name' / SUCCESS
		int file_fd = open("file_name", O_RDWR | O_CREAT | O_TRUNC, 0777);
		write(file_fd, "this is a text", sizeof("this is a text"));
		lseek(file_fd, 0, SEEK_SET);

		errno = 0;
		char buf_except[100] = {0};
		int res_expect = read(file_fd, buf_except, sizeof("this is a text"));
		int errno_mine = errno;
		lseek(file_fd, 0, SEEK_SET);

		errno = 0;
		char buf_mine[100] = {0};
		int res_mine = ft_read(file_fd, buf_mine, sizeof("this is a text"));
		int errno_expect = errno;

		printf("expected : `%s` (%d), got : `%s` (%d) | %s\n", buf_except, res_expect, buf_mine, res_expect, assert_equal_str(assert_equal(res_expect, res_mine), assert_equal_str(buf_except, buf_mine)));
		printf("expected errno : `%s`, my errno : `%s` | %s\n", strerror(errno_expect), strerror(errno_mine), assert_equal_str(strerror(errno_expect), strerror(errno_mine)));
		close(file_fd);
		unlink("file_name");
	}
	{
		// BAD FILE DESCRIPTOR / EBADF
		errno = 0;
		read(-1, NULL, 10);
		int errno_mine = errno;

		errno = 0;
		ft_read(-1, NULL, 10);
		int errno_expect = errno;
		printf("-Should not read-\n");
		printf("expected errno : `%s`, my errno : `%s` | %s\n", strerror(errno_expect), strerror(errno_mine), assert_equal_str(strerror(errno_expect), strerror(errno_mine)));
	}
}

void test_strdup()
{
	// no malloc protections, it's a test
	{
		char *test_string = "this_is_a_string";

		errno = 0;
		char *res_expect = strdup(test_string);
		int errno_expect = errno;

		errno = 0;
		char *res_mine = ft_strdup(test_string);
		int errno_mine = errno;

		printf("expected : `%s`, got : `%s` | %s\n", res_expect, res_mine, assert_equal_str(res_expect, res_mine));
		printf("expected errno : `%s`, my errno : `%s` | %s\n", strerror(errno_expect), strerror(errno_mine), assert_equal_str(strerror(errno_expect), strerror(errno_mine)));
		free(res_expect);
		free(res_mine);
	}
	{
		char *test_string = "";

		errno = 0;
		char *res_expect = strdup(test_string);
		int errno_expect = errno;

		errno = 0;
		char *res_mine = ft_strdup(test_string);
		int errno_mine = errno;

		printf("expected : `%s`, got : `%s` | %s\n", res_expect, res_mine, assert_equal_str(res_expect, res_mine));
		printf("expected errno : `%s`, my errno : `%s` | %s\n", strerror(errno_expect), strerror(errno_mine), assert_equal_str(strerror(errno_expect), strerror(errno_mine)));
		free(res_expect);
		free(res_mine);
	}
}

// bonus
void test_atoi_base()
{
	// C code translation
	{
		// FUNCTION check_base (size <= 1, 2x meme char, +,- ou whitespace)
		// if (!str || !base)
		// 	return 0;
		// int size_base = ft_strlen(base);
		// if (size_base <= 1)
		// 	return 0;
		// for (int i = 0; i < size_base; i++)
		// {
		// 	if ((base[i] >= 8 && base[i] <= 13) || base[i] == 32)
		// 		return 0;
		// 	for (int j = i + 1; j < size_base; j++)
		// 	{
		// 		if (base[i] == base[j])
		// 			return 0;
		// 	}
		// }

		// // skip white spaces
		// int i;
		// for (i = 0; str[i]; i++)
		// {
		// 	if (str[i] < 8 || (str[i] > 13 && str[i] != 32))
		// 		break;
		// }

		// // function get_sign
		// int sign = 1;
		// for (; str[i]; i++)
		// {
		// 	if (str[i] == '+')
		// 		continue;
		// 	else if (str[i] == '-')
		// 		sign *= -1; // neg
		// 	else
		// 		break;
		// }

		// // ft_atoi_base
		// int pos_char;
		// int return_value = 0;
		// while (str[i])
		// {
		// 	pos_char = is_in_base(str[i], base);
		// 	if (pos_char == -1)
		// 		break;
		// 	return_value *= size_base;
		// 	return_value += pos_char;
		// 	i++;
		// }
		// return return_value * sign;
	}

	{	// base 10 -> OK 100
		char *base = "0123456789";
		char *number = "100";
		int expected = 100;
		int my_ret = ft_atoi_base(number, base);
		printf("expected : %d, got : %d | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	}
	{	// base too small -> KO 0
		char *base = "7";
		char *number = "109283";
		int expected = 0;
		int my_ret = ft_atoi_base(number, base);
		printf("expected : %d, got : %d | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	}
	{	// base with illegal char -> KO 0
		char *base = "0123456789-";
		char *number = "109283";
		int expected = 0;
		int my_ret = ft_atoi_base(number, base);
		printf("expected : %d, got : %d | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	}
	{	// base 10 with empty nbr -> OK 0
		char *base = "0123456789";
		char *number = "";
		int expected = 0;
		int my_ret = ft_atoi_base(number, base);
		printf("expected : %d, got : %d | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	}
	{	// base 10 with neg nbr -> OK 1=-100
		char *base = "0123456789";
		char *number = "-100";
		int expected = -100;
		int my_ret = ft_atoi_base(number, base);
		printf("expected : %d, got : %d | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	}
	{	// base 10 with multiple signs -> OK -100
		char *base = "0123456789";
		char *number = "-+--+100";
		int expected = -100;
		int my_ret = ft_atoi_base(number, base);
		printf("expected : %d, got : %d | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	}
	{	// base 16 -> OK -262649830
		char *base = "0123456789ABCDEF";
		char *number = "---FA7B7E6";
		int expected = -262649830;
		int my_ret = ft_atoi_base(number, base);
		printf("expected : %d, got : %d | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	}
	{	// base 32 -> OK -262649830
		char *base = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
		char *number = "SALUT";
		int expected = 29710301;
		int my_ret = ft_atoi_base(number, base);
		printf("expected : %d, got : %d | %s\n", expected, my_ret, assert_equal(expected, my_ret));
	}
}


int main()
{
	printf("\e[36m---== ft_strlen ==---\e[0m\n");
	test_strlen();
	printf("\e[36m---== ft_strcpy ==---\e[0m\n");
	test_strcpy();
	printf("\e[36m---== ft_strcmp ==---\e[0m\n");
	test_strcmp();
	printf("\e[36m---== ft_write ==---\e[0m\n");
	test_write();
	printf("\e[36m---== ft_read ==---\e[0m\n");
	test_read();
	printf("\e[36m---== ft_strdup ==---\e[0m\n");
	test_strdup();
	printf("\e[36m---== ft_atoi_base ==---\e[0m\n");
	test_atoi_base();
}
