/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:24:16 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/10 10:05:09 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Gets PATH from envp and adds '/' at the end*/
char	**get_path(char **envp)
{
	char	**paths;
	int		i;
	char	*temp1;

	i = -1;
	while (envp[++i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break ;
	}
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		temp1 = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free (temp1);
	}
	return (paths);
}

/*Checks if the given command is in PATH*/
int	check_path(char **paths, char *cmd)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (ft_strncmp(paths[i], cmd, ft_strlen(paths[i])) == 0)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_fds	fds;
	char	**paths;
	int		i;

	if (ac < 5)
		return (ft_printf("Usage: ./pipex infile cmd1 ... cmdn outfile.\n"));
	if (check_files(av[1], av[ac - 1]))
		return (1);
	fds.in_fd = open(av[1], O_RDONLY);
	fds.out_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (create_pipes(&fds, ac))
		return (2);
	paths = get_path(envp);
	fds.i_pipe = 0;
	i = -1;
	while (++i < ac - 3)
	{
		get_flag(i, ac, &fds);
		new_process(av[i + 2], paths, envp, &fds);
	}
	close(fds.in_fd);
	close(fds.out_fd);
	plug_pipes(&fds);
	big_free(paths, 0, fds.pipefd);
	return (0);
}
