/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:30:58 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/24 14:24:25 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_tempo_data(int timeout, int time_stamp, t_data *data)
{
	while (timestamp_data(data) < time_stamp + timeout)
		usleep(100);
}

int	timestamp_data(t_data *data)
{
	int				result;
	struct timeval	time;

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000 + time.tv_usec / 1000) - data->start_time;
	return (result);
}

void	all_free(t_data *data, pthread_mutex_t	*speak)
{
	int	n;

	n = 0;
	pthread_mutex_lock(data->nb_meal_mute);
	while (n < data->len)
	{
		data->stop[n] = 1;
		n++;
	}
	pthread_mutex_unlock(data->nb_meal_mute);
	pthread_mutex_unlock(speak);
	n = 0;
	while (n < data->len)
	{
		pthread_join(*(data->thread[n]), NULL);
		n++;
	}
	if (data->hunger_count)
		free(data->hunger_count);
	if (data->number_meal)
		free(data->number_meal);
	if (data->stop)
		free(data->stop);
	add_all_free(data);
}

void	error_out(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	all_free(data, NULL);
}
