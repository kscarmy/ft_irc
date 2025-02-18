/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:46:18 by guderram          #+#    #+#             */
/*   Updated: 2023/10/12 17:27:38 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <vector>
# include <string>
# include "Server.hpp"
# include "Client.hpp"
# include "ft_irc.hpp"

class Server;

class Channel {
private:
	bool						_isSet;
	bool						_isInviteOnly;
	bool						_isTopicOpOnly;
	bool						_isSecret;
	int							_userLimit; // 0 = no limit
    std::string					_ChannelName;
	std::string					_Topic;
	std::vector<int>			_clientFd;
	std::string					_Secret;

public:
    // Constructeurs
    Channel();
    Channel(const std::string& channelName);
    Channel(const Channel& other);

    // Opérateur d'assignation
    Channel& operator=(const Channel& other);

    // Destructeur
    ~Channel();

	// Fcts membres

	void 				sendToAll(const std::string & message);
	void 				sendToAll(const std::string & message, Server & server, std::string nicknameToIgnore);

    // Getters

	bool				getIsSet() const;
	bool				getInviteOnly() const;
	bool				getTopicOpOnly() const;
	bool				isSecret() const;

    std::string			getChannelName() const;
	std::string			getTopic() const;
	std::string			getSecret() const;

	int					getLimit() const;
	int					getClientFd(int i) const;
	int					getNbClients() const;

	std::vector<int> &	getClientFd();

    // Setters

	void setInviteOnly(		bool inviteOnly);
	void setTopicOpOnly(	bool topicOpOnly);
	void setIsSecret(		bool secret);
	void setIsSet(			bool isSet);

    void setChannelName(	const std::string& channelName);
	void setTopic(			const std::string& topic);
	void setSecret(			const std::string& secret);

	void setLimit(			int limit);
	void setClientFd(		const int clientFd);
	void removeClientFd(	const int clientFd);

};

#endif // CHANNEL_HPP
