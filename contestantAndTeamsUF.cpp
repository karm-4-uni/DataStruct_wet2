
#include "ContestantsAndTeamsUF.h"

//****************************************************************************//
    // helper func //

//****************************************************************************//

bool ContestantsAndTeamsUF::addContestantUF(int contestantId, int teamId,
      const Skill &skill, int motivation, int missionsHad) {

    auto newNodeUF = new NodeUF(contestantId, teamId, skill, motivation, missionsHad);

    // if the cond is true, he is already in
    if (!contestantIndex.insert(newNodeUF)) {
        std::free(newNodeUF);
        return false;
    }

    newNodeUF->size++;

    // this we be modified by the team
    newNodeUF->RelativeMissionsOff = missionsHad;

    return true;
}

NodeUF* ContestantsAndTeamsUF::UnionNodes(NodeUF* recruitingRoot,
                                          NodeUF* recruitedRoot) {

}

Skill ContestantsAndTeamsUF::getEffectiveSkill(int contestantId) {

}

bool ContestantsAndTeamsUF::isFound(int contestantId) {
    if (contestantIndex.find(contestantId) != nullptr) {
        return true;
    }
    return false;
}

NodeUF* ContestantsAndTeamsUF::getContestantPtr(int contestantId) {
    return contestantIndex.find(contestantId);
}

int ContestantsAndTeamsUF::getMissionNumRec(NodeUF* contestPtr) {

    if (contestPtr == nullptr) {
        return 0;
    }

    // he is the root
    if (contestPtr->parent == nullptr) {
        return contestPtr->RelativeMissionsOff;
    }

    // his parent is the root (in this case, we just sum)
    if (contestPtr->parent->parent == nullptr) {
        int missionCnt = contestPtr->RelativeMissionsOff;
        missionCnt += contestPtr->parent->RelativeMissionsOff;

        return missionCnt;
    }

    // get the sum on the search path
    int missionCnt = getMissionNumRec(contestPtr->parent);
    missionCnt += contestPtr->RelativeMissionsOff;

    // The parent of my parent is now definitively the root!
    NodeUF* rootNode = contestPtr->parent->parent;

    // maintain the field (the sum minus the root relative field)
    contestPtr->RelativeMissionsOff = missionCnt - rootNode->RelativeMissionsOff;

    // connect to the root
    contestPtr->parent = rootNode;

    return missionCnt;
}

Skill ContestantsAndTeamsUF::getPartialTeamSkillRec(NodeUF* contestPtr) {

    if (contestPtr == nullptr) {
        return Skill::invalid();
    }

    // he is the root
    if (contestPtr->parent == nullptr) {
        return contestPtr->relativeSkill;
    }

    // his parent is the root
    if (contestPtr->parent->parent == nullptr) {
        Skill skillCnt = contestPtr->parent->relativeSkill;
        skillCnt *= contestPtr->relativeSkill; // root*son (the order is matter)

        return skillCnt;
    }

    // get the multiplication on the search path (A1 * A2 * ... * A3)
    Skill skillCnt = getPartialTeamSkillRec(contestPtr->parent);
    skillCnt *= contestPtr->relativeSkill;

    // The parent of my parent is now definitively the root!
    NodeUF* rootNode = contestPtr->parent->parent;

    // maintain the relative field
    // (the inverse of the root relative field multiplied by the tot multiplication)
    contestPtr->relativeSkill = rootNode->relativeSkill.inv() * skillCnt;

    // connect to the root
    contestPtr->parent = rootNode;

    return skillCnt;
}
