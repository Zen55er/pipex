/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:58:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/05 14:19:59 by gacorrei         ###   ########.fr       */
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

/*Special case for awk calls*/
void	awk_cmd(t_cmds **cmds, char *cmd)
{
	int	i;
	int	j;

	(*cmds)->cmd_args = (char **)malloc(sizeof(char *) * 3);
	(*cmds)->cmd_args[0] = ft_substr(cmd, 0, 3);
	i = 3;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == 39)
		i++;
	j = 0;
	while (cmd[j + i] && cmd [j + i] != 39)
		j++;
	if (j)
		(*cmds)->cmd_args[1] = ft_substr(&cmd[i], 0, j);
	/* else
		(*cmds)->cmd_args[1] = ft_strdup(&cmd[i]); */
	(*cmds)->cmd_args[2] = 0;
	return ;
}

/*Fixes path to have the command at the end and splits args if there are any*/
t_cmds	*get_cmd(char **paths, char *cmd)
{
	t_cmds	*cmds;
	char	*test;
	int		i;

	if (cmd[0] == '/' && check_path(paths, cmd))
		cmd = ft_strrchr(cmd, '/');
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd = 0;
	if (ft_strncmp(cmd, "awk ", 4) == 0)
		awk_cmd(&cmds, cmd);
	else
		cmds->cmd_args = ft_split(cmd, ' ');
	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], cmds->cmd_args[0]);
		if (!access(test, F_OK & X_OK) && !cmds->cmd)
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
