/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:53:30 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/21 09:32:07 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft_new/libft.h"
# include <string.h>
# include <sys/wait.h>

typedef struct s_cmds
{
	char	*cmd1;
	char	**cmd1_args;
	char	*cmd2;
	char	**cmd2_args;
}			t_cmds;

/*pipex.c*/
char	**get_path(char **envp);
void	check_args(t_cmds **cmds, char *cmd1, char *cmd2);
t_cmds	*get_cmds(char **paths, char *cmd1, char *cmd2)

/*pipex_utils*/
int		big_free(char **doublep);
int		infile_test(char *path);
int		outfile_test(char *path);
void	child(int *pipefd, int infilefd, char *cmd1);

#endif