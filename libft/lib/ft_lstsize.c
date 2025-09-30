#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*current_node;

	count = 0;
	current_node = lst;
	while (current_node != NULL)
	{
		count++;
		current_node = current_node->next;
	}
	return (count);
}
