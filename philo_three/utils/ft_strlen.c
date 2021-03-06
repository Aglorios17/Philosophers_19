/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:36:10 by aglorios          #+#    #+#             */
/*   Updated: 2020/03/04 13:04:22 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

size_t	ft_strlen(const char *str)
{
	unsigned int a;

	a = 0;
	if (str == NULL)
		return (0);
	while (str[a] != '\0')
		a++;
	return (a);
}
