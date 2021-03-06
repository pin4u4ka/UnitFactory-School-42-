/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing_field.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:28:00 by rbozhko           #+#    #+#             */
/*   Updated: 2017/03/22 14:34:46 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fdf_drawing_pxl(t_env *e, int x, int y)
{
	if ((x < WIDTH && x >= 0) && (y < HEIGHT && y >= 0))
	{
		e->str[(4 * x + y * e->sl)] = 249;
		e->str[(4 * x + y * e->sl + 1)] = 188;
		e->str[(4 * x + y * e->sl + 2)] = 216;
	}
}


void				fdf_bresenheim(t_brezenheim *b, t_pnt *pnt1, t_env *e)
{
    b->x = (int)pnt1->x;
    b->y = (int)pnt1->y;
    b->del_x = abs((int)b->l_pnt->x - b->x);
    b->del_y = abs((int)b->l_pnt->y - b->y);
    b->sign_x = b->x < (int)b->l_pnt->x ? 1 : -1;
    b->sign_y = b->y < (int)b->l_pnt->y ? 1 : -1;
    b->error = b->del_x - b->del_y;
    while (b->x != (int)b->l_pnt->x || b->y != (int)b->l_pnt->y)
    {
        b->error2 = b->error * 2;
        if (b->error2 > -b->del_y)
        {
            b->error -= b->del_y;
            b->x += b->sign_x;
        }
        if (b->error2 < b->del_x)
        {
            b->error += b->del_x;
            b->y += b->sign_y;
        }
        b->temp_pnt.x = b->x;
        b->temp_pnt.y = b->y;
        fdf_drawing_pxl(e, b->x, b->y);
    }
    fdf_drawing_pxl(e, b->x, b->y);
}

void				fdf_drawing_field(t_env *e, int x, int y, t_brezenheim *b)
{
    t_pnt				pnt;

    (e->img_ptr) ? mlx_destroy_image(e->mlx_ptr, e->img_ptr) : 0;
    e->img_ptr = mlx_new_image(e->mlx_ptr, HEIGHT, WIDTH);
    e->str = mlx_get_data_addr(e->img_ptr, &e->bpp, &e->sl, &e->endian);
    fdf_img_to_centre(e);
    while (++y < e->ylen && (x = -1))
    {
        while (++x < e->xlen)
        {
            pnt = *(e->field_ptr[y][x]);
            b->color = (int)pnt.color;
            if (x + 1 < e->xlen)
            {
                b->l_pnt = (e->field_ptr[y][x + 1]) ? e->field_ptr[y][x + 1] : 0;
                (e->field_ptr[y][x + 1]) ? fdf_bresenheim(b, &pnt, e) : 0;
            }
            if (y + 1 < e->ylen)
            {
                b->l_pnt = (e->field_ptr[y + 1][x]) ? e->field_ptr[y + 1][x] : 0;
                (e->field_ptr[y + 1][x]) ? fdf_bresenheim(b, &pnt, e) : 0;
            }
        }
    }
    mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
}
