#include "libasm.h"

t_list	*ft_lst_new(void *content)
{
	t_list *new = malloc(sizeof(t_list));
	if (!new)
		return NULL;
	new->data = content;
	new->next = NULL;
	return new;
}

