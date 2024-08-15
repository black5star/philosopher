/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:46:31 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/14 20:01:09 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    invalid_input(int ac, char *av[])
{
    int i;
    int j;

    i = 1;
    while (i < ac)
    {
        j = 0;
        while(av[i][j])
        {
            if(av[i][j] != ' ' && av[i][j] != '+'
                && (av[i][j] < '0' || av[i][j] > '9'))
                ft_exit("invalid input");
            j++;
        }
        i++;
    }
}

void    check_args(int ac, char *av[], t_info *data)
{
    if(ac != 5 && ac != 6)
        ft_exit("args are more or less than required");
    invalid_input(ac, av);
    data->philo_nb = ft_atoi(av[1]);
    data->time_die = ft_atoi(av[2]);
    data->time_eat = ft_atoi(av[3]);
    data->time_slp = ft_atoi(av[4]);
    if(ac == 6)
        data->max_meals = ft_atoi(av[5]);
    else
        data->max_meals = -1;
    if(data->philo_nb <=0 || data->philo_nb > 200
        || data->time_die < 60 || data->time_eat < 60
        || data->time_slp < 60)
        ft_exit("invalid numbers");
    data->time_die *= 1000;
    data->time_eat *= 1000;
    data->time_slp *= 1000;
}
