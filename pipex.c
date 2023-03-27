/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:58:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/27 11:36:37 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

/*Fixes path to have the command at the end and splits args if there are any*/
t_cmds	*get_cmd(char **paths, char *cmd)
{
	t_cmds	*cmds;
	char	*test;
	int		i;

	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd = 0;
	cmds->cmd_args = ft_split(cmd, ' ');
	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], cmds->cmd_args[0]);
		if (!access(test, F_OK) && !cmds->cmd)
			cmds->cmd = test;
		else
			free(test);
		if (cmds->cmd)
			break ;
	}
	return (cmds);
}

int	main(int ac, char **av, char **envp)
{
	t_fds	fds;
	char	**paths;
	int		i;

	if (ac != 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile.\n"));
	if (infile_test(av[1]))
		return (1);
	if (outfile_test(av[4]))
		return (2);
	fds.in_fd = open(av[1], O_RDONLY);
	fds.out_fd = open(av[4], O_RDWR);
	paths = get_path(envp);
	i = -1;
	while (++i < ac - 3)
	{
		if (i == 0)
			new_process(av[i + 2], paths, envp, (t_fds){fds.in_fd, 0});
		else if (i == ac - 2)
			new_process(av[i + 2], paths, envp, (t_fds){0, fds.out_fd});
		else
			new_process(av[i + 2], paths, envp, (t_fds){0, 0});
			
	}
	close(fds.in_fd);
	close(fds.out_fd);
	big_free(paths, 0);
	return (0);
}
