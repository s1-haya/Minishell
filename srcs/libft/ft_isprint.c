/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:10:06 by tterao            #+#    #+#             */
/*   Updated: 2023/01/10 16:10:08 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int s)
{
	if (s >= 32 && s <= 126)
		return (1);
	else
		return (0);
}
