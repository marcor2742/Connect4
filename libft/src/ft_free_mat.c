/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:25:24 by redei-ma          #+#    #+#             */
/*   Updated: 2025/06/25 13:00:48 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_free_mat(void **mat, int size)
{
	int	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (mat[i])
		{
			free(mat[i]);
			mat[i] = NULL;
		}
		i++;
	}
	free(mat);
	return (NULL);
}
