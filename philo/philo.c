/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:37 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/26 12:11:20 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    turn_and_check(t_philo *philo, int time)
{
    pthread_mutex_lock(&philo->data->monitor_mtx);
    if(time > philo->data->time_die)
        philo->data->death_flag = 1;
    pthread_mutex_unlock(&philo->data->monitor_mtx);
    return ;
}

void    *monitor(void *p)
{
    t_main *data;
    t_philo philo;
    int i;

    data = (t_main *)p;
    i = -1;
    while(++i <= data->philo_nb)
    {
        philo = data->philo[i];
        if(data->full == data->philo_nb)
            break ;
        turn_and_check(&philo, time_out(&philo));
        if(get_value(&philo.data->monitor_mtx, &philo.data->death_flag))
        {
            write_message(&philo, DIED);
            break ;
        }
        if(i == data->philo_nb - 1)
            i = -1;
    }
    ft_free(data, 0);
    return (NULL);
}

int main(int ac, char **av)
{
    t_main data;

    check_args(ac, av, &data);
    ft_init(&data);
    start_feeding(&data);
}
