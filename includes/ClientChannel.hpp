/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientChannel.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:46:14 by guderram          #+#    #+#             */
/*   Updated: 2023/08/14 17:47:22 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CHANNEL_HPP
# define CLIENT_CHANNEL_HPP

# include <vector>
# include <string>
# include <iostream>
// #include "ft_irc.hpp"

class ClientChannel {
private:
	bool					_ClientChannelOperator;
    std::string				_ChannelName;

public:
    // Constructeurs
    ClientChannel();
    ClientChannel(bool clientChannelOperator, const std::string& channelName);
    ClientChannel(const ClientChannel& other);

    // Opérateur d'assignation
    ClientChannel& operator=(const ClientChannel& other);

    // Destructeur
    ~ClientChannel();

    // Getters

    std::string			getChannelName() const;
    bool				getClientChannelOperator() const;

    // Setters

    void setChannelName(			const std::string& channelName);
    void setClientChannelOperator(	int clientChannelOperator);

};

#endif // CLIENT_CHANNEL_HPP
