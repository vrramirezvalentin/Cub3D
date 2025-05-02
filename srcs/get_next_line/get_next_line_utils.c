#include "cub3d.h"

size_t	ft_strlen_c(char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	i;

	i = c;
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && i == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	size_t			i;
	unsigned char	*str;

	if (size != 0 && count * size / size != count)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	str = (unsigned char *)ptr;
	while (i < count * size)
	{
		str[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len + 1)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
