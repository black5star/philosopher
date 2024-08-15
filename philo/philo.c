/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:46:16 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/14 19:41:56 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
    t_info data;

    check_args(ac, av, &data);
    ft_init(&data);
    // printf("pilo_ num : %d \n", data->philo_nb);
    // printf("time die : %d \n", data->time_die);
    // printf("time eat : %d \n", data->time_eat);
    // printf("tima slp : %d \n", data->time_slp);
    // printf("num of meal : %d \n", data->num_of_meal);
   
}
