/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:47:08 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 15:43:33 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

static char	*ft_vide(void)
{
	char	*vide;

	if ((vide = malloc(sizeof(char) * 1)) != NULL)
	{
		vide[0] = '\0';
		return (vide);
	}
	return (NULL);
}

static char	*ft_strcpy(char *dest, char const *src)
{
	int a;

	a = 0;
	while (src[a] != '\0')
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

static char	*ft_strcat(char *dest, char const *src)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0')
	{
		dest[a + b] = src[b];
		b++;
	}
	dest[a + b] = '\0';
	return (dest);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char *s3;

	s3 = 0;
	if (s1 == NULL || s2 == NULL)
		return (ft_vide());
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (s3 == 0)
		return (0);
	ft_strcpy(s3, s1);
	ft_strcat(s3, s2);
	return (s3);
}
