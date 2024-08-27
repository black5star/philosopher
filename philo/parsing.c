/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:30 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/27 16:48:30 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if ((result > 2147483647))
			ft_exit("you passed int_max limit");
		i++;
	}
	if (str[i] == '+')
		ft_exit("error in atoi");
	return (result);
}

void	invalid_input(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] != ' ' && av[i][j] != '+'
				&& (av[i][j] < '0' || av[i][j] > '9'))
				ft_exit("invalid input");
			j++;
		}
		i++;
	}
}

void	check_args(int ac, char **av, t_main *data)
{
	if (ac != 5 && ac != 6)
		ft_exit("args are more or less than required");
	invalid_input(ac, av);
	data->philo_nb = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_slp = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->max_meals = ft_atoi(av[5]);
		if (!data->max_meals)
			exit(EXIT_SUCCESS);
	}
	else
		data->max_meals = -1;
}
