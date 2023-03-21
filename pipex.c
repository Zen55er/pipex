/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:58:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/21 09:27:09 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	infile_test(char *path)
{
	if (access(path, F_OK))
		return (ft_printf("File can't be accessed.\n"));
	if (access(path, R_OK))
		return (ft_printf("File can't be read.\n"));
	if (access(path, W_OK))
		return (ft_printf("File can't be written.\n"));
	return (0);
}

int	main(int ac, char **av)
{
	if (infile_test(av[1]))
		return (1);
	return (ac);
}
