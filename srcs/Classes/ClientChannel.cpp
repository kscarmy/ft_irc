/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientChannel.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:47:02 by guderram          #+#    #+#             */
/*   Updated: 2023/10/19 12:01:43 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

// Constructeurs
ClientChannel::ClientChannel() : _ClientChannelOperator(false), _ChannelName("") {}

ClientChannel::ClientChannel(bool clientChannelOperator, const std::string& channelName)
    : _ClientChannelOperator(clientChannelOperator), _ChannelName(channelName) {
		if (DEBUG)
		    std::cout << "ClientChannel : " << " " << _ChannelName << " " << _ClientChannelOperator << std::endl;
	}

ClientChannel::ClientChannel(const ClientChannel& other)
    :  _ClientChannelOperator(other._ClientChannelOperator), _ChannelName(other._ChannelName) {}

// Opérateur d'assignation
ClientChannel& ClientChannel::operator=(const ClientChannel& other) {
    if (this != &other) {
        _ChannelName = other._ChannelName;
        _ClientChannelOperator = other._ClientChannelOperator;
    }
    return *this;
}

// Destructeur
ClientChannel::~ClientChannel() {
}

// Getters
std::string ClientChannel::getChannelName() const {
    return _ChannelName;
}

bool ClientChannel::getClientChannelOperator() const {
    return _ClientChannelOperator;
}

// Setters
void ClientChannel::setChannelName(const std::string& channelName) {
    _ChannelName = channelName;
}

void ClientChannel::setClientChannelOperator(int clientChannelOperator) {
    _ClientChannelOperator = clientChannelOperator;
}

