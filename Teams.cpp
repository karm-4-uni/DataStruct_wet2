
#include "Teams.h"


// the tot motivation of the team well changes after this,
// we have to handle it on the AVLtree (motivation is the key for the tree)
void Team::addContestantToTeam(NodeUF* newConstant) {
    if (newConstant == nullptr) return;

// connect to the root (it's fine if root == nullptr)
    newConstant->parent = rootNodeUF;

//** maintains the changes on the team because of the new member **//
    memberCnt++;
    totTeamSkill *= newConstant->skill;
    totalMotivation += newConstant->motivation;
    if (rootNodeUF == nullptr) { // first contestant on the team
        rootNodeUF = newConstant;
        return;
    }
    rootNodeUF->size++;

//** maintain relative field of the new contestant **//
    // relative skill
    Skill rootInvRelativeSkill = rootNodeUF->relativeSkill.inv();
    Skill newMemRelativeSkill = newConstant->relativeSkill;
    newConstant->relativeSkill = rootInvRelativeSkill * newMemRelativeSkill;

    // relative missions
    int rootRelativeMissions = rootNodeUF->relativeMissions;
    int newMemRelativeMissions = newConstant->relativeMissions;
    newConstant->relativeMissions -= rootRelativeMissions;
}

NodeUF* Team::getRootNudeUfPtr() {
    return rootNodeUF;
}

void Team::setRootNudeUfPtr(NodeUF* newRoot) {
    rootNodeUF = newRoot;
}