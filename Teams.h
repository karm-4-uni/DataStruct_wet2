
#ifndef TEAMS_H
#define TEAMS_H

#include "contestantsAndTeamsUF.h"

class Team {
    int teamId = 0;
    NodeUF* rootNodeUF = nullptr;
    int teamExp = 0;
    int totalMotivation = 0;
    int memberCount = 0;

public:
    Team();
    ~Team() = default;
};

#endif //TEAMS_H
