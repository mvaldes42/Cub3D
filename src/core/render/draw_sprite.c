/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:33:13 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/10 15:35:36 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	sort_sprites_desc(t_scene *s, double *dist, int amount)
{
	int i;
	int j;
	int tmp;
	t_point tmp_pos;

	i = 0;
	while (i < amount)
	{
		j = i + 1;
		while (j < s->sprt.nbr)
		{
			if (dist[i] < dist[j])
			{
				tmp = dist[i];
				tmp_pos = s->sprt.pos[i];
				s->sprt.pos[i] = s->sprt.pos[j];
				dist[i] = dist[j];
				s->sprt.pos[j] = tmp_pos;
				dist[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	draw_sprt_pxl(t_env *env, t_scene *s, t_sprite *sprt, int x)
{
	sprt->textr.x = (int)(256 * (x - (-sprt->dim.x / 2 + sprt->s_scrn_x)) * 64 / sprt->dim.x) / 256;
	if (sprt->trsfrm.y > 0 && x > 0 && x < s->scrn.x && sprt->trsfrm.y < env->scene.cam.z_buffer[x])
	{
		for (int y = sprt->start.y + 1; y < sprt->end.y; y++)
		{
			sprt->d = y * 256 - s->scrn.y * 128 + sprt->dim.y * 128;
			sprt->textr.y = ((sprt->d  * s->tex[4].h) / sprt->dim.y) / 256;
			sprt->clr = ((int *)s->tex[4].img.data)[(int)(sprt->textr.y * s->tex[4].w + sprt->textr.x)];
			if ((sprt->clr & 0x00FFFFFF) != 0)
				draw_pixel(env, x, y, sprt->clr);
		}
	}
}

static void	calc_sprt_vrbls(t_scene *s, t_sprite *sprt, int i)
{
	int w = s->scrn.x;
	int h = s->scrn.y;

	sprt->r_pos.x = s->sprt.pos[i].x - s->plyr.pos.x;
	sprt->r_pos.y = s->sprt.pos[i].y - s->plyr.pos.y;
	double inv_det = 1.0 / (s->cam.pln.x * s->plyr.dir.y - s->plyr.dir.x * s->cam.pln.y);
	sprt->trsfrm.x = inv_det * (s->plyr.dir.y * sprt->r_pos.x - s->plyr.dir.x * sprt->r_pos.y);
	sprt->trsfrm.y = inv_det * (-s->cam.pln.y * sprt->r_pos.x + s->cam.pln.x * sprt->r_pos.y);
	sprt->s_scrn_x = (int)((w / 2) * (1 + sprt->trsfrm.x / sprt->trsfrm.y));
	sprt->dim.y = abs((int)(h / (sprt->trsfrm.y)));
	sprt->start.y = (-sprt->dim.y / 2 + h / 2) < 0 ? 0 : -sprt->dim.y / 2 + h / 2;
	sprt->end.y = (sprt->dim.y / 2 + h / 2) >= h ? h - 1 : sprt->dim.y / 2 + h / 2;
	sprt->dim.x = abs( (int) (h / (sprt->trsfrm.y)));
	sprt->start.x = (-sprt->dim.x / 2 + sprt->s_scrn_x) < 0 ? 0 : -sprt->dim.x / 2 + sprt->s_scrn_x;
	sprt->end.x = (sprt->dim.x / 2 + sprt->s_scrn_x) >= w ? w - 1 : sprt->dim.x / 2 + sprt->s_scrn_x;
}

void		draw_sprites(t_scene *s, t_env *env, t_sprite *sprt)
{
	int i;
	int x;

	sprt->dst = malloc(sprt->nbr * sizeof(double));
	i = -1;
	while (++i < s->sprt.nbr)
		sprt->dst[i] =((s->plyr.pos.x - s->sprt.pos[i].x)
		* (s->plyr.pos.x - s->sprt.pos[i].x)
		+ (s->plyr.pos.y - s->sprt.pos[i].y)
		* (s->plyr.pos.y - s->sprt.pos[i].y));
	sort_sprites_desc(s, sprt->dst, sprt->nbr);
	i = -1;
	while (++i < sprt->nbr)
	{
		calc_sprt_vrbls(s, sprt, i);
		x = sprt->start.x - 1;
		while (++x < sprt->end.x)
			draw_sprt_pxl(env, s, sprt, x);
	}
}
