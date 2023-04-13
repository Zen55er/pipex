/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:00:15 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/13 12:41:44 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Frees double pointer*/
void	free_double(void **array)
{
	int	i;

	i = -1;
	while (array [++i])
		free (array [i]);
	free (array);
	return ;
}

/*Frees everything*/
int	big_free(char **paths, t_cmds **cmds, int **pipefd, t_fds *fds)
{
	int	i;

	if (paths)
		free_double((void *)paths);
	if (cmds)
	{
		i = -1;
		while ((*cmds)->cmd_args[++i])
			free ((*cmds)->cmd_args[i]);
		free ((*cmds)->cmd_args);
		free ((*cmds)->cmd);
		free((*cmds));
	}
	if (pipefd)
		free_double((void *)pipefd);
	if (fds && fds->here_doc)
		unlink(".here_doc");
	return (0);
}

/*Opens output file*/
void	get_outfile(t_fds *fds, int ac, char **av)
{
	if (fds->here_doc)
		fds->out_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fds->out_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	return ;
}

/*Input and output file checks*/
int	check_files(t_fds *fds, int ac, char **av)
{
	char	*input;

	if (fds->here_doc)
		input = ".here_doc";
	else
		input = av[1];
	if (access(input, F_OK | R_OK))
		perror("pipex: input");
	if (access(av[ac - 1], F_OK))
	{
		fds->in_fd = open(input, O_RDONLY);
		get_outfile(fds, ac, av);
		return (0);
	}
	if (access(av[ac - 1], R_OK | W_OK))
	{
		perror("pipex: input");
		return (1);
	}
	fds->in_fd = open(input, O_RDONLY);
	get_outfile(fds, ac, av);
	return (0);
}

/*Handles here_doc cases*/
int	here_doc(char **av, t_fds *fds)
{
	char	*temp;

	if (ft_strncmp(av[1], "here_doc", 8))
	{
		fds->here_doc = 0;
		return (1);
	}
	fds->here_doc = 1;
	fds->here_doc_fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		temp = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(temp, av[2], ft_strlen(av[2])))
			break ;
		else
			write(fds->here_doc_fd, temp, ft_strlen(temp));
		free(temp);
	}
	free(temp);
	close(fds->here_doc_fd);
	return (0);
}
