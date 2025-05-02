#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

# define BUFFER_SIZE 42

typedef struct s_number
{
	int	nord;
	int	south;
	int	west;
	int	east;
	int	roof;
	int	floor;
}		t_number;

typedef struct s_img
{
	t_number	num;
	char		*nord;
	char		*south;
	char		*west;
	char		*east;
	char		**roof;
	char		**floor;
}				t_img;

typedef struct s_data
{
	t_img	img;
	char	**map;
}			t_data;

//GET_NEXT_LINE
size_t	ft_strlen_c(char *str, char c);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_line(char *str);
char	*ft_read(int fd, char *buffer, char *str);
void	ft_buffer(char *buffer, char *str);
char	*get_next_line(int fd);

//STR_UTILS
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_bzero(void *s, size_t n);

//FT_SPLIT
char	**ft_split(char const *s, char c);

#endif