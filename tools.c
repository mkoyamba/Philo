/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:30:58 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/28 11:43:01 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	all_free(t_data *data)
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
}

void	error_out(char *str, t_data *data, int philo, pthread_mutex_t	*wait)
{
	if (wait)
		pthread_mutex_lock(wait);
	data->stop = 1;
	all_free(data);
	if (philo == 0)
	{
		write(2, "philo: ", 7);
		write(2, str, ft_strlen(str));
	}
	else
		printf("Le philosophe %i est mort.\n", philo - 1);
	exit(0);
}
