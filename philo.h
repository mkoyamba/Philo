/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:23:10 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/26 14:31:52 by mkoyamba         ###   ########.fr       */
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

# define ERROR_ARG ""

/*  		==================(    PROTOTYPES    )==================		  */

/*  		==================(    STRUCTURES    )==================		  */

typedef struct s_data
{
	size_t	num;
	pthread_mutex_t	mutex;
	
}			t_data;

#endif