/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:03:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/19 12:22:51 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	awk_quotes(char *cmd, char c, int *i)
{
	int	len;

	*i += 1;
	len = ft_strlen(cmd + 1);
	if (cmd[len] == c)
		return (len - 1);
	return (0);
}

/*Special case for awk calls.*/
int	awk_cmd(t_cmds **cmds, char *cmd)
{
	int	i;
	int	j;

	i = 3;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == 34 || cmd[i] == 39)
		j = awk_quotes(&cmd[i], cmd[i], &i);
	if (j == 0)
		return (1);
	(*cmds)->cmd_args = (char **)malloc(sizeof(char *) * 3);
	(*cmds)->cmd_args[0] = ft_substr(cmd, 0, 3);
	if (j)
		(*cmds)->cmd_args[1] = ft_substr(&cmd[i], 0, j);
	else
		(*cmds)->cmd_args[1] = ft_strdup(&cmd[i]);
	(*cmds)->cmd_args[2] = 0;
	return (0);
}

/*Tests commands against path*/
void	test_cmd(char **paths, t_cmds **cmds)
{
	int		i;
	char	*test;

	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], (*cmds)->cmd_args[0]);
		if (!access(test, F_OK & X_OK) && !(*cmds)->cmd)
			(*cmds)->cmd = test;
		else
			free(test);
		if ((*cmds)->cmd)
			break ;
	}
	return ;
}

/*Fixes path to have the command at the end and splits args if there are any*/
t_cmds	*get_cmd(char **paths, char *cmd)
{
	t_cmds	*cmds;

	if (cmd[0] == '/' && check_path(paths, cmd))
		cmd = ft_strrchr(cmd, '/');
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd = 0;
	if (ft_strncmp(cmd, "awk ", 4) == 0 || ft_strncmp(cmd, "sed ", 4) == 0)
	{
		if (awk_cmd(&cmds, cmd))
			return (cmds);
	}
	else
		cmds->cmd_args = ft_split(cmd, ' ');
	test_cmd(paths, &cmds);
	return (cmds);
}

/*Waits for each child to end, closes files' fd's and remaining pipes*/
void	big_wait(t_fds *fds)
{
	int		i;

	i = -1;
	while (++i < fds->i)
		waitpid(fds->pids[i], 0, 0);
	close(fds->in_fd);
	close(fds->out_fd);
	plug_pipes(fds);
	return ;
}
