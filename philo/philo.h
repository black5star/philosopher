/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:46:37 by hboustaj          #+#    #+#             */
/*   Updated: 2024/06/05 00:06:43 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    int id;
} t_philo;

typedef struct s_info
{
    int philo_nb;
    int time_die;
    int time_eat;
    int time_slp;
    int num_of_meal;
    t_philo philo;
} t_info;

void    invalid_input(int ac, char *av[]);
void    check_args(int ac, char *av[], t_info *data);
int     ft_atoi(const char	*str, int *arr);

#endif