//
// Created on 3/07/2018.
//

#include "restAction.h"
#define API_URL "https://discordapp.com/api/v6/"

static struct curl_slist* build_headers(struct curl_slist* headers) {
	headers = curl_slist_append(headers, "Accept:");

	//Parts for the auth header
	char* base = "Authorization: Bot "; char* botToken = getenv("token");
	//Build the auth header
	char* authHeader = malloc(strlen(base) + strlen(botToken) +1);
	authHeader = strcat(authHeader, base);
	authHeader = strcat(authHeader, botToken);
	//Add it, and clear now redundant copy from heap
	headers = curl_slist_append(headers, authHeader);
	free(authHeader);

	return headers;
}

struct rest_action* rest_action_init(struct rest_action* ra) {
	if (!ra) ra = malloc(sizeof(struct rest_action));

	//Attempt to init curl
	ra->curl = curl_easy_init();
	if (!(ra->curl)) { fprintf(stderr, "Failed to init curl"); return NULL; }

	//Create struct for HTTP headers
	ra->headers = NULL;
	ra->headers = build_headers(ra->headers);

	//Add the HTTP headers to the curl command
	curl_easy_setopt(ra->curl, CURLOPT_HTTPHEADER, ra->headers);

	return ra;
}

static char* build_url(char* endpoint) {
	char* endPointURL = malloc(strlen(API_URL) + strlen(endpoint) +1);
	endPointURL = strcat(endPointURL, API_URL);
	endPointURL = strcat(endPointURL, endpoint);

	return endPointURL;
}


struct RespStruct {
	char* resp;
	size_t size;
};

static size_t write_resp_callback(void* contents, size_t size, size_t nmemb, void* respPtr) {
	size_t realSize = size * nmemb;
	struct RespStruct* resp = (struct RespStruct*) respPtr;

	char* reloc = realloc(resp->resp, realSize +1);
	if (reloc == NULL) {
		fprintf(stderr, "Not enough memory to realloc for response");
		free(resp->resp);
		return 0;
	}
	resp->resp = reloc;

	memcpy(resp->resp, contents, realSize);
	resp->size = realSize;
	resp->resp[realSize] = 0;

	return realSize;
}

static void perform_request(CURL* curl) {
	//Perform the request, with res for the return code
	CURLcode res = curl_easy_perform(curl);

	//Check if there was an error
	if(res != CURLE_OK) fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
}

void rest_action_get_guilds(struct rest_action* ra) {
	if (!ra) { fprintf(stderr, "trying to get guild with NULL rest_action"); return; }

	//Build and set target URL
	char* targetURL = build_url("users/@me/guilds");
	curl_easy_setopt(ra->curl, CURLOPT_URL, targetURL);
	free(targetURL);

	//Add getting the responses from curl
	struct RespStruct response;
	response.resp = malloc(1); response.size = 0;
	curl_easy_setopt(ra->curl, CURLOPT_WRITEFUNCTION, write_resp_callback);
	curl_easy_setopt(ra->curl, CURLOPT_WRITEDATA, (void*) &response);

	//Run request
	perform_request(ra->curl);

	printf("%s\n", response.resp);
}

void rest_action_cleanup(struct rest_action* ra) {
	curl_easy_cleanup(ra->curl);
	curl_slist_free_all(ra->headers);
	free(ra);
}