//
// Created on 3/07/2018.
//

#ifndef DISCORDBOT_RESTACTION_H
#define DISCORDBOT_RESTACTION_H

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

#endif //DISCORDBOT_RESTACTION_H

typedef enum {
	RESTACTION_GET,
	RESTACTION_POST,
	RESTACTION_PATCH,
	RESTACTION_DELETE,
	RESTACTION_PUT,
	RESTACTION_HEADER_COUNT //Number of headers rest action uses
} restActionHeader;

struct rest_action {
	CURL* curl;
	struct curl_slist* headers;
};

struct rest_action* rest_action_init(struct rest_action* ra);

void rest_action_make_request(struct rest_action* ra, const char* endpoint, const restActionHeader httpHeader);

void rest_action_cleanup(struct rest_action* ra);