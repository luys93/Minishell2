#include "minishell.h"

/* se ci sono altri argomenti dopo exit, stampare " exit: cmd: numeri argument required"
mentre se c'e una pipe non si chiude il programma ed esegue e basta */

void    ft_exit(t_data *data) 
{
    int     exit_value;
    int     arg;

    arg = ft_count_argument(data->command);
	if (arg > 2)
    {
        error_process(data, data->command->argv[0], "exit : too many arguments\n", 1);
        free_temp(data, 'x');
        return ;
    }
    if (arg >= 2 && ft_strcmp(data->command->argv[0], "exit") == 0)
    {
        if (check_exit(data->command->argv[1]) == 0)
        {
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_putstr_fd("bash: exit: %s: numeric argument required\n", STDERR_FILENO);
            free_temp(data, 'v');
            exit(2);
        }
        exit_value = ft_atoi(data->command->argv[1]);
    }
    else
	{
        exit_value = 0;
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
    free_temp(data, 'v');
    exit(exit_value);
}



/* controlla la cifra dopo exit */
int     check_exit(char *str)
{
    int             i;
    int             sign;
    long long int   num;

    i = 0;
    num = 0;
    sign = 1;
    if (str == NULL)
        return(0);
    if (ft_strcmp(str, "--") == 0)
        return(1);
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -sign;
        i++;
    }
    if (str[i] == '\0' || str[i] < '0' || str[i] > '9')
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return(0);
        if (check_overflow(sign, num, str, i) == 1)
            return(0);
        num = (num * 10) + (str[i++] - '0');
    }
    return(1);
}

/* controlla se c'e overflow nella cifra aggiunta */
int	check_overflow(int sign, long long int num, char *str, int i)
{
	if (sign == 1 && num > (LLONG_MAX - (str[i] - '0')) / 10)
		return (1);  // Ha overflow
	else if (sign == -1)
	{
		if (num > LLONG_MAX / 10)
			return (1);  // Ha overflow
		if (num == LLONG_MAX / 10 && (str[i] - '0') > 8)
			return (1);  // Ha overflow
	}
	return (0);  // Non ha overflow
}
