
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

int ContestantsAndTeamsUF::getMissionNumRec(NodeUF* contesPtr) {

    if (contesPtr == nullptr) {
        return 0;
    }

    // he is the root
    if (contesPtr->parent == nullptr) {
        return contesPtr->RelativeMissionsOff;
    }

    // his parent is the root (in this case, we just sum)
    if (contesPtr->parent->parent == nullptr) {
        int missionCnt = contesPtr->RelativeMissionsOff;
        missionCnt += contesPtr->parent->RelativeMissionsOff;

        return missionCnt;
    }

    // get the sum on the search path
    int missionCnt = getMissionNumRec(contesPtr->parent);
    missionCnt += contesPtr->RelativeMissionsOff;

    // The parent of my parent is now definitively the root!
    NodeUF* rootNode = contesPtr->parent->parent;

    // maintain the field (the sum minus the root relative field)
    contesPtr->RelativeMissionsOff = missionCnt - rootNode->RelativeMissionsOff;

    // connect to the root
    contesPtr->parent = rootNode;

    return missionCnt;
}
