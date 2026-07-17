
#ifndef TEAMS_H
#define TEAMS_H

#include "contestantsAndTeamsUF.h"

class Team {
    int teamId = 0;
    NodeUF* rootNodeUF = nullptr;
    int teamExp = 0;
    int totalMotivation = 0;
    int memberCnt = 0;
    Skill totTeamSkill = Skill(); // for duel

public:
    Team();
    ~Team() = default;
    void addContestantToTeam(NodeUF* newConstant);
};

struct MotivationKey {
    int motivation;
    int teamId;

    explicit MotivationKey(int motivation = 0, int teamId = 0)
        : motivation(motivation), teamId(teamId) {}

    bool operator==(const MotivationKey& other) const {
        return motivation == other.motivation && teamId == other.teamId;
    }
    bool operator<(const MotivationKey& other) const {
        if (motivation != other.motivation) return motivation < other.motivation;
        return teamId < other.teamId;
    }
    bool operator>(const MotivationKey& other) const {
        return other < *this;
    }
};

#endif //TEAMS_H
