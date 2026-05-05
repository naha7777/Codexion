/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:43 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/05 10:07:07 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	edf(t_coder *coder)
{
	t_data	*data;
	int		id;

	id = coder->id;
	data = coder->data;
	if (check_flag(coder) == 1)
		return (1);
	if (check_id(id, coder, data))
		return (1);
	return (0);
}
