
#ifndef UNIONFIND_H
#define UNIONFIND_H

// #include <memory>
#include "HashTable.h"
#include "wet2util.h"


struct NodeUF {
    int contestantId = 0;
    NodeUF* parent = nullptr;
    int size = 0;
    int teamId = 0;
    Skill skill = Skill();
    int missionsHad = 0;
    int RelativeMissionsOff = 0;
    Skill relativeSkill;
    bool isEliminated = false;   // set once, at the root, when remove_team happens

    NodeUF();
    ~NodeUF() = default;
};

class ContestantsAndTeamsUF {
    HashTable contestantIndex;   // contestant Id --> pointer to NodeUF
public:

    ContestantsAndTeamsUF();

    ~ContestantsAndTeamsUF() = default;

    NodeUF* makeSet(int contestantId,
                              int teamId,
                              const Skill &skill,
                              int motivation,
                              int missionsHad);

    NodeUF* Find(int contestantId);

    NodeUF* UnionNodes(NodeUF* recruitingRoot, NodeUF* recruitedRoot); // (return ptr to the new root)

    Skill getEffectiveSkill(int contestantId);

};

#endif //UNIONFIND_H
