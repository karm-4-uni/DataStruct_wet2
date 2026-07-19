#include "ContestantsAndTeamsUF.h"

// helper func //
int HashTable::hashFunc(int Id) {
    return Id % maxSize;
}

void HashTable::increaseSize() {
    int oldMaxSize = maxSize;
    maxSize *= 2;

    auto ptrNewTable = std::make_unique<std::unique_ptr<HashNode>[]>(maxSize);

    // rehash to the new table
    for (int i = 0 ; i < oldMaxSize ; i++) {

        auto curr = std::move(ptrTable[i]);

        while (curr != nullptr) {
            ptrTable[i] = std::move(curr->next); // now the curr->next == nullptr

            int newIndex = hashFunc(curr->value->contestantId);
            // make the old head be the next of curr
            curr->next = std::move(ptrNewTable[newIndex]);
            // set the ptr on the new table pointes to the curr
            ptrNewTable[newIndex] = std::move(curr);

            curr = std::move(ptrTable[i]);
        }
    }

    ptrTable = std::move(ptrNewTable);
}



//*******************************************************************//
// inter face func //
NodeUF* HashTable::find(int contestantId) {
    int index = hashFunc(contestantId);

    HashNode* curr = ptrTable[index].get();

    while (curr != nullptr) {
        if (curr->value->contestantId == contestantId) {
            return curr->value.get();
        }
        curr = curr->next.get();
    }

    // we did not find the contestant
    return nullptr;
}

bool HashTable::insert(NodeUF* contestant) {

    // if the contestant hase been joined before return false
    if (HashTable::find(contestant->contestantId) != nullptr) {
        return false;
    }

    int index = hashFunc(contestant->contestantId);

    auto newHashNode = std::make_unique<HashNode>();
    newHashNode->value = std::move(std::unique_ptr<NodeUF>(contestant));

    // make the old head be the next of the newNode
    newHashNode->next = std::move(ptrTable[index]);

    // set the ptr on the table pointes to the new Node
    ptrTable[index] = std::move(newHashNode);

    currSize++;
    if (maxSize == currSize) {
        increaseSize();
    }

    return true;
}