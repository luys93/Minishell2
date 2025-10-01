/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:37 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 18:40:58 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     MINISHELL_H
#define     MINISHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
// # include <linux/limits.h>
# include <errno.h>
# include <sys/stat.h>

# define RED 		"\001\033[91m\002"
# define GREEN 		"\001\033[92m\002"
# define YELLOW		"\001\033[93m\002"
# define BLUE 		"\001\033[94m\002"
# define MAGENTA 	"\001\033[95m\002"
# define CYAN 		"\001\033[96m\002"
# define WHITE 		"\001\033[97m\002"
# define RESET 		"\001\033[0m\002"

#define	T_QUOTES  0
#define	T_WORDS  1
#define	T_METACHAR  2
#define T_SKIP 3
#define T_EOF -1


typedef enum token_type
{
	NONE = 0,
	PIPE = 1 << 1,
	HERE_DOC = 1 << 2,
	R_IN = 1 << 3,
	APPEND = 1 << 4,
	R_OUT = 1 << 5,
	CMD = 1 << 6,
	LIMITER = 1 << 7,
	DELIMITER = 1 << 8,
	REDIRECT = 1 << 9,
	FILENAME = 1 << 10,
	ARG = 1 << 11,
	WORD = 1 << 12,
	QUOTED = 1 << 13,
	METACHAR = 1 << 14,
	
}							token_type;

typedef struct s_token t_token;
typedef struct s_command  t_command;

extern int 						g_status_signal;

typedef struct s_data
{
	char 				**env;
    char                *input;
	char 				*prompt;
	int					exit_status;
	t_token 			*tokens;
	t_command 			*command;
}                           t_data;  

typedef struct s_token
{
	char 				*value;
    token_type          type;
	token_type			subtype;
	char				quote_type;
	char 				must_joined;

	struct	s_token *next;
}                           t_token;

typedef struct s_dir
{
	char *type; 
	char *file;   
	struct s_dir *next;
}						t_dir;

typedef struct s_command        
{
	char 				**argv;
	char 				*path;
	int 				heredoc_fd;
	int 				append;
	t_dir 				*rediraction;
	struct s_command 	*next;
}                              t_command;

/*-----------------PARSER-------------------------------*/
/* expansions */
char *extract_word(char *str, int *pos);
char 		*check_expansion(t_data *data, t_token *tokens);
char *replace_value(t_data *data, char *str, int *pos);
char  *get_env(char *str);
char *ft_strcpy_mod(char *str, int *pos);
int is_valid(char c);
char *allow_expansion(t_data *data, char *str, char *pre_value, int *i);
char	*reset_value(char **str, char *result, int flag);
char *exit_status(t_data *data, char *str, char *pre_value, int *i);
char *expansion_core(t_data *data, char *str, int *i);
char *no_expansion(char *str);
char *handle_empty_str(t_token *prev, t_token *current, char *result);

/* rediractions */
t_dir		*add_redirection(t_command *cmd, char *type, char *file);
void    print_redir(t_command *cmd);
//int rediraction_error(t_command *command);
int rediraction_error(t_data *data, t_command *command);

/* init */
t_command 	*init_command(void);
void 		init_env(t_data *data);
void 		inizialize(t_command **cmd, t_command **head, t_command **tail);

/* input */
int 		read_line(t_data *data);
int 		check_input(t_data *data);
int 		control_string(t_data *data);
int 		handle_input(t_data *data);

/* split */
int 		tokenizer(t_data *data);
int 		detect_token(t_data *data, int i);
int 	split_metachar(t_data *data, int i, int *pos);
int 	split_quote(t_data *data, int i, int *pos);
int 	split_word(t_data *data, int i, int *pos);

/* split utils */
int  		is_match(char *s);
int  		is_delimiter(char c);
int 		is_double_quotes(char c);
int 		is_quotes(char c);
int 		is_space(char c);

/* parser */
void 		parsing(t_data *data);
t_command 	*parser(t_data *data, t_command **head, t_command **tail, t_token *tokens);
t_token 	*parse_cmd(t_command **cmd, t_command **head, t_command **tail, t_token *token);
t_token 	*handle_redir_in_and_heredoc(t_command **cmd, t_token *tokens, t_command **head, t_command **tail);
t_token 	*handle_redir_out_and_append(t_command **cmd, t_token *tokens, t_command **head, t_command **tail);

/* parser utils */
t_token 	*parse_here_doc(t_command **cmd, t_token *token);
t_token 	*parse_r_in(t_command **cmd, t_token *token);
t_token 	*parse_append(t_command **cmd, t_token *token);
t_token 	*parse_r_out(t_command **cmd, t_token *token);
t_token 	*parse_arg(t_command **cmd, t_token *token);
int	parse_condition(t_token *token, t_token *prev);
t_token *handle_cmd_and_arg(t_command **cmd, t_token *tokens, t_command **head, t_command **tail);

/* list utils */
t_token 	*add_token_to_list(t_data *data, char *value, token_type type, char quote_type);
void 		add_arg(t_command *cmd, char *value);

/* token_utils */
void 		add_type(t_data *data);
void 		joined_token(t_token *token);

/* utils */
void 		ft_free_array(char **array);
char 		*safe_strjoin(char *s1, char *s2);
void		safe_free(void *ptr);
void    print_token(t_token *head);

/* here_doc*/
char *is_h_delimiter(t_token *tokens);
int here_doc(t_data *data, t_token *tokens, t_command *command);
int child_process(t_data *data, t_token *tokens, int fd);
char *temp_filename(int i);
char *expand_line(t_data *data, char *str);
int here_doc_condition(t_command *command);
int is_expansion(t_token *tokens);
int fd_error(int fd, char *filename);

/* prompt */
char		*ft_getprompt(void);
char   		*ft_getuser(void);
char    	*ft_getdir(void);

/* free */
void 		free_all_cmd(t_command *cmd);
void 		free_all_token(t_token *token);
void 		free_env(char **env);
void 		free_rediraction(t_dir *dir);
void 		free_all(t_data *data, char flag);

/* error */
int error_pipe(t_data *data);
int split_word_error(int *pos, t_data *data, int i);

/*----------------SIGNALS----------------------------------------*/
int signal_handler(int sigtype, void(*f_hanlder)(int s));
void	heredoc_handler(int sig);
void sigquit_handler(int sig);
void sigint_handler(int sig);

/*----------------EXECUTOR----------------------------------------*/
/* executor */
void    	ft_execution(t_data *data, t_command *cmd);
void    	ft_pipe(t_data *data, t_command *cmd);
void    	pipe_simple(t_data *data, t_command *cmd);
void    	pipe_with_redirection(t_data *data, t_command *cmd);

/* command */
void    	cmd_simple(t_data *data, t_command *cmd);
pid_t   	ft_child_pipe_s(t_data *data, t_command *cmd);
pid_t    	ft_last_child_s(t_data *data, t_command *cmd);
void 		execute_for_pipe(t_data *data, t_command *cmd);

/* check command*/
int     	check_command(t_data *data, t_command *cmd);
int     	command_exists(t_data *data, t_command *cmd);
char 		*search_path(char *cmd, char **env);
int     	check_file(t_command *cmd);

/* redirections */
int     	apply_redirection(t_data *data, t_command *cmd);
void    	cmd_with_redirection(t_data *data, t_command *command);
void    	builtin_with_redirection(t_data *data, t_command *cmd);

/* redirections utils */
int     	handle_append_redir(t_data *data, char *filename);
int     	handle_output_redir(t_data *data, char *filename);
int     	handle_input_redir(t_data *data, char *filename);
int			handle_heredoc_redir(t_command *cmd);

/* pipe redirections */
pid_t 		ft_child_pipe_with_redir(t_data *data, t_command *cmd);
pid_t 		ft_last_child_with_redir(t_data *data, t_command *cmd);
void 		execute_for_pipe_with_redir(t_data *data, t_command *cmd);


/* utils */
int    		ft_file(t_data *data, char *filename, int flag);
void    	ft_error_process(char *str, int status);
int     	count_commands(t_command *cmd);
void 		error_case(t_data *data, const char *path);
void    	error_process(t_data *data, char *argv, char *str, int status);

/*----------------BUILTINS----------------------------------------*/
/* builtins */
void    	execute_builtins(t_data *data, t_command *cmd, char *str);
int     	is_builtin(char *str);
/* exit */
 void    	ft_exit(t_data *data); //, int *i); //lo sto testando
/* pwd */
void    	ft_pwd(t_data *data);
/* echo */
void    	ft_echo(t_data *data, t_command *cmd); //, int *i);
int     	check_n(char *str);
/* cd */
void    	ft_cd(t_data *data, t_command *cmd); // int *i);
/* env */
void    	ft_env(t_data *data);
/* export */
void    	ft_export(t_data *data, t_command *cmd);
int     	valid_value(t_data *data, char *str);  //sto testando
void    	ft_update_export(t_data *data, char *str);
void    	print_sort_env(char **env);
void    	sort_env(char **env);
/* unset */
void    ft_unset(t_data *data, t_command *cmd);
int     valid_identifier(char *str);
void    ft_update_unset(t_data *data, char *key);
int     find_unset_keypos(t_data *data, char *str, int keylen);

/* utils for export */
void    	copy_env(char **new_env, char **old_env, int count);
int 		count_env(char **env);
int     	find_keypos(t_data *data, char *str, int keylen);
int     	find_keylen(char *str);

/* utils for builtins */
int     	ft_count_token(t_token *tokens);
//int     	ft_count_argument(t_command *cmd, int *count);
int     ft_count_argument(t_command *cmd);
int     	check_exit(char *str);
int			check_overflow(int sign, long long int num, char *str, int i);

/* prove */
char    	*token_type_str(token_type type);
void    	print_token(t_token *head);
void 		print_command_list (t_command *cmd);
void    	print_dir(t_command *cmd);

void	free_temp(t_data *data, int flag);
void free_path(t_command *cmd);



//-------------------------------

int search_first_builtins(t_command *cmd);
char *get_env_value(char **env, const char *var);

#endif