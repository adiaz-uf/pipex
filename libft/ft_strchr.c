/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:25:27 by adiaz-uf          #+#    #+#             */
/*   Updated: 2023/04/23 21:12:48 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It returns a pointer to the first occurrence
 * of the character c in the string s
 * 
 * @param s The string to be searched.
 * @param c The character to be located.
 * 
 * @return A pointer to the first occurrence
 * of the character c in the string s.
 */
char	*ft_strchr(const char *s, int c)
{
	char	aux;
	char	*str;
	int		i;

	aux = (char)c;
	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == aux)
			return (&str[i]);
		else
			i++;
	}
	if (aux == '\0')
		return (&str[i]);
	else
		return (0);
}
