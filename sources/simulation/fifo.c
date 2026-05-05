/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:01 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/05 10:07:11 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	fifo(t_coder *coder)
{
	t_data	*data;
	int		id;

	id = coder->id;
	data = coder->data;
	if (check_flag(coder) == 1)
		return (1);
	if (check_id(id, coder, data) == 1)
		return (1);
	return (0);
}
