/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:13:02 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/04 22:20:42 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*c_s1;
	unsigned char	*c_s2;

	i = 0;
	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	while (c_s1[i] == c_s2[i] && c_s1[i] != '\0')
		i++;
	return (c_s1[i] - c_s2[i]);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char *s1;
// 	char *s2;
// 	s1 = "tgj";
// 	s2 = "134";
// 	// printf("origin   %d\n", ft_strncmp(s1, s2));
// 	printf("strcmp   %d\n", strcmp(s1, s2));
// 	return (0);
// }