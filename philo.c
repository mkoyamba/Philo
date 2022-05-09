/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:15:14 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/05/02 16:17:09 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	mutex parole

void	died(t_access *access)
{
	pthread_mutex_lock(access->end);
	print_msg(access, MSG_DIED);
	all_free((t_data *)access->data, access->speak, access->end);
}

static int	sleeping(t_access *access, int *hunger)
{
	locker(access);
	print_msg(access, MSG_SLEEP);
	usleep(access->t_sleep * M);
	locker(access);
	if (hungry(access, hunger))
		return (0);
	return (1);
}

static int	eating(t_access *access, int *hunger)
{
	locker(access);
	print_msg(access, MSG_THINK);
	if (access->num % 2 == 0)
		pthread_mutex_lock(access->fork_0);
	if (access->num % 2 == 1)
		pthread_mutex_lock(access->fork_1);
	locker(access);
	if (hungry(access, hunger))
		return (0);
	print_msg(access, MSG_FORK);
	if (access->num % 2 == 0)
		pthread_mutex_lock(access->fork_1);
	if (access->num % 2 == 1)
		pthread_mutex_lock(access->fork_0);
	locker(access);
	if (hungry(access, hunger))
		return (0);
	print_msg(access, MSG_FORK);
	print_msg(access, MSG_EAT);
	usleep(access->t_eat * M);
	locker(access);
	*hunger = timestamp(access);
	pthread_mutex_unlock(access->fork_0);
	pthread_mutex_unlock(access->fork_1);
	return (1);
}

static void	*philo_loop(void *arg)
{
	int				hunger;
	t_access		*access;

	access = (t_access *)arg;
	hunger = timestamp(access);
	if (((t_data *)access->data)->len == 1)
	{
		print_msg(access, MSG_FORK);
		usleep(access->t_die * M);
		died(access);
	}
	while (1)
	{
		if (hungry(access, &hunger))
			return (0);
		if (!eating(access, &hunger))
			return (0);
		if (!sleeping(access, &hunger))
			return (0);
	}
	return (0);
}

void	philo(t_data *data)
{
	int				n;
	pthread_mutex_t	speak;
	pthread_mutex_t	end;

	pthread_mutex_init(&speak, NULL);
	pthread_mutex_init(&end, NULL);
	n = 0;
	while (n < data->len)
	{
		data->access[n].speak = &speak;
		data->access[n].end = &end;
		pthread_mutex_init(data->mutex[n], NULL);
		pthread_create(data->thread[n], NULL, philo_loop, &(data->access[n]));
		n++;
	}
	while (data->stop == 0)
		usleep(10);
}
