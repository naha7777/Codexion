/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:20:19 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 10:11:10 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_queu	*new_queu(void *coder)
{
	t_queu	*queu;

	queu = malloc(sizeof(t_queu));
	if (queu == NULL)
		return (NULL);
	queu->coder = coder;
	queu->next = NULL;
	return (queu);
}

static t_queu	*queu_last(t_queu *queu)
{
	if (!queu)
		return (NULL);
	while (queu->next)
		queu = queu->next;
	return (queu);
}

void	queu_addlast(t_queu **queu, t_queu *new)
{
	if (*queu == NULL)
		(*queu) = new;
	else
		queu_last((*queu))->next = new;
}

void	queuclear(t_queu **queu)
{
	t_queu *temp;

	if (!queu || !*queu)
		return ;
	while (*queu)
	{
		temp = (*queu)->next;
		free(*queu);
		*queu = temp;
	}
}
