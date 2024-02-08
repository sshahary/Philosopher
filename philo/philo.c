#include "philo.h"

static int	initialize(t_list *ph)
{
	int	i;

	i = 0;
	ph->tab.start_t = current_time();
	ph->tab.exit = 0;
	ph->tab.philos_done = 0;
	init_mutex(ph);
	while (i < ph->tab.philos)
	{
		ph->data[i].id = i + 1;
		ph->data[i].meaten = ph->tab.start_t;
		ph->data[i].peaten = 0;
		ph->data[i].finish = 0;
		ph->data[i].right = NULL;
		pthread_mutex_init(&ph->data[i].left, NULL);
		if (ph->tab.philos == 1)
			return (1);
		if (i == ph->tab.philos - 1)
			ph->data[i].right = &ph->data[0].left;
		else
			ph->data[i].right = &ph->data[i + 1].left;
		i++;
	}
	return (1);
}

int	initialize_philosophers(t_list *ph)
{
	int	i;

	i = 0;
	while (i < ph->tab.philos)
	{
		ph->data[i].index = &ph->tab;
		if (pthread_create(&ph->data[i].thread, \
			NULL, philosopher_thread, &ph->data[i]) != 0)
		{
			return (ft_exit("Pthread did not return 0\n"));
		}
		i++;
	}
	return (1);
}

int	main(int ac, char *argv[])
{
	t_list	ph;

	if (!(philo_validation(ac, argv, &ph)))
	{
		return (ft_exit("Invalid Output\n"), EXIT_FAILURE);
	}
	ph.data = malloc(ph.tab.philos * sizeof(t_philo));
	if (!ph.data)
		return (ft_exit("Malloc returned NULL\n"));
	if (!(initialize(&ph)) || !(initialize_philosophers(&ph)))
	{
		free(ph.data);
		return (0);
	}
	ft_stop(&ph);
}