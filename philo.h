/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:23:10 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/26 19:18:47 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*  		==================(     INCLUDES     )==================		  */

# include <unistd.h>
# include <stddef.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

/*  		==================(      MACROS      )==================		  */

# define E_ALLOC "Problème d'allocation de mémoire."
# define E_ARG "Arguments incorrects."

/*  		==================(    PROTOTYPES    )==================		  */

void	error_out(char *str, t_data *data);
void	init(t_data *data);
void	philo(t_data *data);
size_t	ft_strlen(char *str);
int		ft_atoi(const char *str);

/*  		==================(    STRUCTURES    )==================		  */

typedef struct s_access
{
	size_t	num;
	pthread_mutex_t	*fork_0;
	pthread_mutex_t	*fork_1;
	
}			t_access;

typedef struct s_data
{
	int				len;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_must;
	pthread_t		**thread;
	pthread_mutex_t	**mutex;
	t_access		*access;
}			t_data;

#endif