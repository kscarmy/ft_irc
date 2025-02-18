/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/13 16:11:09 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	inviteHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);
	std::string targetNick;
	std::string targetChannel;

	if (args.size() >= 3){
		targetNick = args[1];
		targetChannel = args[2];

		if (!server.clientExists(targetNick)){
			sendMessage(clientFd, ERR_NOSUCHNICK(client.getNickName(), targetNick));
			return ;
		}
		if (!server.channelExists(targetChannel)){
			sendMessage(clientFd, ERR_NOSUCHCHANNEL(client.getNickName(), targetChannel));
			return ;
		}
		if (!client.isInChannel(targetChannel)){
			sendMessage(clientFd, ERR_NOTONCHANNEL(client.getNickName(), targetChannel));
			return	;
		}
		if (server.clientInChannel(targetNick, targetChannel))
		{
			sendMessage(clientFd, ERR_USERONCHANNEL(client.getNickName(), targetChannel, targetNick));
			return ;
		}
		//envoie une proposition de rejoindre le channel au client
		sendMessage(server.getClientByName(targetNick).getFd(), RPL_INVITE(client.getNickName(), client.getUserName(), targetNick, targetChannel));
		sendMessage(clientFd, RPL_INVITING(client.getNickName(), targetNick, targetChannel));
		// ajoute linvitation a la liste du client cible
		server.getClientByName(targetNick).addInvite(targetChannel);
	}
	else
		sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "INVITE"));
}