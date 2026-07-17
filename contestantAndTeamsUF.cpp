
#include "ContestantsAndTeamsUF.h"

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


NodeUF* ContestantsAndTeamsUF::Find(int contestantId) {

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