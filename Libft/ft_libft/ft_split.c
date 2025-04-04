/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:59:04 by jdhallen          #+#    #+#             */
/*   Updated: 2024/10/22 14:06:37 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft.h"

static void	ft_freeall(char **l, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(l[i]);
		i++;
	}
	free(l);
}

static size_t	ft_lsep(const char *s, const char c)
{
	size_t	ts;
	size_t	x;
	int		in_sub;

	x = 0;
	ts = 0;
	in_sub = 0;
	while (s[x] != '\0')
	{
		if (s[x] != c && in_sub == 0)
		{
			in_sub = 1;
			ts++;
		}
		else if (c == s[x])
			in_sub = 0;
		x++;
	}
	return (ts);
}

static size_t	ft_tsep(const char *s, const char c, size_t *start)
{
	size_t	x;

	x = 0;
	while (s[*start] != '\0' && s[*start] == c)
		(*start)++;
	while (s[*start] != '\0' && s[*start] != c)
	{
		x++;
		(*start)++;
	}
	return (x);
}

static char	*ft_talloc(const char *s, char c, size_t *j)
{
	size_t	k;
	size_t	len;
	char	*t;

	len = ft_tsep(s, c, j);
	t = (char *)malloc((len + 1) * sizeof(char));
	if (t == NULL)
		return (NULL);
	k = 0;
	while (k < len)
	{
		t[k] = s[*j - len + k];
		k++;
	}
	t[k] = '\0';
	return (t);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**l;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s[0] == '\0')
	{
		l = (char **)malloc(sizeof(char *));
		if (l == NULL)
			return (NULL);
		return (l[0] = NULL, l);
	}
	l = (char **)malloc((ft_lsep(s, c) + 1) * sizeof(char *));
	if (l == NULL)
		return (NULL);
	while (i < ft_lsep(s, c))
	{
		l[i] = ft_talloc(s, c, &j);
		if (l[i++] == NULL)
			return (ft_freeall(l, i - 1), NULL);
	}
	return (l[i] = NULL, l);
}

/*
int	main(void)
{
	char	*so1;
	char	so2;
	char	**so3;
	size_t	p;

	so1 = "\0 abbsv\0gdv";
	so2 = '\0';
	p = 0;
	so3 = ft_split(so1, so2);
	printf("Avant : %s, %c \n", so1, so2);
	while (so3[p] != NULL)
	{
		printf("%s", so3[p]);
		printf("\n");
		p++;
	}
	printf("\n");
	free(so3);
	return (0);
}
*/
