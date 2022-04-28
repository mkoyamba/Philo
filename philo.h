/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:23:10 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/28 11:31:53 by mkoyamba         ###   ########.fr       */
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
# define M 1000

/*  		==================(    STRUCTURES    )==================		  */

typedef struct s_access
{
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_must;
	void			*data;
	int				num;
	pthread_mutex_t	*fork_0;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*wait;
	int				*stop;
}			t_access;

typedef struct s_data
{
	int				stop;
	int				len;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_must;
	pthread_t		**thread;
	pthread_mutex_t	**mutex;
	t_access		*access;
}			t_data;

/*  		==================(    PROTOTYPES    )==================		  */

void	error_out(char *str, t_data *data, int philo, pthread_mutex_t	*wait);
void	init(t_data *data);
void	philo(t_data *data);
size_t	ft_strlen(char *str);
int		ft_atoi(char *str);

#endif