/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:58:29 by guderram          #+#    #+#             */
/*   Updated: 2023/10/12 17:55:51 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void privmsgHandler(std::vector<std::string> args, int clientFd, Server &server){ //  private messages to users : PRIVMSG <user> <message>
	int		argNb = args.size();
	Client & client = server.getClientByFd(clientFd);

	if (argNb >= 3){
		std::string message = args[2];
		message.erase(0, 1);	// delete les ':' du début du message
		for (int i = 3; i < argNb; i++)
			message += " " + args[i];
		if (args[1].find('#') == std::string::npos)	// --> PRIVMSG destiné à un utilisateur
		{
			if (!server.clientExists(args[1])){
				sendMessage(clientFd, ERR_NOSUCHNICK(client.getNickName(), args[1]));
				return ;
			}
			// Envoi du message privé
			sendMessage(server.getClientByName(args[1]).getFd(), RPL_PRIVMSG(client.getNickName(), client.getUserName(), args[1], message));
		}
		else	// --> PRIVMSG destiné à un #channel
		{
			if (!server.channelExists(args[1])){
				sendMessage(clientFd, ERR_NOSUCHNICK(client.getNickName(), args[1]));
				return ;
			}
			// Envoi du message à tout le monde sauf a celui qui l'a envoyé
			server.getChannelByName(args[1]).sendToAll(RPL_PRIVMSG(client.getNickName(), client.getUserName(), (std::string(args[1])), message), server, client.getNickName());
		}
	}
	else
		sendMessage(clientFd, ERR_NEEDMOREPARAMS(server.getClientByFd(clientFd).getNickName(), "PRIVMSG"));
}
