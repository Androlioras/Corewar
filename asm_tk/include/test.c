#include "../include/user.h"

t_utils		*ft_init_struct()
{
	t_utils *utils;
	utils = malloc(sizeof(t_utils));
	utils->label = NULL;
	utils->verif = 0;
	utils->oct = 0;
	utils->next = NULL;
}

int	main(int argc, char **argv)
{
	t_utils *utils;
	utils = ft_init_struct();
	return (0);	
}