//
// Created by Admin on 19/07/2026.
//

#ifndef NODEUF_H
#define NODEUF_H
struct NodeUF {
    int contestantId = 0;
    int teamId = 0;
    NodeUF* parent = nullptr;
    int size = 0;                 // used for the union (to ensure O(log*n))
    const Skill skill = Skill::identity();
    int motivation = 0;
    int missionsHad = 0;
    int relativeMissions = 0;
    Skill relativeSkill = Skill::identity();
    bool isEliminated = false;   // set once, at the root, when remove_team happens

    NodeUF() = default;

    NodeUF(int contestantId, int teamId,
        const Skill &skill,int motivation, int missionsHad) :
    contestantId(contestantId), teamId(teamId), skill(skill),
    motivation(motivation), missionsHad(missionsHad) {}

    ~NodeUF() = default;
};
#endif //NODEUF_H
