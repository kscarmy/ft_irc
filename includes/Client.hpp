/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:11:03 by guderram          #+#    #+#             */
/*   Updated: 2023/10/19 12:06:13 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <vector>
# include <string>
# include <iostream>
# include "ClientChannel.hpp"
# define DEBUG 0
// # include "ft_irc.hpp"

# define MAX_INVITS 10


class Client {
private:
	bool						_isSet;
	int							_fd;
	bool						_PASS;
	bool						_NICK;
	bool						_USER;
	bool						_OPER;
	std::string					_NickName;
    std::string 				_UserName;
	std::string					_RealName;
	std::string					_CurrentChannel;
	std::string					_invitChannel[MAX_INVITS];
	std::string					_buff;
	int							_mode; // 0 = normal, 1 = invisible, 2 = wallops
    std::vector<ClientChannel>	_ClientChannel;

public:
    // Constructeurs
    Client();
	Client(const int ClientFd);
    Client(const int ClientFd, std::string& userName, const std::string& nickName);
    Client(const Client& other);

    // Opérateur d'assignation
    Client& operator=(const Client& other);

    // Destructeur
    ~Client();

    // Getters

	bool						getPASS() const;
	bool						getNICK() const;
	bool						getUSER() const;
	bool						getIsSet() const;
	bool						isInChannel(std::string channelName) const;
	bool						isInvited(std::string channelName) const;
	bool						getOPER() const;

    std::string					getUserName() const;
    std::string					getNickName() const;
	std::string 				getRealName() const;
	std::string 				getCurrentChannel() const;
	std::string					getBuff() const;

	int							getFd() const;
	int							getMode() const;

	std::vector<ClientChannel>&	getClientChannel();
	ClientChannel &				getClientChannelName(std::string channelName);
	
    // Setters
	
	void setPASS(				bool pass);
	void setNICK(				bool nick);
	void setUSER(				bool user);
	void setIsSet(				bool isSet);
	void setOPER(				bool oper);

	void setRealName(			const std::string& realName);
	void setUserName(			const std::string& userName);
    void setNickName(			const std::string& nickName);
	void setCurrentChannel(		const std::string& currentChannel);
	void addInvite(				const std::string& channelName);
	void removeInvite(			const std::string& channelName);
	void setBuff(				const std::string& buff);

	void setMode(				int mode);
	void setFd(					int fd);

	


    // Fonctions pour gérer les canaux
	
    void addClientChannel(		bool clientChannelOperator, std::string channelName);
    void removeClientChannel(	std::string channelName);

	// Fonctions qui donne les infos du client
	void debug();

};

#endif // CLIENT_HPP
