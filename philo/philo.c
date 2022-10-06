/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:15:14 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/06 12:00:01 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_data *data)
{
	int	n;

	n = 0;
	pthread_mutex_lock(data->death_check_mute);
	while (n < data->len)
	{
		if (timestamp(&data->access[n]) - data->hunger_count[n] >= data->t_die)
			return (n + 1);
		n++;
	}
	pthread_mutex_unlock(data->death_check_mute);
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
		pthread_mutex_lock(data->nb_meal_mute);
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
		pthread_mutex_unlock(data->nb_meal_mute);
		time_tempo_data(1, timestamp_data(data), data);
	}
}

static int	eating(t_access *access, int mode)
{
	if (!mode)
	{
		if (pthread_mutex_lock(access->fork_0))
			return (0);
		if (pthread_mutex_lock(access->fork_1))
		{
			pthread_mutex_unlock(access->fork_0);
			return (0);
		}
		print_msg(access, MSG_FORK);
		print_msg(access, MSG_FORK);
	}
	else
	{
		if (pthread_mutex_lock(access->fork_1))
			return (0);
		if (pthread_mutex_lock(access->fork_0))
		{
			pthread_mutex_unlock(access->fork_1);
			return (0);
		}
		print_msg(access, MSG_FORK);
		print_msg(access, MSG_FORK);
	}
	return (eat_end(access));
}

static void	*philo_loop(void *arg)
{
	t_access	*access;

	access = (t_access *)arg;
	while (1)
	{
		while (!eating(access, 0))
		{
			if (eating(access, 1))
				break ;
		}
		print_msg(access, MSG_SLEEP);
		time_tempo(access->t_sleep, timestamp(access), access);
		print_msg(access, MSG_THINK);
	}
	return (NULL);
}

void	philo(t_data *data, pthread_mutex_t	*speak,
			pthread_mutex_t	*nb_meal_mute, pthread_mutex_t	*death_check_mute)
{
	int	n;

	n = 0;
	data->start_time = first_timestamp();
	while (n < data->len)
	{
		data->access[n].start_time = data->start_time;
		data->access[n].speak = speak;
		data->access[n].nb_meal_mute = nb_meal_mute;
		data->access[n].death_check_mute = death_check_mute;
		pthread_mutex_init(data->mutex[n], NULL);
		pthread_create(data->thread[n], NULL, philo_loop, &data->access[n]);
		n++;
	}
	data->nb_meal_mute = nb_meal_mute;
	data->death_check_mute = death_check_mute;
	n = check_state(data);
	if (n)
	{
		print_msg(&(data->access[n - 1]), MSG_DIED);
		all_free(data);
	}
	else
	{
		pthread_mutex_lock(speak);
		all_free(data);
		write(1, "All philosophers have eaten enough\n", 35);
	}
}
