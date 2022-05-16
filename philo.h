/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:23:10 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/05/10 13:40:54 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*  		==================(     INCLUDES     )==================		  */

# include <unistd.h>
# include <stddef.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

/*  		==================(      MACROS      )==================		  */

# define E_ALLOC "Problème d'allocation de mémoire.\n"
# define E_ARG "Arguments incorrects.\n"
# define E_FORK "Problème de fork.\n"

# define MSG_FORK 1
# define MSG_EAT 2
# define MSG_SLEEP 3
# define MSG_THINK 4
# define MSG_DIED 5

# define STR_FORK "has taken a fork\n"
# define STR_EAT "is eating\n"
# define STR_SLEEP "is sleeping\n"
# define STR_THINK "is thinking\n"
# define STR_DIED "died\n"

# define M 1000

/*  		==================(    STRUCTURES    )==================		  */

typedef struct s_access
{
	int				num;
	int				t_eat;
	int				t_sleep;
	int				*meal;
	int				*last_eat;
	void			*data;
	int				start_time;
	pthread_mutex_t	*fork_0;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*speak;
}			t_access;

typedef struct s_data
{
	int				start_time;
	int				len;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_must;
	int				*hunger_count;
	int				*number_meal;
	pthread_t		**thread;
	pthread_mutex_t	**mutex;
	t_access		*access;
}			t_data;

/*  		==================(    PROTOTYPES    )==================		  */

void	error_out(char *str, t_data *data);
void	init(t_data *data);
void	philo(t_data *data, pthread_mutex_t	*speak);
size_t	ft_strlen(char *str);
int		ft_atoi(char *str);
int		timestamp(t_access *access);
void	ft_putnbr(int n);
void	print_msg(t_access *access, int msg);
void	died(t_access *access);
void	all_free(t_data *data);

#endif