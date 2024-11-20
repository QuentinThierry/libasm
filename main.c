#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
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
		int fd_no_perm = open("file_no_perm", O_CREAT | O_RDWR, 0777);

		errno = 0;
		int res_expect = write(fd_no_perm, NULL, 6);
		int errno_expect = errno;
		errno = 0;
		int res_mine = ft_write(fd_no_perm, NULL, 6);
		int errno_mine = errno;
		printf("expected : %d, got : %d | %s\n", res_expect, res_mine, assert_equal(res_expect, res_mine));
		printf("expected errno : `%s`, my errno : `%s` | %s\n", strerror(errno_expect), strerror(errno_mine), assert_equal_str(strerror(errno_expect), strerror(errno_mine)));
		close(fd_no_perm);
		unlink("file_no_perm");
	}
}


int main()
{
	test_strlen();
	printf("\n");
	test_strcpy();
	printf("\n");
	test_strcmp();
	printf("\n");
	test_write();
}
