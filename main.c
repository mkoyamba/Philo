/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:34:07 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/26 19:21:25 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_start(char *str, pthread_t **thread)
{
	if (thread)
		free(thread);
	write(2, "philo: ", 7);
	write(2, str, ft_strlen(str));
	exit(1);
}

static char	first_char(char *str)
{
	size_t	n;

	n = 0;
	while (str[n] == ' ' || str[n] == '\t' || str[n] == '\n'
		|| str[n] == '\r' || str[n] == '\v' || str[n] == '\f')
		n++;
	if (str[n] == '+' || str[n] == '-')
		n++;
	return (str[n]);
}

static int	check(int ac, char **av)
{
	size_t	n;
	int		ck;

	n = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (n < ac)
	{
		ck = ft_atoi(av[n]);
		if (ck == 0 && first_char(av[n]) != '0')
			return (0);
		n++;
	}
	return (1);
}

static void	alloc_init(t_data *data, int ac, char **av)
{
	size_t	n;

	n = 0;
	if (!check(ac, av))
		error_start(E_ARG, NULL);
	data->len = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->t_must = -1;
	if (ac == 6)
		data->t_must = ft_atoi(av[5]);
	data->thread = malloc(data->len * sizeof(pthread_t *));
	if (!data->thread)
		error_start(E_ALLOC, NULL);
	data->mutex = malloc(data->len * sizeof(pthread_mutex_t *));
	if (!data->mutex)
		error_start(E_ALLOC, data->thread);
	while (n < data->len)
	{
		data->thread[n] = NULL;
		data->mutex[n] = NULL;
		n++;
	}
}

int	main(int argc, char **argv)
{
/*	pthread_t	thread_un;
	pthread_t	thread_deux;
	pthread_t	thread_trois;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread_un, NULL, test_un, &mutex);
	pthread_create(&thread_deux, NULL, test_deux, &mutex);
	pthread_create(&thread_trois, NULL, test_trois, &mutex);
	usleep(15000000);
	pthread_mutex_destroy(&mutex);
*/
	t_data	data;

	alloc_init(&data, argc, argv);
	init(&data);
	return (0);
}