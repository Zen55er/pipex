/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:53:30 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/05 11:47:27 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft_new/libft.h"
# include <string.h>
# include <sys/wait.h>

typedef struct s_cmds
{
	char	*cmd;
	char	**cmd_args;
}			t_cmds;

typedef struct s_fds
{
	int		in_fd;
	int		out_fd;
	int		pipes;
	int		**pipefd;
	int		i_pipe;
	int		in;
	int		out;
	int		flag;
}			t_fds;

/*pipex.c*/
char	**get_path(char **envp);
int		check_path(char **paths, char *cmd);
//int		fix_awk_quotes(char *cmd, int *i);
int		single_awk(char *cmd, char c, int *i);
//int		double_awk(char *cmd, int *i);
int		awk_cases(char *cmd, int *i);
int		awk_cmd(t_cmds **cmds, char *cmd);
t_cmds	*get_cmd(char **paths, char *cmd);

/*pipex_utils*/
void	free_double(void **array);
int		big_free(char **paths, t_cmds **cmds, int **pipefd);
int		check_files(char *path1, char *path2);
void	new_process(char *cmd, char **paths, char **envp, t_fds *fds);
void	child(char *cmd, char **paths, char **envp, t_fds *fds);

/*pipex_utils2*/
int		create_pipes(t_fds *fds, int ac);
void	plug_pipes(t_fds *fds);
void	get_flag(int i, int ac, t_fds *fds);
void	get_in_out(t_fds *fds);

#endif