/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:24:01 by blackstar         #+#    #+#             */
/*   Updated: 2024/08/14 19:10:44 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ini_philos(t_info *data)
{
    int i;
    
    i = -1;
    while(++i < data->philo_nb)
    {
        data->philo->id = i + 1;
        
    }
}

void ft_init(t_info *data)
{
    int i;
    
    data->philo = malloc(sizeof(t_philo) * data->philo_nb);
    data->thread = malloc(sizeof(pthread_t) * data->philo_nb);
    data->forks = malloc(sizeof(t_forks) * data->philo_nb);
    data->lock = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
    i = -1;
    while(++i < data->philo_nb)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        pthread_mutex_init(&data->lock[i], NULL);
    }
    pthread_mutex_init(&data->message, NULL);
    init_philos(data);
}
