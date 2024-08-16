/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:24:01 by blackstar         #+#    #+#             */
/*   Updated: 2024/08/16 12:09:23 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    assign_forks(t_forks *fork, t_philo *philo, int i)
{
    
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
        assign_forks(data->forks, philo, i);
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
        pthread_mutex_init(&data->forks->fork, NULL);
        data->forks[i].fork_id = i;
    }
    pthread_mutex_init(&data->message, NULL);
    init_philos(data);
    // data->start_time = time_now();
}
