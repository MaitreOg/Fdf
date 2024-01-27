/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:41:05 by smarty            #+#    #+#             */
/*   Updated: 2024/01/27 18:03:17 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	***check_tab(char ***tab, int i, int y)
{
	int	z;
	char *truevalue;
	
	i = -1;
	printf("%s\n", tab[0][0]);
	while(tab[++i])
	{
		y = -1;
		while(tab[i][++y])
		{
			z = -1;
			while (tab[i][y][++z])
			{
				if (tab[i][y][z] == ',')
				{
					z = 0;
					while (tab[i][y][z] != ',')
						z++;
					truevalue = malloc(z);
					z = -1;
					while(tab[i][y][++z] != ',')
						truevalue[z] = tab[i][y][z];
					truevalue[z] = 0;
					free(tab[i][y]);
					tab[i][y] = ft_strdup(truevalue);
				}
			}
		}
	}
	printf("%s\n", tab[1][1]);
	return(tab);
}

//if (fd == -1)
//		return (-1);

// manque gestion d erreur
