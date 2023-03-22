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

typedef struct s_paths
{
	char	**paths_cmd1;
	char	**paths_cmd2;
}			t_paths;

/*pipex.c*/
t_paths	get_path(char **envp, char *cmd1, char *cmd2);

/*pipex_utils*/
int		big_free(t_paths *paths);
int		infile_test(char *path);
int		outfile_test(char *path);
void	child(int *pipefd, int infilefd, char *cmd1);

#endif