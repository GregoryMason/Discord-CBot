#include <stdio.h>
#include "restAction.h"

int main() {
	struct rest_action* restAction = NULL;
	restAction = rest_action_init(restAction);
	rest_action_make_request(restAction, "users/@me/guilds", RESTACTION_GET);
	rest_action_cleanup(restAction);

	return 0;
}