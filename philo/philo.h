#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_table
{
	int				id;
	int				philos;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				must_eat;
	int				philos_done;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat;
	pthread_mutex_t	done;
	long int		start_t;
	int				exit;

}	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_t		thread_die;
	pthread_mutex_t	*right;
	pthread_mutex_t	left;
	unsigned int	peaten;
	int				finish;
	long int		meaten;
	t_table			*index;

}	t_philo;
typedef struct s_list
{
	t_philo	*data;
	t_table	tab;
}	t_list;

long	ft_atoi(char *str);
int		isnum(char **str, int i, int j);
void	ft_usleep(long int duration);
long	current_time(void);
int		ft_exit(char *str);
int		ft_death(t_philo *ph, int i);
int		ft_death2(t_list *ph);
void	init_mutex(t_list *p);
void	ft_stop(t_list *ph);

void	*philosopher_thread(void *arg);
int		initialize_philosophers(t_list *ph);


#endif