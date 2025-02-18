/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:38:49 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/21 14:34:51 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include "Client.hpp"
# include "ft_irc.hpp"
# include "Channel.hpp"

void signalHandler(int signal);

class Server
{
	private:

		int						_errorInit;
		int						_port;
		int						_sock_fd;
		int						_addrlen;
		int						_botStatus;

		// std::vector<Channel>	_ChannelList;
		// std::vector<Client>		_ClientList; //  a supprimer

		Client					_Client[MAX_USERS];
		Channel					_Channel[MAX_CHANNEL]; // nouvelle gestion des channels

		std::string				_password;
		std::string				_operPassword;
		std::string				_botString;
		std::string				_botFound;
		
		struct sockaddr_in		_address;
		
		struct pollfd			_pollFd[MAX_USERS];

		char					_buffer[BUFFER_SIZE];
		
		volatile bool			_isRunning;

		bool					_isBot;

	public:
		Server(int port, std::string passsword);
		~Server();
		void					run();
		void					debug();				// Debug function



		// Getters

		bool 					channelExists(std::string name);
		bool 					clientExists(std::string name);
		bool 					clientInChannel(std::string nickname, std::string channelName);
		bool					clientInChannelOp(std::string name, std::string channelName);
		bool 					getIsBot() const;
		bool					isUserOperIn(std::string nickname, std::string channelName);

		int 					getChannelCout() const;
		int 					getClientFdByNick(std::string Nick) const;
		int 					getChannelClientCount(std::string channelName);

		size_t 					getClientCount() const;

		char 					*_getUserTag(int fd);

		std::string 			getPass() const;
		std::string 			getNickByFd(int fd);
		std::string 			getOperPass() const;
		std::string 			getBotString() const;

		Client& 				getClientByFd(int fd);
		
		// std::vector<Channel> 	getChannelList();
		
		Client* 				getClients();
		Client& 				getClientByName(std::string name);

		Channel& 				getChannelByName(std::string name);
		Channel* 				getChannels();

		std::string 			getBotFound() const;
		int 					getBotStatus() const;


		// Setters

		void removeClientByFd(int		fdToRemove);
		void removeChannel(std::string 	name);	
		void addClient(int				newClientFd, char * ipAddr);  /////// A MODIFIER
		void setBotFound(std::string	botFound);
		void setBotStatus(int			botStatus);
		void addChannel(std::string		name);
		void setIsBot(bool				isBot);
		void setBotString(std::string	botString);
		void setUserOperIn(std::string nickname, std::string channelName, bool oper);
		void setUserServerOper(std::string nickname, bool oper);
		
		//member functions

		void mainLoop();

		void initialize();
		
		void handleNewConnection();
		void handleClientCommunication(int index);

		void sendWelcomeMessage(int socket);

		void sendToAllUsersOf(std::string channelName, std::string message);
		void sendToAllUserChannels(std::string nickname, std::string message);

		void removeClientFromChannel(std::string name, std::string channelName, Server &server);


};


#endif