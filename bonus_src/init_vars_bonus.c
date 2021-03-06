#include "../include/so_long_bonus.h"

int	cnt_map_width(t_vars *vars)
{
	int	x;
	int	y;
	int	width;

	y = 0;
	width = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while (vars->map[y][x])
			x++;
		if (width == 0)
			width = x;
		else if (width != x)
		{
			ft_putstr_fd("Error\n", STDERR_FILENO);
			ft_putstr_fd("The map is not rectangular.\n", STDERR_FILENO);
			vars->exit_status = EXIT_FAILURE;
			destroy_and_exit(vars);
		}
		y++;
	}
	return (width);
}

void	set_player_image(t_vars *vars)
{
	int	x;
	int	y;

	vars->img.player_img[FRONT][ACTION1] = \
		mlx_xpm_file_to_image(vars->mlx, P_FRONT1, &x, &y);
	vars->img.player_img[FRONT][ACTION2] = \
		mlx_xpm_file_to_image(vars->mlx, P_FRONT2, &x, &y);
	vars->img.player_img[LEFT][ACTION1] = \
		mlx_xpm_file_to_image(vars->mlx, P_LEFT1, &x, &y);
	vars->img.player_img[LEFT][ACTION2] = \
		mlx_xpm_file_to_image(vars->mlx, P_LEFT2, &x, &y);
	vars->img.player_img[RIGHT][ACTION1] = \
		mlx_xpm_file_to_image(vars->mlx, P_RIGHT1, &x, &y);
	vars->img.player_img[RIGHT][ACTION2] = \
		mlx_xpm_file_to_image(vars->mlx, P_RIGHT2, &x, &y);
	vars->img.player_img[BACK][ACTION1] = \
		mlx_xpm_file_to_image(vars->mlx, P_BACK1, &x, &y);
	vars->img.player_img[BACK][ACTION2] = \
		mlx_xpm_file_to_image(vars->mlx, P_BACK2, &x, &y);
}

void	set_image(t_vars *vars)
{
	int	x;
	int	y;

	set_player_image(vars);
	vars->img.tile_img = mlx_xpm_file_to_image(vars->mlx, TILE, &x, &y);
	vars->img.collectible_img = \
	mlx_xpm_file_to_image(vars->mlx, COLLECTIBLE, &x, &y);
	vars->img.wall_img = mlx_xpm_file_to_image(vars->mlx, WALL, &x, &y);
	vars->img.exit_img = mlx_xpm_file_to_image(vars->mlx, EXIT, &x, &y);
	vars->img.gray_img = mlx_xpm_file_to_image(vars->mlx, GRAY, &x, &y);
	vars->img.p_exit = mlx_xpm_file_to_image(vars->mlx, P_EXIT, &x, &y);
}

bool	check_allocate(t_vars *vars)
{
	if (!vars->mlx || !vars->mlx_win || !vars->img.p_exit
		|| !vars->img.tile_img || !vars->img.collectible_img
		|| !vars->img.wall_img || !vars->img.exit_img
		|| !vars->img.player_img[FRONT][ACTION1]
		|| !vars->img.player_img[FRONT][ACTION2]
		|| !vars->img.player_img[LEFT][ACTION1]
		|| !vars->img.player_img[LEFT][ACTION2]
		|| !vars->img.player_img[RIGHT][ACTION1]
		|| !vars->img.player_img[RIGHT][ACTION2]
		|| !vars->img.player_img[BACK][ACTION1]
		|| !vars->img.player_img[BACK][ACTION2])
		return (true);
	else
		return (false);
}

void	init_vars(t_vars *vars)
{
	vars->err = false;
	vars->map_width = cnt_map_width(vars);
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, vars->map_width * TILE_SIZE,
			vars->map_height * TILE_SIZE + 20, "so_long");
	set_image(vars);
	if (check_allocate(vars))
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	vars->collectible = 0;
	vars->collected = 0;
	vars->step_cnt = 0;
	vars->exit_status = EXIT_SUCCESS;
	vars->direction = FRONT;
	vars->action = ACTION1;
	vars->end = false;
}
