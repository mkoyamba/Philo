/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:45:12 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/26 18:52:33 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	mutex_create(t_data *data)
{
	pthread_t	*result;

	result = malloc(sizeof(pthread_mutex_t));
	{
		if (!result)
			error_out(E_ALLOC, data);
	}
	return (result);
}

static pthread_t	thread_create(t_data *data)
{
	pthread_t	*result;

	result = malloc(sizeof(pthread_t));
	{
		if (!result)
			error_out(E_ALLOC, data);
	}
	return (result);
}

void	init(t_data *data)
{
	size_t	n;

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
		data->access[n].num = n;
		data->access[n].fork_0 = data->mutex[n];
		if (n < data->len - 1)
			data->access[n].fork_1 = data->mutex[n + 1];
		else
			data->access[n].fork_1 = data->mutex[0];
		n++;
	}
}
