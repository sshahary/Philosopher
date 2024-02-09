#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

int	ft_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->index->dead);
	if (i)
		ph->index->exit = i;
	if (ph->index->exit)
	{
		pthread_mutex_unlock(&ph->index->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->index->dead);
	return (0);
}

void	init_mutex(t_list *p)
{
	if (pthread_mutex_init(&p->tab.print, NULL) != 0
		|| pthread_mutex_init(&p->tab.dead, NULL) != 0
		|| pthread_mutex_init(&p->tab.eat, NULL) != 0
		|| pthread_mutex_init(&p->tab.done, NULL) != 0)
		ft_exit("Mutex initialization failed\n");
}

int	ft_death2(t_list *ph)
{
	pthread_mutex_lock(&ph->tab.dead);
	if (ph->tab.exit)
	{
		pthread_mutex_unlock(&ph->tab.dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->tab.dead);
	return (0);
}
