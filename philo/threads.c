#include "philo.h"

static void	ft_printf(char *str, t_philo *ph)
{
	long	time;

	time = -1;
	time = current_time() - ph->index->start_t;
	if (time >= 0 && time <= 2147483647 && !ft_death(ph, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", ph->id, str);
	}
}

static void	ft_sleept(t_philo *philos)
{
	pthread_mutex_lock(&philos->index->print);
	ft_printf("is sleeping\n", philos);
	pthread_mutex_unlock(&philos->index->print);
	ft_usleep(philos->index->time_sleep);
	pthread_mutex_lock(&philos->index->print);
	ft_printf("is thinking\n", philos);
	pthread_mutex_unlock(&philos->index->print);
}

static void	dining_philosophers(t_philo *philos)
{
	pthread_mutex_lock(&philos->left);
	pthread_mutex_lock(&philos->index->print);
	ft_printf("has taken a fork\n", philos);
	pthread_mutex_unlock(&philos->index->print);
	if (!philos->right)
	{
		ft_usleep(philos->index->time_die * 2);
		return ;
	}
	pthread_mutex_lock(philos->right);
	pthread_mutex_lock(&philos->index->print);
	ft_printf("has taken a fork\n", philos);
	pthread_mutex_unlock(&philos->index->print);
	pthread_mutex_lock(&philos->index->print);
	ft_printf("is eating\n", philos);
	pthread_mutex_lock(&philos->index->eat);
	philos->meaten = current_time();
	pthread_mutex_unlock(&philos->index->eat);
	pthread_mutex_unlock(&philos->index->print);
	ft_usleep(philos->index->time_eat);
	pthread_mutex_unlock(philos->right);
	pthread_mutex_unlock(&philos->left);
	ft_sleept(philos);
}

static void	*dead_thread(void	*arg)
{
	t_philo					*philos;

	philos = (t_philo *)arg;
	ft_usleep(philos->index->time_die + 1);
	pthread_mutex_lock(&philos->index->eat);
	pthread_mutex_lock(&philos->index->done);
	if (!ft_death(philos, 0) && !philos->finish && ((current_time() - \
		philos->meaten) >= (long)(philos->index->time_die)))
	{
		pthread_mutex_unlock(&philos->index->eat);
		pthread_mutex_unlock(&philos->index->done);
		pthread_mutex_lock(&philos->index->print);
		ft_printf("died\n", philos);
		pthread_mutex_unlock(&philos->index->print);
		ft_death(philos, 1);
	}
	pthread_mutex_unlock(&philos->index->eat);
	pthread_mutex_unlock(&philos->index->done);
	return (NULL);
}

void	*philosopher_thread(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->id % 2 == 0)
		ft_usleep(philos->index->time_eat / 10);
	while (!(ft_death(philos, 0)))
	{
		pthread_create(&philos->thread_die, NULL, dead_thread, arg);
		dining_philosophers(philos);
		pthread_detach(philos->thread_die);
		if ((int)++philos->peaten == philos->index->must_eat)
		{
			pthread_mutex_lock(&philos->index->done);
			philos->finish = 1;
			philos->index->philos_done++;
			if (philos->index->philos_done == philos->index->philos)
			{
				pthread_mutex_unlock(&philos->index->done);
				ft_death(philos, 2);
			}
			pthread_mutex_unlock(&philos->index->done);
			return (NULL);
		}
	}
	return (NULL);
}
