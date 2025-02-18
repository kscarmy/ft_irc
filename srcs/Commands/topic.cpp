/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/18 14:25:42 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	topicHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	int		argNb = args.size();
	Client & client = server.getClientByFd(clientFd);

	if (argNb >= 2)
	{
		if (!server.channelExists(args[1]) || !server.clientInChannel(client.getNickName(), args[1])){	// Check si le client est dans le channel
			sendMessage(clientFd, ERR_NOTONCHANNEL(client.getNickName(), args[1]));
			return ;
		}
		if (argNb == 2){
			std::string topic = server.getChannelByName(args[1]).getTopic();
			if (topic == "No topic is set")
				sendMessage(clientFd, RPL_NOTOPIC(server.getClientByFd(clientFd).getNickName(), args[1]));
			else
				sendMessage(clientFd, RPL_SHOWTOPIC(client.getNickName(), args[1], topic));
			return	;
		}


		if (argNb > 2)
		{
			// Check si mode +t
			if (server.getChannelByName(args[1]).getTopicOpOnly() && (!client.getOPER() && !server.isUserOperIn(client.getNickName(), args[1])))
			{
				sendMessage(clientFd, ERR_CHANOPRIVSNEEDED(client.getNickName(), args[1]));
				return ;
			}
			std::string newtopic = args[2];
			for (int i=3; i < (int)args.size(); i++){
				newtopic += " " + args[i];
			} 
			server.getChannelByName(args[1]).setTopic(newtopic);
			// Envoie la notification de changement de topic à tout le monde
			server.getChannelByName(args[1]).sendToAll(RPL_TOPIC(client.getNickName(), client.getUserName(), args[1], newtopic));
		}
	}
	else
		sendMessage(clientFd, ERR_NEEDMOREPARAMS(server.getClientByFd(clientFd).getNickName(), "TOPIC"));
}
