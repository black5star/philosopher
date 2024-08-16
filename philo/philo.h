/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:46:37 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/16 12:01:08 by hboustaj         ###   ########.fr       */
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

typedef struct s_info t_info;

typedef struct s_philo
{
    int id; // index from 0
    int meals_count; // init with 0
    long last_meal_time; // following time_line
    t_info *data; // init with data
    t_forks *left_fork; // init
    t_forks *right_fork; // init
    pthread_mutex_t *message_to_write; 
} t_philo;

typedef struct s_forks
{
    pthread_mutex_t fork;
    int fork_id;
}   t_forks;

struct s_info
{
    int philo_nb; //av[1]
    int time_die; // av[2]
    int time_eat; // av[3]
    int time_slp; // av[4]
    int max_meals; // av[5]
    long start_time; // gettimeof()
    bool end_time; // time_now - start_time
    pthread_t thread; // malloc
    t_philo *philo; //malloc and go to struct
    t_forks *forks; // malloc and go to struct
    pthread_mutex_t *lock; // malloc and init
    pthread_mutex_t message; // init
};

void    invalid_input(int ac, char *av[]);
void    check_args(int ac, char *av[], t_info *data);
int     ft_atoi(const char	*str);
void    ft_init(t_info *data);
void    ft_exit(char *s);
long    time_now();

#endif