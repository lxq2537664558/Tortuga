#ifndef PACKETLIST_HPP_
#define PACKETLIST_HPP_ 

#include "vector2.hpp"

#include <string>

#define PACKET_STRING_SIZE 100

enum class PacketList {
	NONE,

	//connections
	PING,
	PONG,
	JOINREQUEST,
	JOINCONFIRM,
	DISCONNECT,

	//player controls
	NEWPLAYER,
	DELETEPLAYER,
	MOVEMENT,
};

//-------------------------
//connections
//-------------------------

struct Ping {
	PacketList type = PacketList::PING;
};

struct Pong {
	PacketList type = PacketList::PONG;
	char serverName[PACKET_STRING_SIZE];
};

struct JoinRequest {
	PacketList type = PacketList::JOINREQUEST;
	char handle[PACKET_STRING_SIZE];
	char avatar[PACKET_STRING_SIZE];
};

struct JoinConfirm {
	PacketList type = PacketList::JOINCONFIRM;
	int playerID;
};

struct Disconnect {
	PacketList type = PacketList::DISCONNECT;
};

//-------------------------
//player controls
//-------------------------

struct NewPlayer {
	PacketList type = PacketList::NEWPLAYER;
	int playerID;
	char handle[PACKET_STRING_SIZE];
	char avatar[PACKET_STRING_SIZE];
	Vector2 position;
};

struct DeletePlayer {
	PacketList type = PacketList::DELETEPLAYER;
	int playerID;
};

struct Movement {
	PacketList type = PacketList::MOVEMENT;
	int playerID;
	Vector2 position;
	Vector2 motion;
};

//-------------------------
//this state of this is great
//-------------------------

union Packet {
	Packet () {}
	~Packet() {}

	PacketList type = PacketList::NONE;

	//connections
	Ping ping;
	Pong pong;
	JoinRequest joinRequest;
	JoinConfirm joinConfirm;
	Disconnect disconnect;

	//player controls
	NewPlayer newPlayer;
	DeletePlayer deletePlayer;
	Movement movement;
};

#endif
