/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:14:55 by iportill          #+#    #+#             */
/*   Updated: 2023/10/18 20:01:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "Libft/libft.h"
# define BUFFER_SIZE 120000
# include <fcntl.h>  //open O_RDONLY
# include <stdio.h>  //printf
# include <stdlib.h> //malloc
# include <unistd.h> //write
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# define WRITE 1
# define READ 0

typedef struct s_pipex
{
	char	*contenido_archivo_argv1;
	char	*contenido_archivo_argv4;
	char	*cmd1;
	char	*cmd2;
	char	**cmd1_split;
	char	**cmd2_split;
	char	*cmd1_info;
	char	*cmd2_info;
	char	*infile;
	char	*outfile;
	char	*path_raw;
	char	**path_split;
	char	**path_raw_split;
	char	**path_raw_split_repair;
	char	*executable_path_cmd1;
	char	*executable_path_cmd2;
	char	**env;
	int		fd1[2];
	pid_t	child_pid;
	int		a;
	int		b;
	int		argc;
	int		status;
}			t_pipex;

void		correct_argc(int argc);
t_pipex		*create_struc(t_pipex *p, int argc, char **argv, char **env);
char		*find_env_file(char **env, t_pipex *p);
void		repair_and_check_path_raw_split(t_pipex *p);
int			ft_open_r(char *s);
int			ft_open_w(char *s);
void		open_infile_outfile(t_pipex *p);
void		close_infile_outfile(t_pipex *p);
char		*try_path_access(char **s1, char *s2);
void		cmd1(t_pipex *p);
void		cmd2(t_pipex *p);
int			pipex(t_pipex *p);
void		free_split(char **split);
void		cleanup(t_pipex *p);

int			ft_wordlen(const char *s, char c);
char		*word_dupe(const char *s, char c);
int			count_words(const char *s, char c);
void		fill_words(char **array, const char *s, char c);
char		**ft_split(const char *s, char c); //mirar los free del split

#endif