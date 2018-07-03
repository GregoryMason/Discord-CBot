#include <stdio.h>
#include "restAction.h"

int main() {
	struct rest_action* restAction = NULL;
	restAction = rest_action_init(restAction);
	rest_action_get_guilds(restAction);
	rest_action_cleanup(restAction);

	return 0;
}