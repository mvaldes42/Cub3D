/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:33:13 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/10 15:59:54 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	sort_sprites_desc(t_scene *s, double *dist, int amount)
{
	int		i;
	int		j;
	int		tmp;
	t_point	tmp_pos;

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

static void	draw_sprt_pxl(t_env *env, t_scene *s, t_sprite *sp, int x)
{
	int y;

	sp->textr.x = (int)(256 *
	(x - (-sp->dim.x / 2 + sp->s_scrn_x)) * 64 / sp->dim.x) / 256;
	if (sp->trsfrm.y > 0 && x > 0 && x < s->scrn.x
	&& sp->trsfrm.y < env->scene.cam.z_buffer[x])
	{
		y = sp->start.y;
		while (++y < sp->end.y)
		{
			sp->d = y * 256 - s->scrn.y * 128 + sp->dim.y * 128;
			sp->textr.y = ((sp->d * s->tex[4].h) / sp->dim.y) / 256;
			sp->clr = ((int*)s->tex[4].img.data)
			[(int)(sp->textr.y * s->tex[4].w + sp->textr.x)];
			if ((sp->clr & 0x00FFFFFF) != 0)
				draw_pixel(env, x, y, sp->clr);
		}
	}
}

static void	calc_sprt_vrbls(t_scene *s, t_sprite *sp, int i)
{
	int		w;
	int		h;
	double	inv_det;

	w = s->scrn.x;
	h = s->scrn.y;
	sp->r_pos.x = s->sprt.pos[i].x - s->plyr.pos.x;
	sp->r_pos.y = s->sprt.pos[i].y - s->plyr.pos.y;
	inv_det = 1.0 /
	(s->cam.pln.x * s->plyr.dir.y - s->plyr.dir.x * s->cam.pln.y);
	sp->trsfrm.x = inv_det
	* (s->plyr.dir.y * sp->r_pos.x - s->plyr.dir.x * sp->r_pos.y);
	sp->trsfrm.y = inv_det
	* (-s->cam.pln.y * sp->r_pos.x + s->cam.pln.x * sp->r_pos.y);
	sp->s_scrn_x = (int)((w / 2) * (1 + sp->trsfrm.x / sp->trsfrm.y));
	sp->dim.y = abs((int)(h / sp->trsfrm.y));
	sp->start.y = (-sp->dim.y / 2 + h / 2) < 0 ? 0 : -sp->dim.y / 2 + h / 2;
	sp->end.y = (sp->dim.y / 2 + h / 2) >= h ? h - 1 : sp->dim.y / 2 + h / 2;
	sp->dim.x = abs((int)(h / sp->trsfrm.y));
	sp->start.x = (-sp->dim.x / 2 + sp->s_scrn_x) < 0 ?
	0 : -sp->dim.x / 2 + sp->s_scrn_x;
	sp->end.x = (sp->dim.x / 2 + sp->s_scrn_x) >= w ?
	w - 1 : sp->dim.x / 2 + sp->s_scrn_x;
}

void		draw_sprites(t_scene *s, t_env *env, t_sprite *sp)
{
	int i;
	int x;

	sp->dst = malloc(sp->nbr * sizeof(double));
	i = -1;
	while (++i < s->sprt.nbr)
		sp->dst[i] = ((s->plyr.pos.x - s->sprt.pos[i].x)
		* (s->plyr.pos.x - s->sprt.pos[i].x)
		+ (s->plyr.pos.y - s->sprt.pos[i].y)
		* (s->plyr.pos.y - s->sprt.pos[i].y));
	sort_sprites_desc(s, sp->dst, sp->nbr);
	i = -1;
	while (++i < sp->nbr)
	{
		calc_sprt_vrbls(s, sp, i);
		x = sp->start.x - 1;
		while (++x < sp->end.x)
			draw_sprt_pxl(env, s, sp, x);
	}
}
