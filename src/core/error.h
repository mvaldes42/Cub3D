/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 10:48:26 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/11 13:10:31 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ERROR_H
# define __ERROR_H

typedef enum	e_error
{
	E_UNK_ERROR = 0,
	E_NOT_ENOUGH_ARG = 1,
	E_UNK_ARG = 2,
	E_LST_MAP = 3,
	E_INV_FILE_SYNT = 4,
	E_RBG_SYNT = 5,
	E_MAP_N_CLS = 6,
	E_MAP_I_CHAR = 7,
	E_MLX = 8,
	E_TEXT_MLX = 9,
	E_MAL = 10,
	E_RES = 11,
	E_MAP_G = 12,
	E_MAP_POS = 13,
}				t_error;

typedef struct	s_errordesc
{
	int		code;
	char	*msg;
}				t_errordesc;

static const	t_errordesc g_errorm[] =
{
	{E_UNK_ERROR, "Unknown error."},
	{E_NOT_ENOUGH_ARG, "Not enough arguments in scene.cub file."},
	{E_UNK_ARG, "Unknown argument in scene.cub file."},
	{E_LST_MAP, "Could not create map linked list."},
	{E_INV_FILE_SYNT, "Invalid texture file synthax."},
	{E_RBG_SYNT, "Invalid RGB synthax."},
	{E_MAP_N_CLS, "Invalid map (map not closed)."},
	{E_MAP_I_CHAR, "Invalid map (invalid character)."},
	{E_MLX, "MLX init error"},
	{E_TEXT_MLX, "XPM textures could not be loaded"},
	{E_MAL, "Malloc error"},
	{E_RES, "Invalid screen resolution"},
	{E_MAP_G, "Empty line in map"},
	{E_MAP_POS, "Invalid map (invalid player position)."},
};

// int	g_error;

void		exit_message_failure(int error);

#endif
