/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:47:27 by jdhallen          #+#    #+#             */
/*   Updated: 2025/04/07 08:04:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random_gen.h"

void	free_charpp(char ***charpp)
{
	int	i;

	if (!*charpp)
		return ;
	i = 0;
	while ((*charpp)[i] != NULL)
	{
		free((*charpp)[i]);
		i++;
	}
	free(*charpp);
}

int	ft_rand(t_rand *random, int min, int max)
{
	int	nbr;
	
	if (max <= min)
		return (min);
	random->random += (random->random) % 2147483647;//* random->random_utils) % 2147483647;
	if (random->random % 2147483647 == 0)
		random->random = time(NULL) % 2147483647;
	nbr = (random->random % max);
	if (nbr < 0)
		nbr *= -1;
	nbr += min;
	return (nbr);
}

bool	ft_rand_percent(t_rand *random, int percent)
{
	bool	boolean;
	int		nbr;
	
	boolean = false;
	if (percent <= 0)
		return (false);
	if (percent >= 100)
		return (true);
	nbr = ft_rand(random, 0, 100);
	if (nbr <= percent)
		boolean = true;
	return (boolean);
}

char	*ft_create_map_name(t_rand *random, int len)
{
	char	*name;
	char	c;
	int		i;

	i = 0;
	name = malloc((len + 1) * sizeof(char *));
	while (i < len)
	{
		c = 0;
		while (!ft_isalnum(c))
		{
			c = 48;
			c += ft_rand(random, 0, 122 - 48);
		}
		name[i] = c;
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	create_map_alloc(t_rand *random)
{
	int	i;
	int	j;

	random->map = malloc((random->size + 1) * sizeof(char*));
	if (random->map == NULL)
		return (ERROR);
	i = 0;
	while (i < random->size)
	{
		random->map[i] = malloc((random->size + 1) * sizeof(char));
		if (random->map[i] == NULL)
			return (free_charpp(&random->map), ERROR);
		j = 0;
		while (j < random->size)
		{
			random->map[i][j] = 'X';
			j++;
		}
		random->map[i][j] = '\0';
		i++;
	}
	random->map[i] = NULL;
	return (TRUE);
}

int	random_map_generator_space(t_rand *random)
{
	int	i;
	int	j;
	int	percent;
	int	median;
	int	distance;

	median = random->size / 2;
	percent = 0;
	i = 0;
	while (i < random->size)
	{
		j = 0;
		while (j < random->size)
		{
			distance = i;
			if (j < distance)
				distance = j;
			if (random->size - 1 - i < distance)
				distance = random->size - 1 - i;
			if (random->size - 1 - j < distance)
				distance = random->size - 1 - j;
			percent = (20 + ft_rand(random, -10, 10)) * (1.0 - ((float)distance / median));
			if (ft_rand_percent(random, percent) == true)
				random->map[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	random_map_generator_wall(t_rand *random)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	wall;
	int	percent;

	percent = 0;
	i = 0;
	while (i < random->size)
	{
		j = 0;
		while (j < random->size)
		{
			percent = 5;
			wall = 0;
			if (random->map[i][j] == 'X')
			{
				k = i - 1;
				while (k <= i + 1)
				{
					l = j - 1;
					while (l <= j + 1 )
					{
						if (k >= 0 && l >= 0 
							&& l < random->size
							&& k < random->size
							&& random->map[k][l] == '1')
							wall++;
						l++;
					}
					k++;
				}
			}
			wall = 5 * wall;
			if (wall > 60)
				wall = 60;
			percent += wall;
			if (ft_rand_percent(random, percent) == true)
				random->map[i][j] = '2';
			j++;
		}
		i++;
	}
	i = 0;
	while (i < random->size)
	{
		j = 0;
		random->map[i][j] = '1';
		while (j < random->size)
		{
			if (i == 0 || i == random->size - 1)
				random->map[i][j - 1] = '1';
			if (random->map[i][j] == '2')
				random->map[i][j] = '1';
			j++;
		}
		random->map[i][j - 1] = '1';
		i++;
	}
	return (TRUE);
}

int	map_generator_wall(t_rand *random)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	while (i < random->size)
	{
		j = 0;
		while (j < random->size)
		{
			if (random->map[i][j] == ' ')
			{
				k = i - 1;
				while (k <= i + 1)
				{
					l = j - 1;
					while (l <= j + 1 )
					{
						if (k >= 0 && l >= 0 
							&& l < random->size
							&& k < random->size
							&& random->map[k][l] == 'X')
							random->map[k][l] = '1';
						l++;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	player_gen(t_rand *random)
{
	int	i;
	int	j;
	int	dir;
	int	x_nbr_now;
	int	x_numb;
	int	percent;
	int	player;

	player = 0;
	x_numb = 0;
	i = 0;
	while (i < random->size)
	{
		j = 0;
		while (j < random->size)
		{
			if (random->map[i][j] == 'X')
				x_numb++;
			j++;
		}
		i++;
	}
	x_nbr_now = x_numb;
	percent = 1;
	i = 0;
	while (i < random->size)
	{
		j = 0;
		while (j < random->size)
		{
			if (random->map[i][j] == 'X')
			{
				x_nbr_now--;
				if (ft_rand_percent(random, percent) == true && player == 0)
				{
					dir = ft_rand(random, 0, 3);
					if (dir == 0)
						random->map[i][j] = 'N';
					if (dir == 1)
						random->map[i][j] = 'S';
					if (dir == 2)
						random->map[i][j] = 'W';
					if (dir == 3)
						random->map[i][j] = 'E';
					player = 1;
				}
				else
				{
					random->map[i][j] = '0';
					percent = 1 + (100 - (100 * x_nbr_now / x_numb));
				}
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

void	map_display(t_rand *random)
{
	for (int i = 0; i < random->size; i++)
		ft_printf(1, "\033[1A");
	for (int i = 0; i < random->size; i++)
	{
		ft_printf(1, "%s\n", random->map[i]);
		usleep(50000);
	}
}

int	random_map_generator(t_rand *random)
{
	for (int i = 0; i < random->size; i++)
		ft_printf(1, "\n");
	map_display(random);
	random_map_generator_space(random);
	map_display(random);
	map_generator_wall(random);
	map_display(random);
	random_map_generator_wall(random);
	map_display(random);
	player_gen(random);
	map_display(random);
	return (TRUE);
}

int	create_map(t_rand *random)
{
	random->name = ft_strjoin("map_code:", ft_create_map_name(random, 10));
	random->size = ft_rand(random, 15, 30);
	random->fd = open(random->name, O_CREAT, 777, O_TRUNC);
	if (random->fd == -1)
		return (ft_printf(1, "Error\nOpen fd"),
			free(random->name), ERROR);
	if (create_map_alloc(random) == ERROR)
		return (ft_printf(1, "Error\nAllocation"), close(random->fd),
			free(random->name), ERROR);
	if (random_map_generator(random) == ERROR)
		return (ft_printf(1, "Error\nMap generator"), close(random->fd),
			free(random->name), ERROR);
	
	return (TRUE);
}

int	main(void)
{
	t_rand	random;
	
	random.random = time(NULL) % 2147483647;
	if (create_map(&random) == ERROR)
		return (ERROR);
	unlink(random.name);
	return (TRUE);
}