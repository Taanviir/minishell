/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:48:19 by tanas             #+#    #+#             */
/*   Updated: 2023/06/18 17:50:11 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

// bit masks for retrieving primary and secondary type
# define PRI_TYPE	0xF0	// 11110000
# define SUB_TYPE	0x0F	// 00001111

// primary types
# define CMD		0x10	// command
# define BCMD		0x20	// built-in command (cd, exit, ...)
# define ARG		0x30	// argument
# define VAR		0x50	// variable
# define QTS		0x60	// quotes
# define BSL		0x70	// backslash

// secondary types
// operators

#endif

// TODO test commands from (bin, wrong, ./, )
// in case of 2 commands with similar names, one in /bin and the other in ./ which has higher priority
// priority is location in split[index]