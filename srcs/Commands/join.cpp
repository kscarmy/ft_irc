/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/16 16:06:26 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	parseHashtags(std::string & str)
{
	if (str.find('#') == std::string::npos)
	{
		str = "#" + str;
		return ;
	}
}

void 	joinHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);
	bool isOper = client.getOPER();

	if (args.size() >= 2)
	{
		parseHashtags(args[1]);

		if (!server.channelExists(args[1]) && server.getChannelCout() >= MAX_CHANNEL)
		{
			sendMessage(clientFd, RPL_KICK(client.getNickName(), client.getUserName(), args[1], client.getNickName(), ""));
			sendMessage(clientFd, "ERROR : Too many channels on the server");
			return ;
		}

		if (!server.channelExists(args[1])){
			server.addChannel(args[1]);		// Créer le channel
			server.getChannelByName(args[1]).setClientFd(clientFd);	// Ajouter le client au channel
			client.addClientChannel(true, args[1]);	// Ajouter le channel au client
			server.setUserOperIn(client.getNickName(), args[1], true);
		}
		else{
			// TODO : check si le client est déjà dans le channel
			if (client.isInChannel(args[1])){
				sendMessage(clientFd, ERR_USERONCHANNEL(client.getNickName(), args[1], client.getNickName()));
				return ;
			}
			// check mode +l
			if (!isOper && server.getChannelByName(args[1]).getLimit() != 0 && server.getChannelClientCount(args[1]) >= server.getChannelByName(args[1]).getLimit()){
				sendMessage(clientFd, ERR_CHANNELISFULL(client.getNickName(), args[1]));
				return ;
			}
			// check mode +k
			if (!isOper && server.getChannelByName(args[1]).isSecret() && (args.size() < 3 || args[2] != server.getChannelByName(args[1]).getSecret())){
				(sendMessage(clientFd, ERR_BADCHANNELKEY(client.getNickName(), args[1])));
				return ;
			}
			// check mode +i
			if (!isOper && server.getChannelByName(args[1]).getInviteOnly() && !client.isInvited(args[1])){
				sendMessage(clientFd, ERR_INVITEONLYCHAN(client.getNickName(), args[1]));
				return ;
			}
			// remove invite
			if (client.isInvited(args[1]))
				client.removeInvite(args[1]);

			for (int i=0; i < MAX_CHANNEL; i++)
				if (server.getChannels()[i].getChannelName() == args[1]){
					server.getChannels()[i].setClientFd(clientFd);	// Ajouter le client au channel
					client.addClientChannel(false, args[1]);	// Ajouter le channel au client
					break;
				}
		}
			// Envoi du RPLJOIN a tout les membres du channel
			server.getChannelByName(args[1]).sendToAll(RPL_JOIN(client.getNickName(), client.getUserName(), args[1]));
			
			// On crée notre liste des clients du channel sous forme de string pour l'envoyer au client
			// C'est les infos demandées par irssi quand on fait un JOIN
			std::string client_list = "";
			std::vector<int>::const_iterator it = server.getChannelByName(args[1]).getClientFd().begin();
			for (; it != server.getChannelByName(args[1]).getClientFd().end(); it++){
				// Si le client est oper, ajouter un @ devant son nickname
				if (server.isUserOperIn(server.getClientByFd(*it).getNickName(), args[1]))
					client_list += "@";
				client_list += server.getClientByFd(*it).getNickName() + " ";
			}
			// Delete le ' ' en trop à la fin
			client_list.erase(client_list.size() - 1);
			
			sendMessage(clientFd, RPL_SHOWTOPIC(client.getNickName(), args[1], server.getChannelByName(args[1]).getTopic())); //331
			sendMessage(clientFd, RPL_NAMREPLY(client.getNickName(), args[1], client_list)); // 353
			sendMessage(clientFd, RPL_ENDOFNAMES(client.getNickName(), args[1])); // 366

	}
	else
		sendMessage(clientFd, ERR_NEEDMOREPARAMS(server.getClientByFd(clientFd).getNickName(), "JOIN"));
}
