#include "minishell.h"

/* funzione principale */
void    ft_unset(t_data *data, t_command *cmd)
{
    int    i;

    if (!cmd->argv[1])
        return ;
    i = 1;
    while (cmd->argv[i])
    {
        if (valid_identifier(cmd->argv[i]) == 1)
        {
            ft_update_unset(data, cmd->argv[i]);
        }
        else
            printf("unset: `%s': not a valid identifier\n", cmd->argv[i]);
        i++;
    }
}

/* controlla se l'argomento e' valido */
int valid_identifier(char *str)
{
    int i;

    i = 1;
    if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
        return (0);
    while (str[i])
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

/* cerca se la chiave esiste nelle env (riporta i) o no (-1) */
void    ft_update_unset(t_data *data, char *str)
{
    char    **new_env;
    int     keylen;
    int     keypos;
    int     count;
    int     i;
    int     j;

    keylen = find_keylen(str);
    keypos = find_keypos(data, str, keylen);
    if (keypos < 0)
        return; // variabile non trovata, non fare nulla
    count = count_env(data->env);
    if (count <= 1)
    {
        free_env(data->env); // Se c'è solo una variabile o meno, crea array vuoto
        data->env = malloc(sizeof(char *) * 1);
        if (data->env)
            data->env[0] = NULL;
        return;
    }
    new_env = malloc(sizeof(char *) * count); // count - 1 + NULL
    if (!new_env)
        return;
    i = 0;
    j = 0;
    while (data->env[i])
    {
        if (i != keypos) // copia tutto tranne la variabile da rimuovere
        {
            new_env[j] = ft_strdup(data->env[i]);
            j++;
        }
        i++;
    }
    new_env[j] = NULL;
    free_env(data->env);
    data->env = new_env;
}

/* Trova la posizione della chiave per unset (cerca nome esatto) */
int     find_unset_keypos(t_data *data, char *key, int keylen)
{
    int     i;

    i = 0;
    while (data->env && data->env[i])
    {
        if (ft_strncmp(data->env[i], key, keylen) == 0 && 
           (data->env[i][keylen] == '=' || data->env[i][keylen] == '\0'))
            return(i);
        i++;
    }
    return (-1);
}
