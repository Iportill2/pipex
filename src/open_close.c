/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:10:52 by iportill          #+#    #+#             */
/*   Updated: 2023/10/03 16:58:13 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_infile_outfile(t_pipex *p)
{
	p->a = ft_open_r(p->infile);
	p->b = ft_open_w(p->outfile);
}

void	close_infile_outfile(t_pipex *p)
{
	close(p->a);
	close(p->b);
}

int	ft_open_r(char *s)
{
	int	i;

	i = open(s, O_RDONLY);
	if (i == -1)
	{
		perror("Error al abrir el archivo de lectura ");
		close(i);
		exit(1);
	}
	return (i);
}

int	ft_open_w(char *s)
{
	int	i;

	i = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (i == -1)
	{
		perror("Error al abrir el archivo para escribir en el");
		close(i);
		exit(1);
	}
	return (i);
}
