/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:17:12 by iportill          #+#    #+#             */
/*   Updated: 2023/10/03 16:54:53 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_wordlen(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	*word_dupe(const char *s, char c)
{
	int		len;
	char	*word;
	int		i;

	i = 0;
	len = ft_wordlen(s, c);
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
	{
		perror("Error en malloc");
		exit(1);
	}
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

int	count_words(const char *s, char c)
{
	int	i;
	int	num_words;

	i = 0;
	num_words = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		num_words++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (num_words);
}

void	fill_words(char **array, const char *s, char c)
{
	int	i;
	int	word_index;

	i = 0;
	word_index = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (s[i])
	{
		array[word_index] = word_dupe(s + i, c);
		word_index++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
}

char	**ft_split(const char *s, char c)
{
	int		num_words;
	char	**array;

	num_words = count_words(s, c);
	array = malloc(sizeof(char *) * (num_words + 1));
	if (array == NULL)
	{
		perror("Error en malloc");
		exit(1);
	}
	fill_words(array, s, c);
	array[num_words] = NULL;
	return (array);
}
