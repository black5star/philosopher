/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:24:01 by blackstar         #+#    #+#             */
/*   Updated: 2024/08/17 14:39:24 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_forks(t_forks *fork, t_philo *philo, int i)
{
    int philo_nb;

    philo_nb = philo->data->philo_nb;
    if(philo->id % 2)
        usleep(5);
    philo->right_fork = &fork[i];
    philo->left_fork = &fork[(i + 1) % philo_nb];
}

void    ini_philos(t_info *data)
{
    int i;
    t_philo *philo;
    
    i = -1;
    while(++i < data->philo_nb)
    {
        philo = data->philo + i;
        philo->id = i + 1;
        philo->data = data;
        philo->meals_count = 0;
        init_forks(data->forks, philo, i);
    }
}

void ft_init(t_info *data)
{
    int i;
    
    data->philo = malloc(sizeof(t_philo) * data->philo_nb);
    data->forks = malloc(sizeof(t_forks) * data->philo_nb);
    i = -1;
    while(++i < data->philo_nb)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->forks[i].fork_id = i;
    }
    pthread_mutex_init(&data->message, NULL);
    init_philos(data);
}
