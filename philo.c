/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:15:14 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/05/10 12:23:23 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_data *data)
{
	int	n;

	n = 0;
	while (n < data->len)
	{
		if (timestamp(&data->access[n]) - data->hunger_count[n] >= data->t_die)
			return (n + 1);
		n++;
	}
	return (0);
}

static int	check_state(t_data *data)
{
	int	n;

	while (1)
	{
		n = is_dead(data);
		if (n)
			return (n);
		if (data->t_must > 0)
		{
			while (n < data->len)
			{
				if (data->number_meal[n] < data->t_must)
				{
					n = -1;
					break ;
				}
				n++;
			}
			if (n != -1)
				return (0);
		}
	}
}

static void	eating(t_access *access)
{
	if (access->num % 2 == 0)
		pthread_mutex_lock(access->fork_0);
	else
		pthread_mutex_lock(access->fork_1);
	print_msg(access, MSG_FORK);
	if (access->num % 2 == 0)
		pthread_mutex_lock(access->fork_1);
	else
		pthread_mutex_lock(access->fork_0);
	print_msg(access, MSG_FORK);
	print_msg(access, MSG_EAT);
	*(access->last_eat) = timestamp(access);
	usleep(access->t_eat * M);
	*(access->last_eat) = timestamp(access);
	pthread_mutex_unlock(access->fork_0);
	pthread_mutex_unlock(access->fork_1);
	*(access->meal) += 1;
}

static void	*philo_loop(void *arg)
{
	t_access	*access;

	access = (t_access *)arg;
	while (1)
	{
		eating(access);
		print_msg(access, MSG_SLEEP);
		usleep(access->t_sleep * M);
		print_msg(access, MSG_THINK);
	}
	return (NULL);
}

void	philo(t_data *data)
{
	int				n;
	pthread_mutex_t	speak;

	pthread_mutex_init(&speak, NULL);
	n = 0;
	while (n < data->len)
	{
		data->access[n].speak = &speak;
		pthread_mutex_init(data->mutex[n], NULL);
		pthread_create(data->thread[n], NULL, philo_loop, &data->access[n]);
		n++;
	}
	n = check_state(data);
	if (n)
	{
		print_msg(&(data->access[n - 1]), MSG_DIED);
		pthread_mutex_destroy(&speak);
		all_free(data);
	}
	else
	{
		pthread_mutex_lock(&speak);
		write(1, "All philosophers have eaten enough\n", 35);
		all_free(data);
	}
}
