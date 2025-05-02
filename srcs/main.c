#include "cub3d.h"

void	ft_free(char *content)
{
	free(content);
	content = NULL;
}

void clear_tab(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

bool ft_extension(char *file, char *extension)
{
	char	*dot;
	int		len_ext;

	dot = strrchr(file, '.');
	if (!dot)
	{
		write(2, "Error : No extension found.\n", 28);
		return (false);
	}

	len_ext = ft_strlen(extension);
	if (ft_strncmp(dot, extension, len_ext) != 0)
	{
		write(2, "Error : Wrong extension.\n", 26);
		return (false);
	}

	return (true);
}

int	count_line(char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error"), -1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

void	ft_clean(t_data	*data)
{
	if (data->img.east)
		ft_free(data->img.east);
	if (data->img.nord)
		ft_free(data->img.nord);
	if (data->img.south)
		ft_free(data->img.south);
	if (data->img.west)
		ft_free(data->img.west);
	if (data->img.roof)
		clear_tab(data->img.roof);
	if (data->img.floor)
		clear_tab(data->img.floor);
	if (data->map)
		clear_tab(data->map);
	ft_bzero(data, sizeof(t_data));
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
	c == '\v' || c == '\f' || c == '\r');
}

bool	verif_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

// bool verif_FC()

int	parsing(char *file, t_data *data)
{
	int		fd;
	char	**content;
	char	*line;
	int		i;
	
	(void)data;
	i = count_line(file);
	if (i == -1)
		return (EXIT_FAILURE);
	content = malloc(sizeof(char *) * (i + 1));
	if (!content)
		return (perror("Error"), EXIT_FAILURE);

	fd = open(file, O_RDONLY);
	if (fd == -1) 
		return (perror("Error"), EXIT_FAILURE);

	i = 0;
	line = get_next_line(fd);
	while(line)
	{
		content[i] = line;
		line = get_next_line(fd);
		i++;
	}
	content[i] = NULL; 
	
	i = 0;
	while(content[i]) 
	{
		if (ft_strncmp(content[i], "NO ", 3) == 0)
			data->img.num.nord++;
		else if (ft_strncmp(content[i], "SO ", 3) == 0)
			data->img.num.south++;
		else if (ft_strncmp(content[i], "WE ", 3) == 0)
			data->img.num.west++;
		else if (ft_strncmp(content[i], "EA ", 3) == 0)
			data->img.num.east++;
		else if (ft_strncmp(content[i], "C ", 2) == 0)
			data->img.num.roof++;
		else if (ft_strncmp(content[i], "F ", 2) == 0)
			data->img.num.floor++;
		i++;
	}
	if (data->img.num.nord != 1 || data->img.num.south != 1 || data->img.num.west != 1 || data->img.num.east != 1 || data->img.num.roof != 1 || data->img.num.floor != 1)
	{
		write(2, "Error : Wrong number of textures.\n", 35);
		return (clear_tab(content), close(fd), EXIT_FAILURE);
	}

	int	count = 0;
	i = 0;
	while (content[i] && count < 6)
	{
		while (ft_strncmp(content[i], "NO ", 3) != 0 &&
			ft_strncmp(content[i], "SO ", 3) != 0 &&
			ft_strncmp(content[i], "WE ", 3) != 0 &&
			ft_strncmp(content[i], "EA ", 3) != 0 &&
			ft_strncmp(content[i], "C ", 2) != 0 &&
			ft_strncmp(content[i], "F ", 2) != 0)
		{
			if (verif_line(content[i]) == false)
			{
				write(2, "Error : Line empty is not empty.\n", 34);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			i++;
		}
		if (ft_strncmp(content[i], "NO ", 3) == 0)
		{
			data->img.nord = ft_substr(content[i], 3, ft_strlen(content[i]) - 4); 
			if (!data->img.nord)
			{
				write(2, "Error : malloc failed.\n", 24);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			count++;
		}
		else if (ft_strncmp(content[i], "SO ", 3) == 0)
		{
			data->img.south = ft_substr(content[i], 3, ft_strlen(content[i]) - 4);
			if (!data->img.south)
			{
				write(2, "Error : malloc failed.\n", 24);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			count++;
		}
		else if (ft_strncmp(content[i], "WE ", 3) == 0)
		{
			data->img.west = ft_substr(content[i], 3, ft_strlen(content[i]) - 4);
			if (!data->img.west)
			{
				write(2, "Error : malloc failed.\n", 24);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			count++;
		}
		else if (ft_strncmp(content[i], "EA ", 3) == 0)
		{
			data->img.east = ft_substr(content[i], 3, ft_strlen(content[i]) - 4);
			if (!data->img.east)
			{
				write(2, "Error : malloc failed.\n", 24);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			count++;
		}
		else if (ft_strncmp(content[i], "C ", 2) == 0) 
		{
			data->img.roof = ft_split(&content[i][2], ',');
            if (!data->img.roof)
			{
				write(2, "Error : malloc failed.\n", 24);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			char *tmp = data->img.roof[2];
			data->img.roof[2] = ft_substr(data->img.floor[2], 0, ft_strlen(data->img.roof[2]) - 1);
			if(!data->img.roof)
			{
				write(2, "Error : malloc failed.\n", 24);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			free(tmp);
            
			count++;
		}
		else if (ft_strncmp(content[i], "F ", 2) == 0) 
		{
			data->img.floor = ft_split(&content[i][2], ','); 
			if(!data->img.floor)
			{
				write(2, "Error : malloc failed.\n", 24);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			char *tmp = data->img.floor[2];
			data->img.floor[2] = ft_substr(data->img.floor[2], 0, ft_strlen(data->img.floor[2]) - 1);
			if(!data->img.floor)
			{
				write(2, "Error : malloc failed.\n", 24);
				ft_clean(data);
				return (clear_tab(content), close(fd), EXIT_FAILURE);
			}
			free(tmp);
			count++;
		}
		i++;
	}
	if (!ft_extension(data->img.east, ".xpm") || !ft_extension(data->img.west, ".xpm") || !ft_extension(data->img.nord, ".xpm") || !ft_extension(data->img.south, ".xpm"))
	{
		ft_clean(data);
		return (clear_tab(content), close(fd), EXIT_FAILURE);
	}
	int	y = 0;
	int is_valid = 1;
	while (content[i])
	{
		while (content[i][y])
		{
			if (!is_whitespace(content[i][y]) && content[i][y] != '1' && content[i][y] != '0' && content[i][y] != 'N' && content[i][y] != 'S' && content[i][y] != 'E' && content[i][y] != 'W')
			{
				is_valid = 0;
				break ;
			}
			y++;
		}
		if (!is_valid)
		{
			write(2, "Error: Unexpected character before the map.\n", 44);
			ft_clean(data);
			return (clear_tab(content), close(fd), EXIT_FAILURE);
		}
		if (ft_strchr(content[i], '1') || ft_strchr(content[i], '0') ||
			ft_strchr(content[i], 'N') || ft_strchr(content[i], 'S') ||
			ft_strchr(content[i], 'E') || ft_strchr(content[i], 'W'))
		{
			break;
		}
		i++;
	}
	int mapHeight = 0;
	int z = i;
	while (content[z])
	{
		mapHeight++;
		z++;
	}
	data->map = malloc(sizeof(char *) * (mapHeight + 1));
	if(!data->map)
	{
		write(2, "Error: Map Malloc failed.\n", 27);
		ft_clean(data);
		return (clear_tab(content), close(fd), EXIT_FAILURE);
	}
	y = 0;
	int	a = 0;
	while(content[i])
	{
		a = 0;
		while (content[i][a])
		{
			if (content[i][a] == ' ')
				content[i][a] = '1';
			a++;
		}
		data->map[y] = ft_strdup(content[i]);
		y++;
		i++;
	}
	data->map[y] = NULL;
	return (clear_tab(content), close(fd), EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
	{
		write(2, "Error : Wrong number of argument(s).\n", 38);
		return (EXIT_FAILURE);
	}
	if (!ft_extension(argv[1], ".cub"))
		return (EXIT_FAILURE);
	if (parsing(argv[1], &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("NORD = %s\n", data.img.nord);
	printf("SUD = %s\n", data.img.south);
	printf("OUEST = %s\n", data.img.west);
	printf("EST = %s\n", data.img.east);
	int i = 0;
	while(data.img.roof[i])
	{
		printf("C = %s\n", data.img.roof[i]);
		i++;
	}
	i = 0;
	while(data.img.floor[i])
	{
		printf("F = %s\n", data.img.floor[i]);
		i++;
	}
	i = 0;
	while(data.map[i])
	{
		printf("%s", data.map[i]);
		i++;
	}
	ft_clean(&data);
	return (EXIT_SUCCESS);
}
