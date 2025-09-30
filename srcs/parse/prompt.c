#include "minishell.h"

static char	*color_getuser(char *user, char *host);
static char	*color_prompt(char *buff, int len, char *start);

/* stampa l'ultima directory in cui si trova */
char	*ft_getdir(void)
{
	char	buff[PATH_MAX];
	char	*start;
	int		len;

	getcwd(buff, PATH_MAX);
	len = ft_strlen(buff);
	start = buff + len;
	while (*start != '/')
	{
		start--;
		len--;
	}
	return (color_prompt(buff, len, start));
}

static char	*color_prompt(char *buff, int len, char *start)
{
	char	*prompt;
	char	*result;
	char	*colored_prompt;

	prompt = ft_substr(buff, len, ft_strlen(start));
	colored_prompt = ft_strjoin(CYAN, prompt);
	free(prompt);
	result = ft_strjoin(colored_prompt, RESET "$ ");
	free(colored_prompt);
	return (result);
}

/* stampa user@localhost */
char	*ft_getuser(void)
{
	char	*user;
	char	*host;

	user = getenv("USER");
	if (user == NULL)
		user = "unknown";
	host = getenv("HOSTNAME");
	if (host == NULL)
		host = "localhost";
	return (color_getuser(user, host));
}

static char	*color_getuser(char *user, char *host)
{
	char	*color_user;
	char	*color_host;
	char	*temp;
	char	*result;

	color_user = ft_strjoin(YELLOW, user);
	color_host = ft_strjoin(color_user, "@");
	temp = ft_strjoin(color_host, host);
	result = ft_strjoin(temp, RESET ":");
	free(color_user);
	free(temp);
	free(color_host);
	return (result);
}

/* stampa il prompt finale */
char	*ft_getprompt(void)
{
	char	*result;
	char	*user;
	char	*dir;

	user = ft_getuser();
	dir = ft_getdir();
	result = ft_strjoin(user, dir);
	free(user);
	free(dir);
	return (result);
}
