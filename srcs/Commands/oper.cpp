/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:34:40 by guderram          #+#    #+#             */
/*   Updated: 2023/10/13 13:57:34 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	operHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);

	if (args.size() >= 3){
		// user exist
		if (!server.clientExists(args[1])){
			sendMessage(clientFd, ERR_NOSUCHNICK(client.getNickName(), args[1]));
			return ;
		}
		if (args[2] == server.getOperPass()){
			client.setOPER(true);
			sendMessage(server.getClientByName(args[1]).getFd(), RPL_OPER(server.getClientByName(args[1]).getNickName()));
		}
		else
			sendMessage(clientFd, ERR_PASSWDMISMATCH(client.getNickName()));
	}
	else
		sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "OPER"));
}
