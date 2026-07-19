
#ifndef UNIONFIND_H
#define UNIONFIND_H

// #include <memory>
#include "HashTable.h"
#include "wet2util.h"
#include <utility>
#include "NodeUF.h"

//*************************************************************************//
// nodes for UF class evry node for one contestant //


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

    std::pair<int, Skill> getRelativeFieldsRec(NodeUF* contestPtr);
};

#endif //UNIONFIND_H
