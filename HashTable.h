
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
#include "ContestantsAndTeamsUF.h"


class HashTable {
private:
    // node struct //
    struct HashNode {
        std::unique_ptr<HashNode> next = nullptr;
        std::unique_ptr<NodeUF> value = nullptr;

        HashNode() = default;
        explicit HashNode(NodeUF* contestantPtr) : value(contestantPtr) {};
        ~HashNode() = default;
    };

//****************************************************************************//
    // fields of the HashTable //
    int maxSize = 10;
    int currSize = 0;
    std::unique_ptr<std::unique_ptr<HashNode>[]> ptrTable = nullptr;

//****************************************************************************//
    // helper func //
    int hashFunc(int Id);

    void increaseSize();

//****************************************************************************//
public:
    // inter face //
    HashTable() : ptrTable(std::make_unique<std::unique_ptr<HashNode>[]>(10)) {}

    ~HashTable() = default;

    NodeUF* find(int contestantId);

    bool insert(NodeUF* contestant);
};
#endif //HASHTABLE_H
