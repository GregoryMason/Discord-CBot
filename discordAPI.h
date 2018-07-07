//
// Created on 4/07/2018.
//

#ifndef DISCORDBOT_DISCORDAPI_H
#define DISCORDBOT_DISCORDAPI_H


#include <string.h>
#include "restAction.h"

#ifdef APIROUTE
#undef APIROUTE
#endif
#define APIROUTE(name,header,first,second,third,forth) DAPI_ROUTE_ ## name = \
				((( RESTACTION_ ## header )<<28)+\
				((first) << 21)+((second) << 14)+((third) << 7)+((forth) << 0))

typedef enum {
	/* Misc */
	APIROUTE(MISC_GET_VOICE_REGIONS,GET,1,0,0,0),				// voice/regions
	APIROUTE(MISC_GATEWAY,GET,2,0,0,0),							// gateway
	APIROUTE(MISC_GATEWAY_BOT,GET,3,0,0,0),						// gateway/bot
	APIROUTE(MISC_TRACK,POST,4,0,0,0),							// track

	/* Applications */
	APIROUTE(APPS_GET_BOT_APPLICATION,GET,5,3,0,0),				// oauth2/applications/@me
	//Client Only
	APIROUTE(APPS_GET_APPLICATIONS,GET,5,0,0,0),				// oauth2/applications
	APIROUTE(APPS_CREATE_APPLICATION,POST,5,1,0,0),				// oauth2/applications/{application_id}
	APIROUTE(APPS_GET_APPLICATION,GET,5,1,0,0),					// oauth2/applications/{application_id}
	APIROUTE(APPS_MODIFY_APPLICATION,PUT,5,1,0,0),				// oauth2/applications/{application_id}
	APIROUTE(APPS_DELETE_APPLICATION,DELETE,5,1,0,0),			// oauth2/applications/{application_id}
	APIROUTE(APPS_CREATE_BOT,POST,5,1,3,0),						// oauth2/applications/{application_id}/bot
	APIROUTE(APPS_RESET_APPLICATION_SECRET,POST,5,1,4,0),		// oauth2/applications/{application_id}/reset
	APIROUTE(APPS_RESET_BOT_TOKEN,POST,5,1,3,1),				// oauth2/applications/{application_id}/bot/reset
	APIROUTE(APPS_GET_AUTHORIZED_APPLICATIONS,GET,6,0,0,0),		// oauth2/tokens
	APIROUTE(APPS_GET_AUTHORIZED_APPLICATION,GET,6,1,0,0),		// oauth2/tokens/{auth_id}
	APIROUTE(APPS_DELETE_AUTHORIZED_APPLICATION,DELETE,6,1,0,0),// oauth2/tokens/{auth_id}

	/* Self */
	APIROUTE(SELF_GET_SELF,GET,7,0,0,0),						// users/@me
	APIROUTE(SELF_MODIFY_SELF,PATCH,7,0,0,0),					// users/@me
	APIROUTE(SELF_GET_GUILDS,GET,7,4,0,0),						// users/@me/guilds
	APIROUTE(SELF_LEAVE_GUILD,DELETE,7,4,1,0),					// users/@me/guilds/{guild_id}
	APIROUTE(SELF_GET_PRIVATE_CHANNELS,GET,7,5,0,0),			// users/@me/channels
	APIROUTE(SELF_CREATE_PRIVATE_CHANNEL,POST,7,5,0,0),			// users/@me/channels
	APIROUTE(SELF_GATEWAY_BOT,GET,3,0,0,0),						// gateway/bot
	//Client Only
	APIROUTE(SELF_USER_SETTINGS,GET,7,6,0,0),					// users/@me/settings
	APIROUTE(SELF_GET_CONNECTIONS,GET,7,7,0,0),					// users/@me/connections
	APIROUTE(SELF_FRIEND_SUGGESTIONS,GET,8,0,0,0),				// friend-suggestions
	APIROUTE(SELF_GET_RECENT_MESSAGES,GET,7,8,0,0),				// users/@me/mentions

	/* Users */
	APIROUTE(USERS_GET_USER,GET,9,0,0,0),						// users/{user_id}
	APIROUTE(USERS_GET_PROFILE,GET,9,9,0,0),					// users/{user_id}/profile
	APIROUTE(USERS_GET_NOTE,GET,7,10,1,0),						// users/@me/notes/{user_id}
	APIROUTE(USERS_SET_NOTE,PUT,7,10,1,0),						// users/@me/notes/{user_id}

	/* Relationships */
	APIROUTE(RELATION_GET_RELATIONSHIPS,GET,7,11,0,0),			// users/@me/relationships
	APIROUTE(RELATION_GET_RELATIONSHIP,GET,7,11,1,0),			// users/@me/relationships/{user_id}
	APIROUTE(RELATION_ADD_RELATIONSHIP,PUT,7,11,1,0),			// users/@me/relationships/{user_id}
	APIROUTE(RELATION_DELETE_RELATIONSHIP,DELETE,7,11,1,0),		// users/@me/relationships/{user_id}

	/* Guilds */
	APIROUTE(GUILDS_GET_GUILD,GET,11,0,0,0),					// guilds/{guild_id}
	APIROUTE(GUILDS_MODIFY_GUILD,PATCH,11,0,0,0),				// guilds/{guild_id}
	APIROUTE(GUILDS_GET_VANITY_URL,GET,11,12,0,0),				// guilds/{guild_id}/vanity-url
	APIROUTE(GUILDS_CREATE_CHANNEL,POST,11,5,0,0),				// guilds/{guild_id}/channels
	APIROUTE(GUILDS_GET_CHANNELS,GET,11,5,0,0),					// guilds/{guild_id}/channels
	APIROUTE(GUILDS_MODIFY_CHANNELS,PATCH,11,5,0,0),			// guilds/{guild_id}/channels
	APIROUTE(GUILDS_MODIFY_ROLES,PATCH,11,13,0,0),				// guilds/{guild_id}/roles
	APIROUTE(GUILDS_GET_BANS,GET,11,14,0,0),					// guilds/{guild_id}/bans
	APIROUTE(GUILDS_UNBAN,DELETE,11,14,1,0),					// guilds/{guild_id}/bans/{user_id}
	APIROUTE(GUILDS_BAN,PUT,11,14,1,0),							// guilds/{guild_id}/bans/{user_id}
	APIROUTE(GUILDS_KICK_MEMBER,DELETE,11,15,1,0),				// guilds/{guild_id}/members/{user_id}
	APIROUTE(GUILDS_MODIFY_MEMBER,PATCH,11,15,1,0),				// guilds/{guild_id}/members/{user_id}
	APIROUTE(GUILDS_MODIFY_SELF_NICK,PATCH,11,15,2,2),			// guilds/{guild_id}/members/@me/nick
	APIROUTE(GUILDS_PRUNABLE_COUNT,GET,11,16,0,0),				// guilds/{guild_id}/prune
	APIROUTE(GUILDS_PRUNE_MEMBERS,POST,11,16,0,0),				// guilds/{guild_id}/prune
	APIROUTE(GUILDS_GET_WEBHOOKS,GET,11,17,0,0),				// guilds/{guild_id}/webhooks
	APIROUTE(GUILDS_GET_GUILD_EMBED,GET,11,18,0,0),				// guilds/{guild_id}/embed
	APIROUTE(GUILDS_MODIFY_GUILD_EMBED,PATCH,11,18,0,0),		// guilds/{guild_id}/embed
	APIROUTE(GUILDS_GET_GUILD_EMOTES,GET,11,19,0,0),			// guilds/{guild_id}/emojis
	APIROUTE(GUILDS_GET_AUDIT_LOGS,GET,11,20,0,0),				// guilds/{guild_id}/audit-logs
	APIROUTE(GUILDS_GET_VOICE_REGIONS,GET,11,21,0,0),			// guilds/{guild_id}/regions
	APIROUTE(GUILDS_GET_INTEGRATIONS,GET,11,22,0,0),			// guilds/{guild_id}/integrations
	APIROUTE(GUILDS_CREATE_INTEGRATION,POST,11,22,0,0),			// guilds/{guild_id}/integrations
	APIROUTE(GUILDS_DELETE_INTEGRATION,DELETE,11,22,1,0),		// guilds/{guild_id}/integrations/{integration_id}
	APIROUTE(GUILDS_MODIFY_INTEGRATION,PATCH,11,22,1,0),		// guilds/{guild_id}/integrations/{integration_id}
	APIROUTE(GUILDS_SYNC_INTEGRATION,POST,11,22,1,3),			// guilds/{guild_id}/integrations/{integration_id}/sync
	APIROUTE(GUILDS_ADD_MEMBER_ROLE,PUT,11,15,1,4),				// guilds/{guild_id}/members/{user_id}/roles/{role_id}
	APIROUTE(GUILDS_REMOVE_MEMBER_ROLE,DELETE,11,15,1,4),		// guilds/{guild_id}/members/{user_id}/roles/{role_id}
	//Client Only
	APIROUTE(GUILDS_CREATE_GUILD,POST,10,0,0,0),				// guilds
	APIROUTE(GUILDS_DELETE_GUILD,POST,11,23,0,0),				// guilds/{guild_id}/delete
	APIROUTE(GUILDS_ACK_GUILD,POST,11,24,0,0),					// guilds/{guild_id}/ack
	APIROUTE(GUILDS_MODIFY_NOTIFICATION_SETTINGS,POST,7,4,1,5),	// users/@me/guilds/{guild_id}/settings

	/* Emotes */
	//Client Only
	APIROUTE(EMOTES_MODIFY_EMOTE,PATCH,11,19,1,0),				// guilds/{guild_id}/emojis/{emote_id}
	APIROUTE(EMOTES_DELETE_EMOTE,DELETE,11,19,1,0),				// guilds/{guild_id}/emojis/{emote_id}
	APIROUTE(EMOTES_CREATE_EMOTE,POST,11,19,0,0),				// guilds/{guild_id}/emojis

	/* Webhooks */
	APIROUTE(WEBHOOK_GET_WEBHOOK,GET,12,0,0,0),					// webhooks/{webhook_id}
	APIROUTE(WEBHOOK_GET_TOKEN_WEBHOOK,GET,12,2,0,0),			// webhooks/{webhook_id}/{token}
	APIROUTE(WEBHOOK_DELETE_WEBHOOK,DELETE,12,0,0,0),			// webhooks/{webhook_id}
	APIROUTE(WEBHOOK_DELETE_TOKEN_WEBHOOK,DELETE,12,2,0,0),		// webhooks/{webhook_id}/{token}
	APIROUTE(WEBHOOK_MODIFY_WEBHOOK,PATCH,12,0,0,0),			// webhooks/{webhook_id}
	APIROUTE(WEBHOOK_MODIFY_TOKEN_WEBHOOK,PATCH,12,2,0,0),		// webhooks/{webhook_id}/{token}
	APIROUTE(WEBHOOK_EXECUTE_WEBHOOK,POST,12,2,0,0),			// webhooks/{webhook_id}/{token}
	APIROUTE(WEBHOOK_EXECUTE_WEBHOOK_SLACK,POST,12,2,5,0),		// webhooks/{webhook_id}/{token}/slack
	APIROUTE(WEBHOOK_EXECUTE_WEBHOOK_GITHUB,POST,12,2,6,0),		// webhooks/{webhook_id}/{token}/github

	/* Roles */
	APIROUTE(ROLES_GET_ROLES,GET,11,13,0,0),					// guilds/{guild_id}/roles
	APIROUTE(ROLES_CREATE_ROLE,POST,11,13,0,0),					// guilds/{guild_id}/roles
	APIROUTE(ROLES_GET_ROLE,GET,11,13,1,0),						// guilds/{guild_id}/roles/{role_id}
	APIROUTE(ROLES_MODIFY_ROLE,PATCH,11,13,1,0),				// guilds/{guild_id}/roles/{role_id}
	APIROUTE(ROLES_DELETE_ROLE,DELETE,11,13,1,0),				// guilds/{guild_id}/roles/{role_id}

	/* Channels */
	APIROUTE(CHANNELS_DELETE_CHANNEL,DELETE,13,0,0,0),			// channels/{channel_id}
	APIROUTE(CHANNELS_MODIFY_CHANNEL,PATCH,13,0,0,0),			// channels/{channel_id}
	APIROUTE(CHANNELS_SEND_TYPING,POST,13,25,0,0),				// channels/{channel_id}/typing
	APIROUTE(CHANNELS_GET_PERMISSIONS,GET,13,26,0,0),			// channels/{channel_id}/permissions
	APIROUTE(CHANNELS_GET_PERM_OVERRIDE,GET,13,26,1,0),			// channels/{channel_id}/permissions/{permoverride_id}
	APIROUTE(CHANNELS_GET_WEBHOOK,GET,13,17,0,0),				// channels/{channel_id}/webhooks
	APIROUTE(CHANNELS_CREATE_WEBHOOK,POST,13,17,0,0),			// channels/{channel_id}/webhooks
	APIROUTE(CHANNELS_CREATE_PERM_OVERRIDE,PUT,13,26,1,0),		// channels/{channel_id}/permissions/{permoverride_id}
	APIROUTE(CHANNELS_MODIFY_PERM_OVERRIDE,PUT,13,26,1,0),		// channels/{channel_id}/permissions/{permoverride_id}
	APIROUTE(CHANNELS_DELETE_PERM_OVERRIDE,DELETE,13,26,1,0),	// channels/{channel_id}/permissions/{permoverride_id}
	//Client Only
	APIROUTE(CHANNELS_GET_RECIPIENTS,GET,13,27,0,0),			// channels/{channel_id}/recipients
	APIROUTE(CHANNELS_GET_RECIPIENT,GET,13,27,1,0),				// channels/{channel_id}/recipients/{user_id}
	APIROUTE(CHANNELS_ADD_RECIPIENT,PUT,13,27,1,0),				// channels/{channel_id}/recipients/{user_id}
	APIROUTE(CHANNELS_REMOVE_RECIPIENT,DELETE,13,27,1,0),		// channels/{channel_id}/recipients/{user_id}
	APIROUTE(CHANNELS_START_CALL,POST,13,28,7,0),				// channels/{channel_id}/call/ring
	APIROUTE(CHANNELS_STOP_CALL,POST,13,28,8,0),				// channels/{channel_id}/call/stop_ringing

	/* Messages */
	APIROUTE(MESSAGES_SEND_MESSAGE,POST,13,29,0,0),				// channels/{channel_id}/messages
	APIROUTE(MESSAGES_EDIT_MESSAGE,PATCH,13,29,1,0),			// channels/{channel_id}/messages/{message_id}
	APIROUTE(MESSAGES_DELETE_MESSAGE,DELETE,13,29,1,0),			// channels/{channel_id}/messages/{message_id}
	APIROUTE(MESSAGES_GET_PINNED_MESSAGES,GET,13,30,0,0),		// channels/{channel_id}/pins
	APIROUTE(MESSAGES_ADD_PINNED_MESSAGE,PUT,13,30,1,0),		// channels/{channel_id}/pins/{message_id}
	APIROUTE(MESSAGES_REMOVE_PINNED_MESSAGE,DELETE,13,30,1,0),	// channels/{channel_id}/pins/{message_id}
	APIROUTE(MESSAGES_ADD_REACTION,PUT,13,29,1,10),				// channels/{channel_id}/messages/{message_id}/reactions/{reaction_code}/@me
	APIROUTE(MESSAGES_REMOVE_OWN_REACTION,DELETE,13,29,1,10),	// channels/{channel_id}/messages/{message_id}/reactions/{reaction_code}/@me
	APIROUTE(MESSAGES_REMOVE_REACTION,DELETE,13,29,1,9),		// channels/{channel_id}/messages/{message_id}/reactions/{reaction_code}/{user_id}
	APIROUTE(MESSAGES_REMOVE_ALL_REACTIONS,DELETE,13,29,1,7),	// channels/{channel_id}/messages/{message_id}/reactions
	APIROUTE(MESSAGES_GET_REACTION_USERS,GET,13,29,1,8),		// channels/{channel_id}/messages/{message_id}/reactions/{reaction_code}
	APIROUTE(MESSAGES_GET_MESSAGE_HISTORY,GET,13,29,0,0),		// channels/{channel_id}/messages
	//Bot Only
	APIROUTE(MESSAGES_GET_MESSAGE,GET,13,29,1,0),				// channels/{channel_id}/messages/{message_id}
	APIROUTE(MESSAGES_DELETE_MESSAGES,POST,13,29,9,0),			// channels/{channel_id}/messages/bulk-delete
	//Client Only
	APIROUTE(MESSAGES_ACK_MESSAGE,POST,13,29,1,6),				// channels/{channel_id}/messages/{message_id}/ack

	/* Invites */
	APIROUTE(INVITES_GET_INVITE,GET,14,0,0,0),					// invites/{code}
	APIROUTE(INVITES_DELETE_INVITE,DELETE,14,0,0,0),			// invites/{code}
	APIROUTE(INVITES_GET_GUILD_INVITES,GET,11,31,0,0),			// guilds/{guild_id}/invites
	APIROUTE(INVITES_GET_CHANNEL_INVITES,GET,13,31,0,0),		// channels/{channel_id}/invites
	APIROUTE(INVITES_CREATE_INVITE,POST,13,31,0,0)				// channels/{channel_id}/invites
} dAPIRoute;

#endif //DISCORDBOT_DISCORDAPI_H
