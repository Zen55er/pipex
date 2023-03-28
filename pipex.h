/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:53:30 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/28 11:56:12 by gacorrei         ###   ########.fr       */
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
	int		pipefd1[2];
	int		pipefd2[2];
	int		in;
	int		out;
	int		flag;
}			t_fds;

/*pipex.c*/
char	**get_path(char **envp);
t_cmds	*get_cmd(char **paths, char *cmd);

/*pipex_utils*/
int		big_free(char **paths, t_cmds **cmds);
int		infile_test(char *path);
int		outfile_test(char *path);
int		create_pipes(t_fds *fds);
void	new_process1(char *cmd, char **paths, char **envp, t_fds *fds);
void	new_process2(char *cmd, char **paths, char **envp, t_fds *fds);
void	child(t_cmds **cmds, char **envp, int in, int out);

/*pipex_utils2*/
void	plug_pipe(int pipefd[2]);
void	get_in_out(t_fds *fds);

#endif