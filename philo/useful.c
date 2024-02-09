#include "philo.c"

long	ft_atoi(char *str)
{
	long	r;
	long	i;
	int		s;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * s);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	isnum(char **str, int i, int j)
{
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] < '0' || str[i][j] > '9' || (ft_strlen(str[i]) > 10))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

long	current_time(void)
{
	struct timeval	tv;
	long int		time;

	if (gettimeofday(&tv, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (time);
}

void	ft_usleep(long int duration)
{
	long int	i;

	i = current_time();
	while ((current_time() - i) < duration)
		usleep(duration / 10);
}
