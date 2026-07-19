
#ifndef UNIONFIND_H
#define UNIONFIND_H

// #include <memory>
#include "HashTable.h"
#include "wet2util.h"
#include <utility>

//*************************************************************************//
// nodes for UF class evry node for one contestant //
struct NodeUF {
    int contestantId = 0;
    int teamId = 0;
    NodeUF* parent = nullptr;
    int size = 0;                 // used for the union (to ensure O(log*n))
    const Skill skill = Skill();
    int motivation = 0;
    int missionsHad = 0;
    int relativeMissions = 0;
    Skill relativeSkill;
    bool isEliminated = false;   // set once, at the root, when remove_team happens

    NodeUF() = default;

    NodeUF(int contestantId, int teamId,
        const Skill &skill,int motivation, int missionsHad) :
    contestantId(contestantId), teamId(teamId), skill(skill),
    motivation(motivation), missionsHad(missionsHad) {}

    ~NodeUF() = default;
};

//****************************************************************************//
// Union Find class //
class ContestantsAndTeamsUF {
private:

    HashTable contestantIndex;   // contestant Id --> pointer to NodeUF
//****************************************************************************//
    // helper func //

    //****************************************************************************//

    // inter face //

public:
    ContestantsAndTeamsUF() = default;

    ~ContestantsAndTeamsUF() = default;

    bool addContestantUF(int contestantId, int teamId, const Skill &skill,
        int motivation, int missionsHad);

    // (return ptr to the new root)
    NodeUF* UnionNodes(NodeUF* recruitingRoot, NodeUF* recruitedRoot);

    Skill getEffectiveSkill(int contestantId);

    // checks if he found in the hash table (O(1) in average)
    bool isFound(int contestantId);

    // return ptr to the NodeUF that containing the contestant (O(1) in average)
    NodeUF* getContestantPtr(int contestantId);

    int getMissionNumRec(NodeUF* contestPtr);

    Skill getPartialTeamSkillRec(NodeUF* contestPtr);

    std::pair<int, Skill> getRelativeFieldsRec(NodeUF* contestPtr);
};

#endif //UNIONFIND_H
