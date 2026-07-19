
#ifndef TEAMS_H
#define TEAMS_H

#include "contestantsAndTeamsUF.h"

class Team {
    int teamId ;
    NodeUF* rootNodeUF ;
    int teamExp ;
    int totalMotivation ;
    int memberCnt ;
    Skill totTeamSkill ; // for duel

public:
    Team(int teamId) :teamId(teamId) , rootNodeUF(nullptr) , teamExp(0) , totalMotivation(0)
    ,memberCnt(0) , totTeamSkill(Skill()){
    }
    ~Team() = default;
    void addContestantToTeam(NodeUF* newConstant);

    int gettotalMotivation() const {
        return  totalMotivation;
    }
    void setTotalMotivation(int newTot) {
        totalMotivation = newTot;
    }
int getTeamExp() const {
        return teamExp;
    }
bool isEmpty() const {
        return rootNodeUF;
    }

    Skill* getTeamSkills()  {
        return  &totTeamSkill ;
    }

    void addExp(int add_i) {
        teamExp += add_i;
    }

    NodeUF* getRootNudeUfPtr();

    void setRootNudeUfPtr(NodeUF* newRoot);
};

struct MotivationKey {
    int motivation;
    int teamId;

    explicit MotivationKey(int motivation = 0 , int teamId )
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
