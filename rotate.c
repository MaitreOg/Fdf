/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:25:19 by smarty            #+#    #+#             */
/*   Updated: 2024/01/23 15:56:47 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    rotate_x (t_point *point, double corner, double center_y)
{
    double  y;
    double  z;

    point->y -= center_y;
    y = (point->y * cos(corner)) - (point->z * sin(corner));
    z = (point->y * sin(corner)) + (point->z * cos(corner));
    point->y = y + center_y;
    point->z = z;

}
void    rotate_y (t_point *point, double corner, double center_x)
{
    double  x;
    double  z;

    point->x -= center_x;
    x = (point->z * sin(corner)) + (point->x * cos(corner));
    z = (point->z * cos(corner)) - (point->x * sin(corner));
    point->x = x + center_x;
    point->z = z;
}

void rotate_z(t_point *point, double corner, double center_x, double center_y)
{
    double  x;
    double  y;

    point->x -= center_x;
    point->y -= center_y;
    x = (point->x * cos(corner)) - (point->y * sin(corner));
    y = (point->x * sin(corner)) + (point->y * cos(corner));
    // Translation pour ramener le point à sa position d'origine
    point->x = x + center_x;
    point->y = y + center_y;
}

void apply_corner(t_data *map, int axe, double corner)
{
    int i;

    i = 0;
    if (axe == 3)
    {
        while (map->len >= i)
        {
            rotate_z(&map->map[i], corner, map->lenstruct / 2, map->nbrline / 2);
            i++;
        }
    }
    if (axe == 2)
    {
        while (map->len >= i)
        {
            rotate_y(&map->map[i], corner, map->lenstruct / 2);
            i++;
        }
    }
    if (axe == 1)
    {
        while (map->len >= i)
        {
            rotate_x(&map->map[i], corner, map->nbrline / 2);
            i++;
        } 
    }

}
