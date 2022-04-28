/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:15:14 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/28 19:32:18 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	hung_update(struct timeval *start, size_t *hungry)
{
	size_t			result;
	struct timeval	end;

	gettimeofday(&end, NULL);
	result = ((size_t)end.tv_usec / M) - ((size_t)start->tv_usec / M);
	start->tv_usec = end.tv_usec;
	*hungry += result;
}

static void	norminetted_un(t_access *access, int *stop, size_t *hungry,
	struct timeval *start)
{
	t_data			*data;

	data = (t_data *)access->data;
	if (*stop == 1)
		error_out(NULL, NULL, -1, access->wait);
	else if (*hungry >= (size_t)access->t_die)
		error_out(NULL, (t_data *)access->data, access->num + 1,
			access->wait);
	gettimeofday(start, NULL);
	if (access->num % 2 == 0)
		pthread_mutex_lock(access->fork_0);
	else
		pthread_mutex_lock(access->fork_1);
	if (*stop == 1)
		error_out(NULL, NULL, -1, access->wait);
	hung_update(start, hungry);
	printf("%03d %i has taken a fork\n", start->tv_usec / M, access->num);
	if (*stop == 1)
		error_out(NULL, NULL, -1, access->wait);
	else if (data->len == 1)
		error_out(NULL, (t_data *)access->data, access->num + 1,
			access->wait);
	else if (*hungry >= (size_t)access->t_die)
		error_out(NULL, (t_data *)access->data, access->num + 1,
			access->wait);
}

static void	norminetted_deux(t_access *access, int *stop, size_t *hungry,
	struct timeval *start)
{
	if (access->num % 2 == 0)
		pthread_mutex_lock(access->fork_1);
	else
		pthread_mutex_lock(access->fork_0);
	if (*stop == 1)
		error_out(NULL, NULL, -1, access->wait);
	hung_update(start, hungry);
	if (*stop == 1)
		error_out(NULL, NULL, -1, access->wait);
	else if (*hungry >= (size_t)access->t_die)
		error_out(NULL, (t_data *)access->data, access->num + 1,
			access->wait);
	printf("%03d %i has taken a fork\n", start->tv_usec / M, access->num);
	*hungry = 0;
	printf("%03d %i is eating\n", start->tv_usec / M, access->num);
	usleep(access->t_eat * M);
	if (*stop == 1)
		error_out(NULL, NULL, -1, access->wait);
	gettimeofday(start, NULL);
	printf("%03d %i is sleeping\n", start->tv_usec / M, access->num);
	if (*stop == 1)
		error_out(NULL, NULL, -1, access->wait);
}

static void	*philo_loop(void *arg)
{
	t_access		*access;
	struct timeval	start;
	size_t			hungry;
	int				*stop;
	t_data			*data;

	access = (t_access *)arg;
	stop = access->stop;
	data = (t_data *)access->data;
	hungry = 0;
	while (1)
	{
		norminetted_un(access, stop, &hungry, &start);
		norminetted_deux(access, stop, &hungry, &start);
		pthread_mutex_unlock(access->fork_0);
		if (*stop == 1)
			error_out(NULL, NULL, -1, access->wait);
		pthread_mutex_unlock(access->fork_1);
		usleep(access->t_sleep * M);
		if (*stop == 1)
			error_out(NULL, NULL, -1, access->wait);
		hung_update(&start, &hungry);
	}
	return (0);
}

void	philo(t_data *data)
{
	int				n;
	pthread_mutex_t	wait;

	pthread_mutex_init(&wait, NULL);
	n = 0;
	while (n < data->len)
	{
		data->access[n].wait = &wait;
		n++;
	}
	n = 0;
	while (n < data->len)
	{
		pthread_mutex_init(data->mutex[n], NULL);
		pthread_create(data->thread[n], NULL, philo_loop, &(data->access[n]));
		n++;
	}
	while (1)
	{
		if (data->stop == 1)
			break ;
		usleep(10);
	}
	pthread_mutex_destroy(&wait);
}
