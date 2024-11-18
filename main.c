#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "BIG_STRINGS.h"

#define assert_equal(x, y) (x) == (y) ? "\e[32mTrue\e[0m" : "\e[31mFalse\e[0m"
#define assert_equal_str(x, y) (strcmp(x, y) == 0) ? "\e[32mTrue\e[0m" : "\e[31mFalse\e[0m"
#define assert_equal_str3(x, y, z) (strcmp(x, y) == 0) && (strcmp(y, z) == 0) ? "\e[32mTrue\e[0m" : "\e[31mFalse\e[0m"

extern size_t ft_strlen(const char *);
extern char *ft_strcpy(char *, char *);

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


int main()
{
	test_strlen();
	printf("\n");
	test_strcpy();
}
