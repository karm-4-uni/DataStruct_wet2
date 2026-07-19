
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
    newNodeUF->relativeMissions = missionsHad;

    return true;
}

NodeUF* ContestantsAndTeamsUF::UnionNodes(NodeUF* recruitingRoot,
                                          NodeUF* recruitedRoot) {
    if (recruitedRoot == nullptr
        || recruitingRoot == nullptr) {
        return nullptr;
    }
    if (recruitedRoot->size < recruitingRoot->size) {
        // recruitingRoot will be the new root
        recruitedRoot->parent = recruitingRoot;

        // maintain the relative fields (no need to change the Skill relative)
        // mission:
        recruitedRoot->relativeMissions -= recruitingRoot->relativeMissions;
        // skill: (no change)

        recruitingRoot->size += recruitedRoot->size;
        recruitedRoot->teamId = recruitingRoot->teamId;

        return recruitingRoot;
    } else {
        // recruitedRoot will be the new root
        recruitingRoot->parent = recruitedRoot;

        // maintain the relative fields
        // mission:
        recruitingRoot->relativeMissions -= recruitedRoot->relativeMissions;
        // skill:
        recruitedRoot->relativeSkill =
            recruitingRoot->relativeSkill * recruitedRoot->relativeSkill;
        recruitingRoot->relativeSkill =
            recruitedRoot->relativeSkill.inv() * recruitingRoot->relativeSkill;

        recruitedRoot->size += recruitingRoot->size;
        recruitedRoot->teamId = recruitingRoot->teamId;

        return recruitedRoot;
    }
}

Skill ContestantsAndTeamsUF::getEffectiveSkill(int contestantId) {
    return contestantIndex.find(contestantId)->skill;
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

std::pair<int, Skill> ContestantsAndTeamsUF::getRelativeFieldsRec(NodeUF* contestPtr) {

    if (contestPtr == nullptr) {
        return std::make_pair(0, Skill::identity());
    }

    // he is the root
    if (contestPtr->parent == nullptr) {
        return  std::make_pair(contestPtr->relativeMissions, contestPtr->relativeSkill);
    }

    // his parent is the root
    if (contestPtr->parent->parent == nullptr) {
        // mission relative field
        int missionCnt = contestPtr->relativeMissions;
        missionCnt += contestPtr->parent->relativeMissions;
        // skill relative field
        Skill skillCnt = contestPtr->parent->relativeSkill;
        skillCnt *= contestPtr->relativeSkill; // root*son (the order is matter)
        return std::make_pair(missionCnt, skillCnt);
    }

    std::pair<int, Skill> missionSkillCnt = getRelativeFieldsRec(contestPtr->parent);
    // get the sum of the mission relative field
    // on the search path to the root
    int missionCnt = missionSkillCnt.first;
    missionCnt += contestPtr->relativeMissions;

    // get the multiplication of the skill relative field (mul : A1 * A2 * ... * A3)
    // on the search path to the root
    Skill skillCnt = missionSkillCnt.second;
    skillCnt *= contestPtr->relativeSkill;

    // The parent of my parent is now definitively the root!
    NodeUF* rootNode = contestPtr->parent->parent;

    // maintain the relative fields
    contestPtr->relativeMissions = missionCnt - rootNode->relativeMissions;
    contestPtr->relativeSkill = rootNode->relativeSkill.inv() * skillCnt;

    // connect to the root
    contestPtr->parent = rootNode;

    return std::make_pair(missionCnt, skillCnt);
}
