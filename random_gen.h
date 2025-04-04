/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_gen.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:10:12 by jdhallen          #+#    #+#             */
/*   Updated: 2025/04/04 13:41:44 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_GEN_H
# define RANDOM_GEN_H

# include "Libft/ft_libft/ft_libft.h"
# include "Libft/ft_printf/ft_printf.h"
# include "Libft/get_next_line/get_next_line.h"
# include <stdbool.h>
# include <math.h>
# include <time.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef ERROR
#  define ERROR -1
# endif


typedef struct s_rand
{
	char	**map;
	char	*name;
	int		fd;
	int		random;
	int		random_utils;
	int		size;
	int		test;
}	t_rand;

#endif