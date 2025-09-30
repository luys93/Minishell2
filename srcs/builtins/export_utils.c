#include "minishell.h"

/* riporta la lunghezza della chiave, fino al '=' */
int     find_keylen(char *str)
{
    int     len;

    len = 0;
    while (str[len] && str[len] != '=')
        len++;
    return (len);
}

/* cerca se la chiave esiste gia nelle env (riporta i) o e nuova (riporta -1) */
int     find_keypos(t_data *data, char *str, int keylen)
{
    int     i;

    i = 0;
    while (data->env && data->env[i])
    {
        if (ft_strncmp(data->env[i], str, keylen) == 0 && 
        (data->env[i][keylen] == '=' || data->env[i][keylen] == '\0'))
            return(i);
        i++;
    }
    return (-1);
}

/* conta le variabili d'ambiente */
int count_env(char **env)
{
    int     count;

    count = 0;
    while (env && env[count])
        count++;
    return (count);
}

/* riempie new_env con le vecchie env */
void    copy_env(char **new_env, char **old_env, int count)
{
    int     i;

    i = 0;

    while (i < count)
    {
    	new_env[i] = ft_strdup(old_env[i]);
        i++;
    }
}
