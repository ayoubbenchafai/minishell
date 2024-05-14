#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_env
{
    char **env;
    char **export;
} t_env;

typedef struct s_command
{
    char    **cmd;
    int     input;
    int     output;
    struct s_command   *next;
}       t_command;

typedef struct s_args{
	char	c;
	int		i;
}		t_args;

typedef struct s_node{
	void	*value;
	char	*type;
	struct s_node *next;
}		t_node;

typedef struct s_fd{
	int out;
    int in;
    int flag;
}		t_fd;
typedef struct s_new_list
{
    char        *s;
    char        **array;
    t_command    *cmd;
    t_fd        fd;
}               t_new_list;

typedef struct s_heredoc
{
    int fd_write;
    int fd_read;
}   t_heredoc;

//-----------------------------------------------------
int				ft_cd(char **args, t_env *env);

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	**ft_split(char *original, char c, t_node **addresses);
char	*ft_strdup(const char *str, t_node **addresses);
char	*ft_strjoin(const char *s1, const char *s2, t_node **addresses);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *str, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int	    ft_isalpha(int c);
//-----------------------------------------------------

// t_command *set_newlist(t_node **node, t_env *env, t_node **addresses);
t_command *set_newlist(t_node **node, t_env *env, t_node **addresses);
void handle_space(t_node **node, char ***array, char **s, t_node **addresses);
// void handle_pipe(t_node **node, t_command **cmd, char ***array, t_fd *fd, t_node **addresses);
void handle_pipe(t_node **node, t_new_list **new, t_fd *fd, t_node **addresses);
int  handle_append_or_red_out(t_node **node, int *fd_out, int flag);
int handle_here_doc_or_rd_in(t_node **node, t_fd *fd, char **env, t_node **addresses);
void execute_commands(t_command *cmd, t_env *env, t_node **addresses);
void display_cmd(t_command *cmd);
t_command *ft_lstnew_cmd(char **cmd, int input, int output, t_node **addresses);
void ft_lstadd_back_cmd(t_command **lst, t_command *new);
t_command	*ft_lstlast_cmd(t_command *lst);
char	*ft_join_free(char *s, const char *buf, t_node **addresses);
char	**ft_pathname(char *p, char **cmdargs, char **env, t_node **addresses);
int     ft_herdoc(char *s, char **env, t_node **addresses);
// int     ft_herdoc(char *s, t_env *env, t_node **addresses);
// int ft_herdoc(char *s, t_node **addresses);
// int make_process(t_command *command, t_env *env, t_node **addresses);
int make_process(t_command *command, t_env *env, int *i, t_node **addresses);
char **ft_array(char **array, char *s, t_node **addresses);
//-------------------signals functions
int     exit_status(int exit_status);
void    run_signals(int flag);
void    signal_default();
void    ctr_d();
void    ctr_c(int sig);
//-----------function li zedt-------------


void    signal_here_doc(int sig);
void    ft_read_input(char *s, t_heredoc *heredoc, char **env, t_node **addresses);
void    get_terminal_attr(struct termios *original_termios);
void    restore_terminal_attributes(struct termios *original_termios);

int	    ft_lstsize_cmd(t_command *cmd);
void    ft_putchar_fd(char c, int fd);
void    ft_putendl_fd(char *s, int fd);
char    *ft_itoa(int n, t_node **addresses);
char    *expand_heredoc(char *var, char **env, t_node **addresses);
char    *ft_strtrim(char *s1, char *set, t_node **addresses);
int     ft_atoi(const char *str);
void    exec_exit(char **cmd);
int     ft_isdigit(int c);
void    print_exit_status(char *cmd, int flag, t_node **addresses);
int	    cmp_size(char *env, char *var);
//----
// int check_error(char *var);
int check_error(char *var, int flag);
int get_best_size(char *var);
void swap(char **a, char **b);  
int    case_one(char *var, int *i, int size);
int     case_two(char *var, int i, int size);

//-----------------------
int pipe_parse_error(t_node *node);
char **get_env(char **env);
void exec_export(char **vars, char ***env, char ***ex_env, t_node **addresses);
void exec_unset(char *s, char ***env, t_node **addresses);
int ft_isalnum(int c);
int ft_strcmp(const char *s1, const char *s2);
char    *ft_substr(const char *str, unsigned int start, size_t len, t_node **addresses);
//-----------------------------------------------------
void exec_echo(char **cmd, char **env, t_node **addresses);
char    *get_environment(char **envp, char *var);
int exec_pwd();
int exec_cd(char *path, t_env *env, t_node **addresses);
int is_builtin(t_command *commands, t_env *env, t_node **addresses);
void    expand(t_node *node, t_env *env, t_node **addresses, char *response);
int exec_env(char **env);
// int exec_env(char **env, char **export);
int get_equal(char *s);
void *ft_malloc(size_t size, t_node **addresses);
t_node  *ft_alloc(void *value, char *type);
void	add_back(t_node **lst, t_node *new);
void	free_addresses(t_node *addresses);
t_node  *ft_lstnew1(void *value, char *type, t_node **addresses);
t_node  *ft_lstlast1(t_node *lst);
void	ft_lstadd_back1(t_node **lst, t_node *new);
void    ft_expand(char *line, t_node **commands, int *offset, t_node **addresses);
void    parse_line(char *line, t_node **commands, t_node **addresses, int i);
int     check_char(char *s,char c);
#endif