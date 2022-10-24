/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:15:14 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/24 14:43:30 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_data *data)
{
	int	n;
	int	result;

	n = 0;
	result = 0;
	while (n < data->len)
	{
		if (timestamp(&data->access[n]) - data->hunger_count[n] >= data->t_die)
		{
			result = n + 1;
			break ;
		}
		n++;
	}
	pthread_mutex_unlock(data->death_check_mute);
	return (result);
}

int	check_state(t_data *data)
{
	int	n;

	while (1)
	{
		pthread_mutex_lock(data->death_check_mute);
		n = is_dead(data);
		if (n)
			return (n);
		pthread_mutex_lock(data->nb_meal_mute);
		if (data->t_must > 0)
		{
			n = add_check_state(data, n);
			if (n != -1)
			{
				pthread_mutex_unlock(data->nb_meal_mute);
				return (0);
			}
		}
		pthread_mutex_unlock(data->nb_meal_mute);
		time_tempo_data(1, timestamp_data(data), data);
	}
}

static int	eating(t_access *access)
{
	pthread_mutex_lock(access->fork_0);
	print_msg(access, MSG_FORK);
	if (!access->fork_1)
		return (0);
	pthread_mutex_lock(access->fork_1);
	print_msg(access, MSG_FORK);
	return (eat_end(access));
}

static void	*philo_loop(void *arg)
{
	t_access	*access;

	access = add_philo_loop(arg);
	while (1)
	{
		if (!eating(access))
			return (NULL);
		pthread_mutex_lock(access->nb_meal_mute);
		if (*(access->stop))
		{
			pthread_mutex_unlock(access->nb_meal_mute);
			return (NULL);
		}
		pthread_mutex_unlock(access->nb_meal_mute);
		print_msg(access, MSG_SLEEP);
		time_tempo(access->t_sleep, timestamp(access), access);
		pthread_mutex_lock(access->nb_meal_mute);
		if (*(access->stop))
			pthread_mutex_unlock(access->nb_meal_mute);
		if (*(access->stop))
			return (NULL);
		pthread_mutex_unlock(access->nb_meal_mute);
		print_msg(access, MSG_THINK);
	}
	return (NULL);
}

void	philo(t_data *data, pthread_mutex_t	*speak,
			pthread_mutex_t	*nb_meal_mute, pthread_mutex_t	*death_check_mute)
{
	int				n;
	pthread_mutex_t	start_mute;

	pthread_mutex_init(&start_mute, NULL);
	pthread_mutex_lock(&start_mute);
	n = 0;
	while (n < data->len)
	{
		data->access[n].start_mute = &start_mute;
		data->access[n].speak = speak;
		data->access[n].nb_meal_mute = nb_meal_mute;
		data->access[n].death_check_mute = death_check_mute;
		pthread_mutex_init(data->mutex[n], NULL);
		pthread_create(data->thread[n], NULL, philo_loop, &data->access[n]);
		n++;
	}
	n = add_philo(data, nb_meal_mute, death_check_mute, &start_mute);
	if (n > 0)
	{
		print_msg(&(data->access[n - 1]), MSG_DIED);
		all_free(data, speak);
	}
	else
		add_philo_2(data, speak);
}
