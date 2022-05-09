/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:45:12 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/05/02 16:17:39 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*mutex_create(t_data *data)
{
	pthread_mutex_t	*result;

	result = malloc(sizeof(pthread_mutex_t));
	if (!result)
		error_out(E_ALLOC, data);
	return (result);
}

static pthread_t	*thread_create(t_data *data)
{
	pthread_t	*result;

	result = malloc(sizeof(pthread_t));
	{
		if (!result)
			error_out(E_ALLOC, data);
	}
	return (result);
}

static void	init_loop(t_data *data)
{
	int	n;

	n = 0;
	while (n < data->len)
	{
		data->thread[n] = thread_create(data);
		data->mutex[n] = mutex_create(data);
		n++;
	}
	n = 0;
	while (n < data->len)
	{
	//	data->access[n].stop = &data->stop;
		data->access[n].t_die = data->t_die;
		data->access[n].t_eat = data->t_eat;
		data->access[n].t_sleep = data->t_sleep;
		data->access[n].t_must = data->t_must;
		data->access[n].data = data;
		data->access[n].num = n + 1;
		data->access[n].fork_0 = data->mutex[n];
		if (n < data->len - 1)
			data->access[n].fork_1 = data->mutex[n + 1];
		n++;
	}
	data->access[data->len - 1].fork_1 = data->mutex[0];
}

void	init(t_data *data)
{
	int				n;
	struct timeval	start;

	init_loop(data);
	gettimeofday(&start, NULL);
	n = 0;
	while (n < data->len)
	{
		data->access[n].start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
		n++;
	}
}