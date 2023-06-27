
# include "philo.h"

t_rules *init_rules(int ac, char **av);
void free_rules(t_rules *rules);

t_data *init_data(char **av);
void free_data(t_data *data);

t_philo *init_philo(int philo_num);
t_node *init_queue(int philo_num);