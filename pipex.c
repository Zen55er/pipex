/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:58:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/20 13:28:11 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	infile_test(char *path)
{
	if (!access(path, F_OK))
		return (ft_printf("File can be accessed.\n"));
	if (!access(path, R_OK))
		return (ft_printf("File can be read.\n"));
	if (!access(path, W_OK))
		return (ft_printf("File can be written.\n"));
	return (0);
}

int	main(int ac, char **av)
{
	if (!infile_test(av[1]))
		return (ft_printf("Can't access infile\n"));
	return (ac);
}
