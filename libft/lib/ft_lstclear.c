#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp_node;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp_node = *lst;
		*lst = tmp_node->next;
		ft_lstdelone(tmp_node, del);
	}
}