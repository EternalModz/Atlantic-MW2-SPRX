#include "Includes.h"

// Function prototypes
int getAmountOnTeam(team_t team);
void SetTeam(int botNum, handle_t* handle, handleCall_t type);
void SetClass(int botNum, handle_t* handle, handleCall_t type);
void setupBot(int botNum, handle_t* handle, handleCall_t type);
void SpawnBots(int botAmount);
void spawnBots(int arg, handle_t* handle, handleCall_t type);
bool IsBot(int clientNum);

// Function pointers
opd_s SV_AddTestClient_t = { SV_AddTestClient_a, TOC };
opd_s SV_GetGuid_t = { 0x218E28, TOC };
char* (*SV_GetGuid)(int clientNum) = (char* (*)(int)) & SV_GetGuid_t;
gentity_s* (*SV_AddTestClient)() = (gentity_s * (*)()) & SV_AddTestClient_t;

// Get the count of players on a specific team
int getAmountOnTeam(team_t team) {
    int count = 0;
    for (int i = 0; i < level_locals->maxclients; i++) {
        gclient_s* client = &g_clients[i];
        if (client->sess.cs.team == team)
            ++count;
    }
    return count;
}

// Set the team for a bot based on game type and team availability
void SetTeam(int botNum, handle_t* handle, handleCall_t type) {
    gclient_s* bot = &g_clients[botNum];
    if (strcmp(ui_gametype->current.string, "dm")) {
        if (!level->botTeamIndex) {
            // Team assignment logic for non-bot teams
            if (level->spawnerClient->sess.cs.team == TEAM_AXIS) {
                Scr_AddString("allies");
                bot->sess.cs.team = TEAM_ALLIES;
                Client[botNum].azzaTeam = TEAM_ALLIES;
            }
            else if (level->spawnerClient->sess.cs.team == TEAM_ALLIES) {
                Scr_AddString("axis");
                bot->sess.cs.team = TEAM_AXIS;
                Client[botNum].azzaTeam = TEAM_AXIS;
            }
        }
        else if (level->botTeamIndex == 1) {
            // Team assignment logic for bot team
            if (level->spawnerClient->sess.cs.team == TEAM_AXIS) {
                Scr_AddString("axis");
                bot->sess.cs.team = TEAM_AXIS;
                Client[botNum].azzaTeam = TEAM_AXIS;
            }
            else if (level->spawnerClient->sess.cs.team == TEAM_ALLIES) {
                Scr_AddString("allies");
                bot->sess.cs.team = TEAM_ALLIES;
                Client[botNum].azzaTeam = TEAM_ALLIES;
            }
        }
    }
    else {
        // Default team assignment for non-DM game types
        Scr_AddString("autoassign");
        bot->sess.cs.team = TEAM_FREE;
        Client[botNum].azzaTeam = TEAM_FREE;
    }
    Scr_AddString("team_marinesopfor");
    Scr_NotifyNum(botNum, CT_ENTITY, scr_const->menuresponse, 2);
}

// Set the class for a bot
void SetClass(int botNum, handle_t* handle, handleCall_t type) {
    Scr_AddString("class0");
    Scr_AddString("changeclass");
    Scr_NotifyNum(botNum, CT_ENTITY, scr_const->menuresponse, 2);
}

// Setup bot attributes
void setupBot(int botNum, handle_t* handle, handleCall_t type) {
    gclient_s* client = &g_clients[botNum];
    client->sess.cs.rank = 0x45;
    client->sess.cs.prestige = G_irand(0, 11);
    client->sess.emblem = G_irand(0, 251);
    client->sess.title = G_irand(0, 251);
}

// Spawn a specified number of bots
void SpawnBots(int botAmount) {
    if (strcmp(ui_gametype->current.string, "dm")) {
        if ((!level->botTeamIndex && getAmountOnTeam(TEAM_AXIS) >= 9) || (level->botTeamIndex == 1 && getAmountOnTeam(TEAM_ALLIES) >= 9))
            return;
    }
    if (botAmount > level_locals->maxclients)
        botAmount = level_locals->maxclients;

    // Spawn bots and set up hooks
    for (int i = 0; i < botAmount; i++) {
        gentity_s* botent = SV_AddTestClient();
        if (botent) {
            handleHookAllocTemp(botent->s.number, SetTeam, 300);
            handleHookAllocTemp(botent->s.number, SetClass, 600);
            handleAllocTemp(botent->s.number, setupBot, 750);
        }
    }
}

// Handler function for spawning bots
void spawnBots(int arg, handle_t* handle, handleCall_t type) {
    SpawnBots(arg);
}

// Check if a client is a bot based on its GUID
bool IsBot(int clientNum) {
    return strstr(SV_GetGuid(clientNum), "bot");
}