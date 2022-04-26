/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:34:07 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/26 14:28:07 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *test_un(void *arg)
{
	(void)arg;
	int	n;

	n = 0;
	pthread_mutex_lock(arg);
	while (n < 10)
	{
		printf("UN	: %i\n", n);
		usleep(500000);
		n++;
	}
	pthread_mutex_unlock(arg);
	return (NULL);
}

void *test_deux(void *arg)
{
	(void)arg;
	int	n;

	n = 0;
	pthread_mutex_lock(arg);
	while (n < 10)
	{
		printf("DEUX	: %i\n", n);
		usleep(500000);
		n++;
	}
	pthread_mutex_unlock(arg);
	return (NULL);
}

void *test_trois(void *arg)
{
	(void)arg;
	int	n;

	n = 0;
	pthread_mutex_lock(arg);
	while (n < 10)
	{
		printf("TROIS	: %i\n", n);
		usleep(500000);
		n++;
	}
	pthread_mutex_unlock(arg);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_un;
	pthread_t	thread_deux;
	pthread_t	thread_trois;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread_un, NULL, test_un, &mutex);
	pthread_create(&thread_deux, NULL, test_deux, &mutex);
	pthread_create(&thread_trois, NULL, test_trois, &mutex);
	usleep(15000000);
	pthread_mutex_destroy(&mutex);
	return (0);
}