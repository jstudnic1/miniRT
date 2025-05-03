/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deploy_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:51:28 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 16:45:54 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <pthread.h>
#include <unistd.h>

/**
 * @brief Creates state mutexes and debug print mutex
 * 
 * @param data 
 * @return int 
 */
int	create_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_THREADS)
	{
		pthread_mutex_init(&data->cores[i].state_mtx, NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	return (0);
}

/**
 * @brief Dummy function that will be used as a template for the computation
 *        function
 * 
 * @param core 
 * @return void* 
 */
void	*dummy_function(t_core *core)
{
	while (true)
	{
		pthread_mutex_lock(&core->state_mtx);
		if (core->state == core_run)
		{
			pthread_mutex_lock(core->print);
			printf("Hello from thread %i!\n", core->id);
			pthread_mutex_unlock(core->print);
		}
		else if (core->state == core_finish)
		{
			pthread_mutex_unlock(&core->state_mtx);
			break ;
		}
		pthread_mutex_unlock(&core->state_mtx);
		usleep(100000);
	}
	return (NULL);
}

/**
 * @brief Initializes data for the particular threads,
 starting and ending pixel coordinates computed by the number of
 threads
 TODO compute different intervals for different threads
 * 
 * @param data - main data struct
 */
void	init_cores_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_THREADS)
	{
		data->cores[i].id = i;
		data->cores[i].tid = 0;
		data->cores[i].x_start = 0;
		data->cores[i].x_end = 0;
		data->cores[i].y_start = 0;
		data->cores[i].y_end = 0;
		data->cores[i].print = &data->print;
		data->cores[i].state = core_stop;
		i++;
	}
}

/**
 * @brief Changes the state of all running threads
 * 
 * @param data - main data struct
 * @param new_state - new state of the threads
 */
void	change_cores_state(t_data *data, t_e_core_state new_state)
{
	int	i;

	i = 0;
	while (i < N_THREADS)
	{
		pthread_mutex_lock(&data->cores[i].state_mtx);
		data->cores[i].state = new_state;
		pthread_mutex_unlock(&data->cores[i].state_mtx);
		i++;
	}
}

/**
 * @brief Creates thread specific mutexes, inits thread data structure
 and creates the threads themselves
 * 
 * @param data - main data struct
 * @return int - 0 OK, -1 - NOK
 */
int	deploy_threads(t_data *data)
{
	int	i;

	i = 0;
	create_mutexes(data);
	init_cores_data(data);
	while (i < N_THREADS)
	{
		pthread_create(&data->cores[i].tid, NULL,
			(void *)&dummy_function, &data->cores[i]);
		i++;
	}
	return (0);
}
