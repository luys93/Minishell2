#include "minishell.h"

//controllare che sia valido l'argomento da inserire
void    ft_export(t_data *data, t_command *cmd)
{
    int     i;

    if (!cmd->argv[1])
    {
        print_sort_env(data->env);
        return;
    }
    i = 1;
    while (cmd->argv[i])
    {
        if (valid_value(data, cmd->argv[i]) == 0)
        {
			data->exit_status = 0;
            ft_update_export(data, cmd->argv[i]);
        }
        else
			rl_on_new_line();
        i++;
    }
}

void    sort_env(char **env)
{
    int     i;
    int     j;
    char    *temp;

    i = 0;
    while (env[i])
    {
        j = i + 1;
        while (env[j])
        {
            if (ft_strcmp(env[i], env[j]) > 0)
            {
                temp = env[i];
                env[i] = env[j];
                env[j] = temp;
            }
            j++;
        }
        i++;
    }
	
}

void    print_sort_env(char **env)
{
    int     i;
    int     count;
    char    **sorted_env;

    i = 0;
    count = count_env(env);
    sorted_env = malloc(sizeof(char *) * (count + 1));
    if (!sorted_env)
        return;
    copy_env(sorted_env, env, count);
    sorted_env[count] = NULL;
    sort_env(sorted_env);
    while (sorted_env[i])
        printf("declare -x %s\n", sorted_env[i++]);
    free_env(sorted_env);
}

int     valid_value(t_data *data, char *str)
{
    int     i;

    i = 1;
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		error_process(data, str, ": not a valid identifier", 1);
        return(1);
	}
    while (str[i] && str[i] != '=')
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			error_process(data, str, ": not a valid identifier", 1);
            return(1);
		}
        i++;
    }
   	if (str[i] == '=' && str[i + 1])
        return(0);
    return(0);
}

void    ft_update_export(t_data *data, char *str)
{
    char    **new_env;
    int     keylen;
    int     keypos;
    int     count;

    keylen = find_keylen(str);
    keypos = find_keypos(data, str, keylen);
    if (keypos >= 0)
    {
        free(data->env[keypos]);
        data->env[keypos] = ft_strdup(str);
        return;
    }
    count = count_env(data->env);
    new_env = ft_calloc(sizeof(char *), (count + 2));
    if (!new_env)
        return;
    copy_env(new_env, data->env, count);
	new_env[count++] = ft_strdup(str);
	new_env[count] = NULL;
    free_env(data->env);
    data->env = new_env;
}
