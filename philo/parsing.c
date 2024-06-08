/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:46:31 by hboustaj          #+#    #+#             */
/*   Updated: 2024/06/07 15:34:28 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    invalid_input(int ac, char *av[], t_info *data)
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
                ft_exit(data);
            j++;
        }
        i++;
    }
}

void    check_args(int ac, char *av[], t_info *data)
{
    if(ac != 5 && ac != 6)
        ft_exit(data);
    invalid_input(ac, av, data);
    data->philo_nb = ft_atoi(av[1], data);
    data->time_die = ft_atoi(av[2], data);
    data->time_eat = ft_atoi(av[3], data);
    data->time_slp = ft_atoi(av[4], data);
    if(ac == 6)
        data->num_of_meal = ft_atoi(av[5], data);
    else
        data->num_of_meal = -1;
    if(data->philo_nb <=0 || data->philo_nb > 200
        || data->time_die == 0 || data->time_eat == 0
        || data->time_slp == 0)
        ft_exit(data);
    
}
