# ft_irc

## Introduction

ft_irc est une implémentation d'un serveur IRC (Internet Relay Chat) en C++98. Il permet aux clients IRC de se connecter, de créer et rejoindre des canaux, d'échanger des messages et de gérer les permissions via des opérateurs.

## Installation

### Prérequis

- Un compilateur compatible C++98 comme g++
- Make
- Un client IRC tel que [irssi](https://irssi.org/)

### Compilation

```sh
make
```

Le binaire `ircserv` sera généré.

## Utilisation

### Lancer le serveur

```sh
./ircserv <port> <password>
```

- `<port>` : Le port d'écoute du serveur IRC.
- `<password>` : Le mot de passe requis pour se connecter.

### Connexion avec un client IRC

Avec **irssi** :

```sh
irssi -c 127.0.0.1 -p <port> -w <password>
```

## Fonctionnalités

- Authentification avec mot de passe
- Gestion des utilisateurs et canaux
- Messages privés et de groupe
- Commandes des opérateurs :
  - `KICK` : Expulser un utilisateur
  - `INVITE` : Inviter un utilisateur
  - `TOPIC` : Modifier le sujet du canal
  - `MODE` : Gestion des permissions (`i`, `t`, `k`, `o`, `l`)
- **Fonctionnalités bonus** :
  - Transfert de fichiers entre utilisateurs
  - Mini-jeu intégré au serveur IRC

## Tests

Un test basique peut être réalisé avec **nc** :

```sh
nc 127.0.0.1 <port>
```


## Documentation

Le sujet du projet [fr.sujet.ft_irc.pdf](https://github.com/kscarmy/ft_irc/blob/main/fr.sujet.ft_irc.pdf)


## Auteurs

Projet réalisé par :
- [kscarmy](https://github.com/kscarmy)
- [dbelpaum](https://github.com/dbelpaum/ft_irc)

## Contribution

Les contributions sont les bienvenues. Forkez le dépôt, proposez des corrections ou des améliorations via des pull requests.

