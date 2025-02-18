/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/19 10:16:38 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


static void	modeI(int clientFd, std::string ArgChannel, char sign, Server& server);
static void	modeT(int clientFd, std::string ArgChannel, char sign, Server& server);
static void	modeK(int clientFd, std::string ArgChannel, char sign, Server& server, std::string ArgKey);
static void	modeO(int clientFd, std::string ArgChannel, char sign, Server& server, std::string ArgTarget);
static void	modeL(int clientFd, std::string ArgChannel, char sign, Server& server, int ArgLimit);
static void userModeI(int clientFd, std::string nickname, char sign, Server& server);


void 	modeHandler(std::vector<std::string> args, int clientFd, Server& server)
{
	// Cas à gérer : https://media.discordapp.net/attachments/952890980003115048/1140651641876521070/rotate.png?width=702&height=936
	Client & client = server.getClientByFd(clientFd);
	
	if (args.size() < 3)			// Check si y'a 3+ args (ex: MODE #general +i)
		return ((void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")));

	if (args[2].size() != 2 || (args[2][0] != '+' && args[2][0] != '-'))	// Check si le 2e argument est bien de la forme +x ou -X
		return ((void)sendMessage(clientFd,ERR_MODEUNKNOWNFLAG(client.getNickName())));
	char sign = args[2][0];
	char mode = args[2][1];

	if (mode == 'i' && args[1].find('#') == std::string::npos)
		return userModeI(clientFd, args[1], sign, server);

	if (args[1].find('#') == std::string::npos)		// Si c'est pas un channel on gère pas bonne chance
		return ;
	if (server.channelExists(args[1]) == false)		// Check si arg[1] est bien un channel existant
		return ((void)sendMessage(clientFd, ERR_NOSUCHCHANNEL(client.getNickName(), args[1])));

	// Check si le client est bien dans le channel
	if (server.clientInChannel(server.getNickByFd(clientFd), args[1]) == false)
		return ((void)sendMessage(clientFd, ERR_NOTONCHANNEL(server.getNickByFd(clientFd), args[1])));
	// Check si le client est bien opérateur du channel
	if (server.getClientByFd(clientFd).getClientChannelName(args[1]).getClientChannelOperator() == false && !server.getClientByFd(clientFd).getOPER())
		return ((void)sendMessage(clientFd, ERR_CHANOPRIVSNEEDED(args[1], server.getNickByFd(clientFd))));

	switch (mode)
	{
		case 'i':
			if (args.size() < 3)
				return ((void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")));
			modeI(clientFd, args[1], sign, server);
			break;
		case 't':
			if (args.size() < 3)
					return ((void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")));
			modeT(clientFd, args[1], sign, server);
			break;
		case 'k':
			if (sign == '+' && args.size() < 4)
				return ((void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")));
			else if (sign == '-' && args.size() < 3)
				return ((void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")));
			modeK(clientFd, args[1], sign, server,  args[3]);
			break;
		case 'o':
			if (args.size() < 4)
				return ((void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")));
			modeO(clientFd, args[1], sign, server, args[3]);
			break;
		case 'l':
			if (sign == '-' && args.size() < 3)
				return ((void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")));
			else if (sign == '+' && args.size() < 4)
				return ((void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "MODE")));
			if (sign == '-')
				modeL(clientFd, args[1], sign, server, 0);
			else if (args.size() == 4)
				modeL(clientFd, args[1], sign, server, std::atoi(args[3].c_str()));
			break;
		default:
			return ((void)sendMessage(clientFd, ERR_MODEUNKNOWNFLAG(client.getNickName())));
	}
}

static void modeI(int clientFd, std::string ArgChannel, char sign, Server& server)
{
	if (sign == '+')
	{
		server.getChannelByName(ArgChannel).setInviteOnly(true);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "+i"));
	}
	else if (sign == '-')
	{
		server.getChannelByName(ArgChannel).setInviteOnly(false);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "-i"));
	}
}

static void modeT(int clientFd, std::string ArgChannel, char sign, Server& server)
{
	if (sign == '-')
	{
		server.getChannelByName(ArgChannel).setTopicOpOnly(true);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "-t"));
	}
	else if (sign == '+')
	{
		server.getChannelByName(ArgChannel).setTopicOpOnly(false);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "+t"));
	}
}

static void modeK(int clientFd, std::string ArgChannel, char sign, Server& server, std::string ArgKey)
{
	if (sign == '+')
	{
		server.getChannelByName(ArgChannel).setIsSecret(true);
		server.getChannelByName(ArgChannel).setSecret(ArgKey);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "+k"));
		return ;
	}
	else if (sign == '-')
	{
		server.getChannelByName(ArgChannel).setIsSecret(false);
		server.getChannelByName(ArgChannel).setSecret("");
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "-k"));
	}
}

static void modeO(int clientFd, std::string ArgChannel, char sign, Server& server, std::string ArgTarget)
{
	if (server.clientInChannel(ArgTarget, ArgChannel) == false)
		return ((void)sendMessage(clientFd, ERR_USERNOTINCHANNEL(server.getNickByFd(clientFd), ArgChannel, ArgTarget)));

	if (sign == '+')
	{
		server.getClientByName(ArgTarget).getClientChannelName(ArgChannel).setClientChannelOperator(true);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "+o"));
	}
	else
	{
		server.getClientByName(ArgTarget).getClientChannelName(ArgChannel).setClientChannelOperator(false);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "-o"));
	}
}

static void modeL(int clientFd, std::string ArgChannel, char sign, Server& server, int ArgLimit)
{
	if (sign == '+' && ArgLimit < 1)
		return ;
	
	if (sign == '-')
	{
		server.getChannelByName(ArgChannel).setLimit(0);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "-l"));
	}
	else if (sign == '+')
	{
		server.getChannelByName(ArgChannel).setLimit(ArgLimit);
		server.sendToAllUsersOf(ArgChannel, RPL_MODE(server.getNickByFd(clientFd), server.getClientByFd(clientFd).getUserName(), ArgChannel, "+l"));
	}

}

static void userModeI(int clientFd, std::string nickname, char sign, Server& server)
{
	if (sign != '+')
		return ;
	if (server.getClientByFd(clientFd).getNickName() != nickname)
		return ((void)sendMessage(clientFd, ERR_USERSDONTMATCH(server.getClientByFd(clientFd).getNickName())));
	sendMessage(clientFd, RPL_MODE_USER(nickname, server.getClientByFd(clientFd).getUserName(), nickname, "+i"));
}