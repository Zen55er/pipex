/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:53:30 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/30 15:38:52 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
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
int		check_path(char **paths, char *cmd);
t_cmds	*get_cmd(char **paths, char *cmd);

/*pipex_utils*/
int		big_free(char **paths, t_cmds **cmds);
int		check_files(char *path1, char *path2);
void	new_process(char *cmd, char **paths, char **envp, t_fds *fds);
void	child(char *cmd, char **paths, char **envp, t_fds *fds);

/*pipex_utils2*/
int		create_pipes(t_fds *fds);
void	plug_pipes(int pipefd1[2], int pipefd2[2]);
void	get_flag(int i, int ac, t_fds *fds);
void	get_in_out(t_fds *fds);

#endif