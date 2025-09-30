/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 00:46:13 by lluciani          #+#    #+#             */
/*   Updated: 2025/09/27 15:57:35 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child(t_data *data, t_token *tokens, int fd);

int	here_doc(t_data *data, t_token *tokens, t_command *command)
{
	int			fd;
	pid_t		pid;
	char		*filename;
	int			status;
	static int	i;

	status = 0;
	filename = temp_filename(i++);
	if (!filename)
		return(-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_error(fd, filename) == 1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		status = handle_child(data, tokens, fd);
		exit(status);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	command->heredoc_fd = fd;
	free(filename);
	g_status_signal = 0;
	signal_handler(SIGINT, sigint_handler);
	return (status);
}

int	child_process(t_data *data, t_token *tokens, int fd)
{
	char	*line;
	char	*delimiter;

	line = NULL;
	delimiter = is_h_delimiter(tokens);
	//printf("delimiter is:%s\n", delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			break ;
		}
		else
		{
			if (is_expansion(tokens) == 1)
				line = expand_line(data, line);
			ft_putendl_fd(line, fd);
			free(line);
		}
	}
	return (1);
}

char	*temp_filename(int i)
{
	char	*str;
	char	*num;

	num = ft_itoa(i);
	str = ft_strjoin("temp_heredoc_", num);
	free(num);
	return (str);
}

char	*expand_line(t_data *data, char *str)
{
	int		i;
	char	*temp;
	char	*result;

	i = 0;
	result = NULL;
	temp = NULL;
	while (str[i])
	{
		temp = ft_strcpy_mod(str, &i);
		result = safe_strjoin(result, temp);
		safe_free(temp);
		if (str[i] == '$')
			result = allow_expansion(data, str, result, &i);
	}
	if (str[0] == '\0')
		result = ft_strdup("");
	return (result);
}

static int	handle_child(t_data *data, t_token *tokens, int fd)
{
	int	status;

	g_status_signal = 0;
	signal_handler(SIGINT, heredoc_handler);
	status = child_process(data, tokens, fd);
	return (status);
}
