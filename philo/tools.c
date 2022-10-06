/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:30:58 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/06 11:58:31 by mkoyamba         ###   ########.fr       */
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

void	all_free(t_data *data)
{
	int	n;

	usleep((data->t_eat + data->t_sleep) * M);
	free(data->hunger_count);
	free(data->number_meal);
	n = 0;
	while (n < data->len)
	{
		pthread_mutex_destroy(data->mutex[n]);
		free(data->mutex[n]);
		free(data->thread[n]);
		n++;
	}
	free(data->mutex);
	free(data->thread);
	free(data->access);
	return ;
}

void	error_out(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	all_free(data);
}
