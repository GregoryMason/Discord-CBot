//
// Created on 4/07/2018.
//

#include "discordAPI.h"

static char* URLDir0[] = {
		NULL, 												/*     0 Generic		*/
		"voice/regions","gateway","gateway/bot","track",	/*  1- 4 Misc			*/
		"oauth2/applications","oauth2/tokens",				/*  5- 6 Applications	*/
		"users/@me","friend-suggestions",					/*  7- 8 Self			*/
		"users/%ld",										/*     9 Users			*/
		"guilds","guilds/%ld",								/* 10-11 Guilds			*/
		"webhooks/%ld",										/*    12 Webhooks		*/
		"channels/%ld",										/*    13 Channels		*/
		"invites/%s"										/*    14 Invites		*/
};
static char* URLDir1[] = {
		NULL,"%ld","%s","@me",										/*  0- 3 Generic: NULL,{id},{code/token},@me	*/
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
		NULL,"%ld","@me",		/* 0-2 Generic: NULL,{id},@me	*/
		"bot","reset",			/* 3-4 Misc						*/
		"slack","github",		/* 5-6 Webhooks					*/
		"ring","stop_ringing",	/* 7-8 Channels					*/
		"bulk-delete"			/*   9 Messages					*/
};
static char* URLDir3[] = {
		NULL,									/*    0 Generic				*/
		"reset",								/*    1 Misc				*/
		"nick","sync","roles/%ld","settings",	/* 2- 5 Guilds				*/
		"ack","reactions",						/* 6- 7 Messages			*/
		"reactions/%s",							/*    8 Messages/reactions	*/
		"reactions/%s/%ld","reactions/%s/@me"	/* 9-10 Messages/reactions	*/
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

static restActionHeader read_api_header(dAPIRoute routeCode) {
	return (restActionHeader) (routeCode >> 28);
}

static void perform_api_call(char* routeURL, restActionHeader requestHeader) {
	struct rest_action* restAction = NULL;
	restAction = rest_action_init(restAction);
	rest_action_make_request(restAction, routeURL, requestHeader);

	rest_action_cleanup(restAction);
}


void dapi_get_guilds() {
	dAPIRoute routeCode = DAPI_ROUTE_SELF_GET_GUILDS;
	char* route = build_api_route(routeCode);

	perform_api_call(route, read_api_header(routeCode));
	free(route);
}