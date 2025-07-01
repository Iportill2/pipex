/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:27:11 by iportill          #+#    #+#             */
/*   Updated: 2023/10/04 12:04:36 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*p;
	int		status;

	p = NULL;
	correct_argc(argc);
	p = create_struc(p, argc, argv, env);
	repair_and_check_path_raw_split(p);
	open_infile_outfile(p);
	p->executable_path_cmd1 = try_path_access(p->path_raw_split,
			p->cmd1_split[0]);
	p->executable_path_cmd2 = try_path_access(p->path_raw_split,
			p->cmd2_split[0]);
	if (!p->executable_path_cmd1 || !p->executable_path_cmd2)
	{
		perror("Command not found");
		cleanup(p);
		return (127);
	}
	pipe(p->fd1);
	status = pipex(p);
	close_infile_outfile(p);
	cleanup(p);
	return (status);
}
