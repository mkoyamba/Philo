/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:21:04 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/24 14:27:31 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_init(t_data *data, int n)
{
	data->access[n].stop = &(data->stop[n]);
	data->stop[n] = 0;
	data->access[n].last_eat = &(data->hunger_count[n]);
	data->access[n].t_eat = data->t_eat;
	data->access[n].t_sleep = data->t_sleep;
	data->access[n].meal = &(data->number_meal[n]);
}

t_access	*add_philo_loop(void *arg)
{
	t_access	*access;

	access = (t_access *)arg;
	pthread_mutex_lock(access->start_mute);
	pthread_mutex_unlock(access->start_mute);
	if (access->num % 2)
		time_tempo(0.6 * access->t_eat, timestamp(access), access);
	return (access);
}

int	add_check_state(t_data *data, int n)
{
	while (n < data->len)
	{
		if (data->number_meal[n] == data->t_must)
			*(data->access[n].stop) = 1;
		if (data->number_meal[n] < data->t_must)
		{
			n = -1;
			break ;
		}
		n++;
	}
	return (n);
}

int	add_philo(t_data *data, pthread_mutex_t *nb_meal_mute,
				pthread_mutex_t *death_check_mute, pthread_mutex_t *start_mute)
{
	int	n;

	n = 0;
	data->start_time = first_timestamp();
	while (n < data->len)
	{
		data->access[n].start_time = data->start_time;
		n++;
	}
	data->nb_meal_mute = nb_meal_mute;
	data->death_check_mute = death_check_mute;
	pthread_mutex_unlock(start_mute);
	n = check_state(data);
	return (n);
}

void	add_philo_2(t_data *data, pthread_mutex_t *speak)
{
	all_free(data, speak);
	write(1, "All philosophers have eaten enough\n", 35);
}
