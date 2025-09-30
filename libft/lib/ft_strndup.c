#include "libft.h"

char *ft_strndup(char *s1, int size)
{
    char *s2;
    int i;

    i = 0;

    if(size <= 0)
        return(NULL);
    while(s1[i])
        i++;
    s2 = malloc((i + 1) * sizeof(char));
    if(!s2)
        return(NULL);
    i = 0;
    while(s1[i] && i < size)
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
    return(s2);
}
