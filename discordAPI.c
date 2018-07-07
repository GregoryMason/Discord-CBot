//
// Created on 4/07/2018.
//

#include "discordAPI.h"

static char* URLDir0[] = {
		NULL, 							/*   0 Generic		*/
		"voice","gateway","track",		/* 1-3 Misc			*/
		"oauth2",						/*   4 Applications	*/
		"friend-suggestions",			/*   5 Self			*/
		"users",						/*   6 Users		*/
		"guilds",						/*   7 Guilds		*/
		"webhooks",						/*   8 Webhooks		*/
		"channels",						/*   9 Channels		*/
		"invites"						/*  10 Invites		*/
};
static char* URLDir1[] = {
		NULL,"%d","%s","@me",	/* 0-3 Generic: NULL,{id},{code/token},@me	*/
		"regions","bot",		/* 4-5 Misc									*/
		"applications","tokens"	/* 6-7 Applications							*/
};
static char* URLDir2[] = {
		NULL,"%d","%s","@me",										/*  0- 3 Generic: NULL,{id},{code/token},@me	*/
		"guilds","channels","settings","connections","mentions",	/*  4- 8 Self									*/
		"profile","notes",											/*  9-10 User									*/
		"relationships",											/*    11 Relationships							*/
		"vanity-url","roles","bans","members","prune","webhooks",	/* 12-17 Guilds									*/
		"embed","emojis","audit-logs","regions","integrations",		/* 18-22 Guilds (continued)						*/
		"delete","ack",												/* 23-24 Guilds (Client Only)					*/
		"typing","permissions","recipients","call",					/* 25-28 Channels								*/
		"messages","pins",											/* 29-30 Messages								*/
		"invites"													/*    31 Invites								*/

};
static char* URLDir3[] = {
		NULL,"%d","@me",		/* 0-1 Generic: NULL,{id},@me	*/
		"bot","reset",			/* 2-3 Misc						*/
		"slack","github",		/* 4-5 Webhooks					*/
		"ring","stop_ringing",	/* 6-7 Channels					*/
		"bulk-delete"			/*   8 Messages					*/
};
static char* URLDir4[] = {
		NULL,								/*   0 Generic				*/
		"reset",							/*   1 Misc					*/
		"sync","roles/%d","settings",		/* 2-4 Guilds				*/
		"ack","reactions",					/* 5-6 Messages				*/
		"reactions/%s",						/*   7 Messages/reactions	*/
		"reactions/%s/%d","reactions/%s/@me"/* 8-9 Messages/reactions */
};
//Used for quick access to piece together the URL endpoint for route
static char** URLDirParts[] = {URLDir0, URLDir1, URLDir2, URLDir3, URLDir4};