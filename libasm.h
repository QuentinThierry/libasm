#ifndef LIBASM_H
#define LIBASM_H

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

typedef struct s_list
{
	void *data;
	struct s_list *next;
} t_list;

// MANDATORY PART
extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *dest, const char *src);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *s);

// BONUS PART
extern int ft_atoi_base(char *str, char *base);
extern void ft_list_push_front(t_list **begin_list, void *content);
extern int ft_list_size(t_list *begin_list);
extern int ft_list_sort(t_list **begin_list, int (*cmp)());
extern int ft_list_remove_if(t_list **begin_list, void *dataref, int (*cmp)(), void (*free_fct)(void *));

// UTILS_C
t_list *ft_lst_new(void *content);
void free_list(t_list *begin_list);
void print_list_str(t_list *list);
void print_list_int(t_list *list);
int is_less_than(int a, int b);
int is_less_than_ptr(int *data, int *ref);
void do_nothing(void *ptr);

#endif