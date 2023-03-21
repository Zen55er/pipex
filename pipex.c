/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:58:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/21 09:31:52 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	infile_test(char *path)
{
	if (access(path, F_OK))
		return (ft_printf("Infile can't be accessed.\n"));
	if (access(path, R_OK))
		return (ft_printf("Infile can't be read.\n"));
	return (0);
}

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

int	main(int ac, char **av)
{
	if (ac != 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"));
	if (infile_test(av[1]))
		return (1);
	if (outfile_test(av[4]))
		return (1);
	return (ac);
}
