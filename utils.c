#include "libasm.h"

t_list *ft_lst_new(void *content)
{
	t_list *new = malloc(sizeof(t_list));
	if (!new)
		return NULL;
	new->data = content;
	new->next = NULL;
	return new;
}

void free_list(t_list *begin_list)
{
	while (begin_list)
	{
		t_list *tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp);
	}
}

int is_less_than(int a, int b)
{
	return a - b;
}

void print_list_str(t_list *list)
{
	while (list)
	{
		printf("%s->", (char *)list->data);
		list = list->next;
	}
	printf("\n");
}

void print_list_int(t_list *list)
{
	while (list)
	{
		printf("%d->", *(int *)list->data);
		list = list->next;
	}
	printf("\n");
}

int is_less_than_ptr(int *data, int *ref)
{
	if (*data == *ref)
		return 0;
	return 1;
}

void do_nothing(void *ptr)
{
	(void)ptr;
}