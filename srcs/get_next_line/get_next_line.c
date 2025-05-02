#include "cub3d.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	str = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

char	*ft_line(char *str)
{
	char	*line;
	size_t	i;

	line = ft_calloc(sizeof(char), (ft_strlen_c(str, '\n') + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *buffer, char *str)
{
	ssize_t	ret;
	char	*tmp;

	ret = 1;
	while (!ft_strchr(str, '\n') && ret != 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			buffer[0] = '\0';
			return (free(str), NULL);
		}
		if (ret == 0 && str[0] == '\0')
			return (free(str), NULL);
		buffer[ret] = 0;
		tmp = str;
		str = ft_strjoin(str, buffer);
		if (!str)
			return (NULL);
		free(tmp);
	}
	return (str);
}

void	ft_buffer(char *buffer, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	j = 0;
	while (str[i])
	{
		buffer[j] = str[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_strdup(buffer);
	if (!str)
		return (NULL);
	str = ft_read(fd, buffer, str);
	if (!str)
		return (NULL);
	line = ft_line(str);
	if (!line)
		return (NULL);
	ft_buffer(buffer, str);
	return (free(str), line);
}
