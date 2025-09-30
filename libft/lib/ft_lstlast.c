#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current_node;

	current_node = lst;
	if (!current_node)
		return (NULL);
	while (current_node->next != NULL)
		current_node = current_node->next;
	return (current_node);
}
