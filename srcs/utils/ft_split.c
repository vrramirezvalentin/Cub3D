#include "cub3d.h"

static void	ft_free_tab(char **strs, int i)
{
	while(i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

static int	count_words(char const *s, char c)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return(count);
}

static char	*copy_word(char const *s, int start, int end)
{
	int i;
	char *word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if(!word)
		return NULL;
	while(start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	**fill_strs(char const *s, char c, char **strs) {
	int k;
	int i;
	int j;

	j = 0;
	i = 0;
		while(s[i])
		{
			if(s[i] != c)
			{
				k = i;
				while(s[i] != c && s[i] != '\0')
					i++;
				strs[j] = copy_word(s,k,i);
				if(!strs[j])
					return (ft_free_tab(strs, j), NULL);
				j++;
			}else
				i++;
		}
		strs[j] = NULL;
		return(strs);
}

char	**ft_split(char const *s, char c)
{
	char **strs;

	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (count_words(s,c)+1));
	if(!strs)
		return NULL;
	
	strs = fill_strs(s,c,strs);
	return (strs);

}