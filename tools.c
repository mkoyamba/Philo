/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:30:58 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/27 17:46:39 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_out(char *str, t_data *data, int philo)
{
	int	n;

	n = 0;
	if (philo == -1)
		usleep(1000000);
	printf("%i\n", philo);
	data->stop = 1;
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
	if (philo == 0)
	{
		write(2, "philo: ", 7);
		write(2, str, ft_strlen(str));
	}
	else
		printf("Le philosophe %i est mort.\n", philo - 1);
	exit(0);
}
