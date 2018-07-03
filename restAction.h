//
// Created on 3/07/2018.
//

#ifndef DISCORDBOT_RESTACTION_H
#define DISCORDBOT_RESTACTION_H

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#endif //DISCORDBOT_RESTACTION_H

typedef enum {
	RESTACTION_GET,
	RESTACTION_POST,
	RESTACTION_PATCH,
	RESTACTION_DELETE,
	RESTACTION_PUT
} restActionHeader;

struct rest_action {
	CURL* curl;
	struct curl_slist* headers;
	restActionHeader httpHeader;
};

struct rest_action* rest_action_init(struct rest_action* ra);

void rest_action_get_guilds(struct rest_action* ra);

void rest_action_cleanup(struct rest_action* ra);