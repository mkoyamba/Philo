/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:30:58 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/05/02 16:17:13 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_free(t_data *data, pthread_mutex_t	*speak, pthread_mutex_t	*end)
{
	int	n;

	n = 0;
	while (n < data->len)
	{
		if (data->thread[n])
			free(data->thread[n]);
		if (data->mutex[n])
			pthread_mutex_destroy(data->mutex[n]);
		n++;
	}
	if (data->thread)
		free(data->thread);
	if (data->mutex)
		free(data->mutex);
	if (data->access)
		free(data->access);
	if (speak)
		pthread_mutex_destroy(speak);
	if (end)
		pthread_mutex_destroy(end);
	data->stop = 1;
}

void	error_out(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	all_free(data, NULL, NULL);
}

