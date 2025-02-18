/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:18 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	passHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	if (isUserLogged(clientFd, server))
	{
		sendMessage(clientFd, ERR_ALREADYREGISTRED(server.getClientByFd(clientFd).getNickName()));
		return ;
	}
	if (args.size() - 1 >= 1){
		if (args[1] == server.getPass()){
			server.getClientByFd(clientFd).setPASS(true);
		}
		else
			sendMessage(clientFd, ERR_PASSWDMISMATCH(server.getClientByFd(clientFd).getNickName()));
	}
	else
		sendMessage(clientFd, ERR_NEEDMOREPARAMS(server.getClientByFd(clientFd).getNickName(), "PASS"));

}
