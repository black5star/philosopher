/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:46:37 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/15 11:23:20 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
    int id;
    int nb_meals;
    long time_of_lm;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    pthread_mutex_t *message_to_write;
} t_philo;

typedef struct s_forks
{
    pthread_mutex_t *fork;
    int fork_id;
}   t_forks;

typedef struct s_info
{
    int philo_nb;
    int time_die;
    int time_eat;
    int time_slp;
    int max_meals;
    long start_time;
    bool end_time;
    pthread_t thread;
    t_philo *philo;
    t_forks *forks;
    pthread_mutex_t *lock;
    pthread_mutex_t message;
} t_info;

void    invalid_input(int ac, char *av[]);
void    check_args(int ac, char *av[], t_info *data);
int     ft_atoi(const char	*str);
void    ft_exit(char *s);
void    convert_to_ms(t_info *data);
#endif