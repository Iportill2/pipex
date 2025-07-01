/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:05:33 by iportill          #+#    #+#             */
/*   Updated: 2023/10/04 12:07:28 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	cmd1(t_pipex *p)
{
	dup2(p->a, STDIN_FILENO);
	close(p->fd1[READ]);
	dup2(p->fd1[WRITE], STDOUT_FILENO);
	execve(p->executable_path_cmd1, p->cmd1_split, p->env);
	perror("execve cmd1");
	exit(EXIT_FAILURE);
}

void	cmd2(t_pipex *p)
{
	if (p->child_pid == -1)
	{
		perror("Error al crear el hijo");
		close(p->a);
		exit(1);
	}
	if (p->child_pid == 0)
	{
		close(p->fd1[WRITE]);
		dup2(p->fd1[READ], STDIN_FILENO);
		dup2(p->b, STDOUT_FILENO);
		execve(p->executable_path_cmd2, p->cmd2_split, p->env);
		perror("execve cmd2");
		exit(EXIT_FAILURE);
	}
	else
		close(p->fd1[WRITE]);
}

int	pipex(t_pipex *p)
{
	p->child_pid = fork();
	if (p->child_pid == -1)
	{
		perror("Error al crear el hijo");
		close(p->a);
		return (EXIT_FAILURE);
	}
	else if (p->child_pid == 0)
		cmd1(p);
	else
	{
		waitpid(p->child_pid, &p->status, 0);
		p->child_pid = fork();
		cmd2(p);
	}
	waitpid(p->child_pid, &p->status, 0);
	return (0);
}
