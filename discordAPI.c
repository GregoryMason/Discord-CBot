//
// Created on 4/07/2018.
//

#include "discordAPI.h"

static char* URLDir0[] = {
		NULL, 												/*     0 Generic		*/
		"voice/regions","gateway","gateway/bot","track",	/*  1- 4 Misc			*/
		"oauth2/applications","oauth2/tokens",				/*  5- 6 Applications	*/
		"users/@me","friend-suggestions",					/*  7- 8 Self			*/
		"users/%d",											/*     9 Users			*/
		"guilds","guilds/%d",								/* 10-11 Guilds			*/
		"webhooks/%d",										/*    12 Webhooks		*/
		"channels/%d",										/*    13 Channels		*/
		"invites/%s"										/*    14 Invites		*/
};
static char* URLDir1[] = {
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
static char* URLDir2[] = {
		NULL,"%d","@me",		/* 0-1 Generic: NULL,{id},@me	*/
		"bot","reset",			/* 2-3 Misc						*/
		"slack","github",		/* 4-5 Webhooks					*/
		"ring","stop_ringing",	/* 6-7 Channels					*/
		"bulk-delete"			/*   8 Messages					*/
};
static char* URLDir3[] = {
		NULL,								/*   0 Generic				*/
		"reset",							/*   1 Misc					*/
		"sync","roles/%d","settings",		/* 2-4 Guilds				*/
		"ack","reactions",					/* 5-6 Messages				*/
		"reactions/%s",						/*   7 Messages/reactions	*/
		"reactions/%s/%d","reactions/%s/@me"/* 8-9 Messages/reactions	*/
};
//Used for quick access to piece together the URL endpoint for route
static char** URLDirParts[] = {URLDir0, URLDir1, URLDir2, URLDir3};


static char* build_api_route(dAPIRoute routeCode) {
	char* route = malloc(1);
	*route = 0; size_t routeLen = 0;

	char* URLpart;
	for (int i = 0; (URLpart = URLDirParts[i][(routeCode >> (21-(i*7))) & 0x3F]) != NULL && i < 4; i++) {
		size_t sectionLen = strlen(URLpart);
		route = realloc(route, routeLen + sectionLen +2);
		strcat(route, "/");
		strcat(route, URLpart);
		routeLen += sectionLen +1;
	}

	return route;
}