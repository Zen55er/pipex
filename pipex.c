/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:58:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/21 13:23:17 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Tests if infile can be accessed and read from*/
int	infile_test(char *path)
{
	if (access(path, F_OK))
		return (ft_printf("Infile can't be accessed.\n"));
	if (access(path, R_OK))
		return (ft_printf("Infile can't be read.\n"));
	return (0);
}

/*Tests if outfile can be accessed and has read/write permissions*/
int	outfile_test(char *path)
{
	if (access(path, F_OK))
		return (ft_printf("Outfile can't be accessed.\n"));
	if (access(path, R_OK))
		return (ft_printf("Outfile can't be read.\n"));
	if (access(path, W_OK))
		return (ft_printf("Outfile can't be written.\n"));
	return (0);
}

char	**get_path(char **envp)
{
	char	**paths;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (strncmp(envp[i], "PATH", 4))
		{
			paths = ft_split(envp[i], ":");
			break ;
		}
	}
	return (paths);
}

build_path_cmds???

void	child(int *pipefd, int infilefd, char *cmd1)
{
	dup2(infilefd, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	execve()
}

int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	int		proc1;
	int		proc2;
	int		infilefd;
	int		outfilefd;
	char	**paths;

	if (ac != 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile.\n"));
	if (infile_test(av[1]))
		return (1);
	if (outfile_test(av[4]))
		return (1);
	infilefd = open(av[1], O_RDONLY);
	outfilefd = open(av[4], O_RDWR);
	paths = get_path(envp);
	pipe(pipefd);
	proc1 = fork;
	if (!proc1)
		child(&pipefd, infilefd, av[2]);
	else
		parent(&pipefd, outfilefd, av[3]);
	close (pipefd[0]);
	close (pipefd[1]);
	free (paths);
	return (0);
}
