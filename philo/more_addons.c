/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_addons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:14:07 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/24 14:42:53 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(
				pthread_mutex_t *speak, pthread_mutex_t *nb_meal_mute,
				pthread_mutex_t *death_check_mute)
{
	pthread_mutex_destroy(speak);
	pthread_mutex_destroy(nb_meal_mute);
	pthread_mutex_destroy(death_check_mute);
}

void	add_all_free(t_data *data)
{
	int	n;

	n = 0;
	while (n < data->len)
	{
		pthread_mutex_destroy(data->mutex[n]);
		if (data->mutex[n])
			free(data->mutex[n]);
		if (data->thread[n])
			free(data->thread[n]);
		n++;
	}
	if (data->mutex)
		free(data->mutex);
	if (data->thread)
		free(data->thread);
	if (data->access)
		free(data->access);
}

void	add_main(t_data *data, pthread_mutex_t *speak,
					pthread_mutex_t *nb_meal_mute,
					pthread_mutex_t *death_check_mute)
{
	data->hunger_count = malloc(data->len * sizeof(int));
	if (!data->hunger_count)
	{
		destroy_mutexes(speak, nb_meal_mute, death_check_mute);
		error_start(E_ALLOC, data->thread, data->mutex);
	}
	data->number_meal = malloc(data->len * sizeof(int));
	if (!data->number_meal)
	{
		destroy_mutexes(speak, nb_meal_mute, death_check_mute);
		free(data->hunger_count);
		error_start(E_ALLOC, data->thread, data->mutex);
	}
	data->access = malloc(data->len * sizeof(t_access));
	if (!data->access)
	{
		destroy_mutexes(speak, nb_meal_mute, death_check_mute);
		free(data->hunger_count);
		free(data->number_meal);
		error_start(E_ALLOC, data->thread, data->mutex);
	}
}
