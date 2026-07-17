//
// Created by Admin on 12/07/2026.
//

#ifndef RANKTREE_H
#define RANKTREE_H





template <typename T, typename S>
struct RankedNode {
    std::shared_ptr<T> data;
    S key;
    RankedNode* parent;
    std::shared_ptr<RankedNode<T,S>>  rightSon;
    std::shared_ptr<RankedNode<T,S>>  leftSon;
    int height;
    int Rank ;
    RankedNode(std::shared_ptr<T> data = nullptr, const S& key = S()): data(data),
    key(key), parent(nullptr), rightSon(nullptr),
    leftSon(nullptr), height(0) ,Rank(1) {};

    ~RankedNode() = default;

    int get_height() const {
        return  height ;
    }
    int get_balnce_factor() const {
        int left , right ;
        if(leftSon == nullptr ) {
            left = -1 ;
        } else {
            left = leftSon->height;
        }
        if( rightSon == nullptr) {
            right = -1;
        } else {
            right = rightSon->height;
        }
        return  left - right  ;
    }
    void add_hight(int add) {
        if(add + height < 0) {
            throw 001;
        }
        height += add;
    }
    void updateHeight() {
        int leftHeight;
        int rightHeight;
        if (leftSon != nullptr) {
            leftHeight = leftSon->height;
        } else {
            leftHeight = -1;
        }
        if (rightSon != nullptr) {
            rightHeight = rightSon->height;
        } else {
            rightHeight = -1;
        }

        height = 1 + std::max(leftHeight, rightHeight);
    }
    bool isleaf() const {
        return  (rightSon == nullptr && leftSon == nullptr);
    }
    int getRank() const  {
        return Rank;
    }
    void setRank() {
        int leftRank = leftSon ? leftSon->getRank() : 0;
        int rightRank = rightSon ? rightSon->getRank() : 0;

        Rank = leftRank + 1 + rightRank;
    }

    void update() {
        setRank();
        updateHeight();
    }
};

template <typename  T ,typename S>
class RankedTree {
    class Iterator;
    using NodePtr = std::shared_ptr<RankedNode<T,S>>;
    NodePtr root;
    int size;

    void insert_recurcion(const std::shared_ptr<T>& data ,const S& key ,
        NodePtr& currTree) {
        if (!currTree) {

            currTree = std::make_shared<RankedNode<T,S>>(data, key);
            return;
        }
        if(key == currTree->key ) {
            throw 1;
        }

        if(key < currTree->key ) {
            if( currTree->leftSon != nullptr) {
                insert_recurcion(data,key,currTree->leftSon);
            } else {
                currTree->leftSon = std::make_shared<RankedNode<T,S>>(data ,key);
                currTree->leftSon->parent = currTree.get();
            }

        }  else  {
            if( currTree->rightSon != nullptr) {
                insert_recurcion(data,key,currTree->rightSon);
            } else {
                currTree->rightSon = std::make_shared<RankedNode<T,S>>(data,key);
                currTree->rightSon->parent = currTree.get();
            }

        }
        balance(currTree);
    }
    bool search_recurcion(const S& key,
        NodePtr& currTree) {
        if(currTree == nullptr  ) {
            return  false ;
        }
        if(key == currTree->key   ) {
            return  true;
        }
        if(key < currTree->key) {
            return   search_recurcion(key,currTree->leftSon);
        } else {
            return   search_recurcion(key,currTree->rightSon);
        }
    }
    NodePtr find_min_recurction(NodePtr& currTree) {
        if (currTree->leftSon == nullptr)
        {
            return currTree;
        } else {
            return find_min_recurction(currTree->leftSon);
        }


    }
    NodePtr findNextGreater(const S& key)
    {
        NodePtr curr = root;
        NodePtr answer = nullptr;

        while (curr != nullptr){
            if (curr->key > key){
                answer = curr;
                curr = curr->leftSon;
            }   else {
                curr = curr->rightSon;
            }
        }

        return answer;
    }
    void remove_recurction(const S& key ,std::shared_ptr<RankedNode<T,S>>& currTree ) {
        if(currTree == nullptr) {
            throw "key not found";
        } else {
            if(key == currTree->key) {
                if(currTree->rightSon == nullptr) {
                    if(currTree->leftSon == nullptr) {
                        currTree = nullptr;
                        // there is one node in the tree

                    } else {
                        RankedNode<T,S>* oldParent = currTree->parent;
                        currTree = currTree->leftSon;
                        currTree->parent = oldParent;
                    }

                } else if(currTree->leftSon == nullptr) {
                    RankedNode<T,S>* oldParent = currTree->parent;
                    currTree = currTree->rightSon;
                    currTree->parent = oldParent;
                } else {
                    std::shared_ptr<RankedNode<T,S>> new_root = find_min_recurction(currTree->rightSon );
                    currTree->key = new_root->key;
                    currTree->data = new_root->data;
                    remove_recurction(new_root->key, currTree->rightSon);
                }
            }
            else if (key < currTree->key) {
                remove_recurction(key, currTree->leftSon);
            }
            else { // key > currTree->key
                remove_recurction(key, currTree->rightSon);
            }
        }
        if (currTree != nullptr) {
            currTree->update();
        }
        balance(currTree);
    }

    T* find_recurction(const S& key ,const std::shared_ptr<RankedNode<T,S>>& currTree) {
        if(currTree == nullptr) {
            return  nullptr;
        } else {
            if( key == currTree->key) {
                return  currTree->data.get();
            } else if(key < currTree->key) {
                return  find_recurction(key , currTree->leftSon);
            } else {
                return  find_recurction(key , currTree->rightSon);
            }
        }
    }
    std::shared_ptr<T> find_recurction_ptr(const S& key ,const std::shared_ptr<RankedNode<T,S>>& currTree) {
        if(currTree == nullptr) {
            return  nullptr;
        } else {
            if( key == currTree->key) {
                return  currTree->data;
            } else if(key < currTree->key) {
                return  find_recurction_ptr(key , currTree->leftSon);
            } else {
                return  find_recurction_ptr(key , currTree->rightSon);
            }
        }
    }

    void LL_rotation(NodePtr& currRoot) {
        if (currRoot == nullptr || currRoot->leftSon == nullptr) return;

        NodePtr oldRoot = currRoot;
        NodePtr newRoot = oldRoot->leftSon;

        //changing the sons
        oldRoot->leftSon = newRoot->rightSon;
        newRoot->rightSon = oldRoot;

        // changing the parents
        newRoot->parent = oldRoot->parent;
        oldRoot->parent = newRoot.get();
        if (oldRoot->leftSon != nullptr) {
            oldRoot->leftSon->parent = oldRoot.get();
        }

        // updating the heights
        oldRoot->update();
        newRoot->update();
        // updating the connection to the tree
        currRoot = newRoot;
    }
    void RR_rotation(NodePtr& currRoot) {
        if (currRoot == nullptr || currRoot->rightSon == nullptr) return;

        NodePtr oldRoot = currRoot;
        NodePtr newRoot = oldRoot->rightSon;

        // changing the sons
        oldRoot->rightSon = newRoot->leftSon;
        newRoot->leftSon = oldRoot;

        // changing the parents
        newRoot->parent = oldRoot->parent;
        oldRoot->parent = newRoot.get();
        if (oldRoot->rightSon != nullptr) {
            oldRoot->rightSon->parent = oldRoot.get();
        }

        oldRoot->update();
        newRoot->update();

        currRoot = newRoot;
    }
    void LR_rotation(NodePtr& currRoot) {
        if (currRoot == nullptr || currRoot->leftSon == nullptr) return;

        RR_rotation(currRoot->leftSon);
        LL_rotation(currRoot);
    }
    void RL_rotation(NodePtr& currRoot) {
        if (currRoot == nullptr || currRoot->rightSon == nullptr) return;

        LL_rotation(currRoot->rightSon);
        RR_rotation(currRoot);
    }
    void balance(NodePtr& currRoot) {
        if (currRoot == nullptr) return;

        currRoot->update();

        int balanceFactor = currRoot->get_balnce_factor();
        if (balanceFactor > 1) {
            if (currRoot->leftSon->get_balnce_factor() >= 0) {
                LL_rotation(currRoot);
            } else {
                LR_rotation(currRoot);
            }
        } else if (balanceFactor < -1) {
            if (currRoot->rightSon->get_balnce_factor() <= 0) {
                RR_rotation(currRoot);
            } else {
                RL_rotation(currRoot);
            }
        }
    }

    void inOrderToArray(const NodePtr& currNode,
                        std::shared_ptr<T>* dataArr, S* keyArr, int& index) const {
        if (currNode == nullptr) {
            return;
        }
        inOrderToArray(currNode->leftSon, dataArr, keyArr, index);

        dataArr[index] = currNode->data;
        keyArr[index] = currNode->key;
        index++;

        inOrderToArray(currNode->rightSon, dataArr, keyArr, index);
    }

    NodePtr sortedArrayToBST(std::shared_ptr<T>* dataArr, S* keyArr,
                             int start, int end, RankedNode<T,S>* parentNode) {
        if (start > end) {
            return nullptr;
        }

        int mid = start + (end - start) / 2;

        NodePtr newNode = std::make_shared<RankedNode<T,S>>(dataArr[mid], keyArr[mid]);
        newNode->parent = parentNode;

        newNode->leftSon = sortedArrayToBST(dataArr, keyArr, start, mid - 1, newNode.get());
        newNode->rightSon = sortedArrayToBST(dataArr, keyArr, mid + 1, end, newNode.get());

        newNode->update();

        return newNode;
    }

    class Iterator {
        friend class RankedTree<T,S>;
        RankedNode<T,S>* curr;
        // inorder Iterator
    public:
        Iterator(RankedNode<T,S>* node = nullptr)
            : curr(node) {}

        T& operator*()
        {
            return *(curr->data);
        }

        Iterator& operator++()
        {
            if(curr == nullptr) { return *this;}

            if(curr->rightSon){
                curr = curr->rightSon.get();
                while(curr->leftSon)
                {
                    curr = curr->leftSon.get();
                }
            } else {
                RankedNode<T,S>* parent = curr->parent;
                while(parent &&
                      curr == parent->rightSon.get())
                {
                    curr = parent;
                    parent = parent->parent;
                }
                curr = parent;
            }

            return *this;
        }

        bool operator==(const Iterator& other) const
        {
            return curr == other.curr;
        }

        bool operator!=(const Iterator& other) const
        {
            return curr != other.curr;
        }
    };
public:
    RankedTree(T* data = nullptr,S key = 0) :root(nullptr), size(0) {
    }
    ~RankedTree() = default ;

    bool insert(const std::shared_ptr<T>& data, const S& key) {
        // need first to search for the value
        // need to do rotate to fix the tree
        if(search_recurcion(key, root)) {
            return false;
        }

        insert_recurcion(data, key, root);
        balance(root);
        size++;
        return  true ;
    }
    bool  search(const S& key ) {
        // check if the date is in the tree
        return  search_recurcion( key,root);
    }
    bool remove(const S& key) {
        if (!search( key)) {
            return  false;
        }
        remove_recurction(key,root);
        balance(root);
        size--;
        return  true;
    }
    T* find(const S& key) {
        return  find_recurction(key ,root);
    }
    std::shared_ptr<T> find_ptr(const S& key)  // return shared ptr
    {
        return  find_recurction_ptr(key ,root);
    }
    NodePtr find_min(S* key = nullptr ) {
        if(root == nullptr) {
            return  nullptr;
        }
       if(key == nullptr) {
               return find_min_recurction(root) ;
       } else {
               return  findNextGreater(*key);
       }

    }
    void printTree_recurction(std::ostream& os,
                   const NodePtr& curr,int depth = 0)
    {
        if (!curr) {
            return;
        }
        for (int i = 0; i < curr->height; i++) {
            os << "  ";
        } os<< *curr->data << '\n';
        printTree_recurction(os, curr->rightSon ,depth + 1);

        for (int i = 0; i <5; i++) {
            os << "  ";
        }
        printTree_recurction(os, curr->leftSon, depth + 1);



    }
    //****************************************************************//
    // print the tree like paramid
    void printPyramid(std::ostream& os) const {
        if (!root) {
            os << "Tree is empty.\n";
            return;
        }

        std::queue<std::shared_ptr<RankedNode<T,S>>> q;
        q.push(root);

        int currentLevel = 0;
        int maxLevel = root->height; // מניח שהגובה מעודכן נכון!

        os << "\n--- AVL Tree Pyramid ---\n\n";

        while (!q.empty() && currentLevel <= maxLevel) {
            int levelNodes = q.size();

            // חישוב הרווח ההתחלתי לשורה הנוכחית (כדי למרכז את הפירמידה)
            int startSpaces = std::pow(2, maxLevel - currentLevel) - 1;
            for (int i = 0; i < startSpaces; i++) {
                os << "   "; // 3 רווחים לכל יחידת מרווח
            }

            for (int i = 0; i < levelNodes; i++) {
                auto curr = q.front();
                q.pop();

                if (curr) {
                    // מדפיסים את המפתח. הוספתי [ ] כדי שייראה כמו צומת
                    os << "[" << curr->key << "]";
                    q.push(curr->leftSon);
                    q.push(curr->rightSon);
                } else {
                    os << "   "; // מקום ריק אם אין צומת
                    q.push(nullptr);
                    q.push(nullptr);
                }

                // חישוב הרווח בין הצמתים באותה שורה
                int betweenSpaces = std::pow(2, maxLevel - currentLevel + 1) - 1;
                for (int j = 0; j < betweenSpaces; j++) {
                    os << "   ";
                }
            }
            os << "\n\n"; // יורדים שורה בסיום כל רמה של העץ
            currentLevel++;
        }
        os << "------------------------\n";
    }
    //****************************************************************//
    void printTree(std::ostream& os) {
        //printTree_recurction(os,root);
        printPyramid(os);
    }
    int getSize() const {
        return  size;
    }
    void mergeWith(const RankedTree<T,S>& otherTree) {
        if (otherTree.root == nullptr) return;

        int size1 = this->size;
        int size2 = otherTree.size;
        int totalSize = size1 + size2;

        auto* data1 = new std::shared_ptr<T>[size1];
        S* keys1 = new S[size1];

        auto* data2 = new std::shared_ptr<T>[size2];
        S* keys2 = new S[size2];

        auto* mergedData = new std::shared_ptr<T>[totalSize];
        S* mergedKeys = new S[totalSize];

        try {
            int index1 = 0;
            inOrderToArray(this->root, data1, keys1, index1);

            int index2 = 0;
            otherTree.inOrderToArray(otherTree.root, data2, keys2, index2);

            int i = 0, j = 0, k = 0;
            while (i < size1 && j < size2) {
                if (keys1[i] < keys2[j]) {
                    mergedData[k] = data1[i];
                    mergedKeys[k] = keys1[i];
                    i++;
                } else {
                    mergedData[k] = data2[j];
                    mergedKeys[k] = keys2[j];
                    j++;
                }
                k++;
            }

            while (i < size1) {
                mergedData[k] = data1[i];
                mergedKeys[k] = keys1[i];
                i++; k++;
            }
            while (j < size2) {
                mergedData[k] = data2[j];
                mergedKeys[k] = keys2[j];
                j++; k++;
            }

            this->root = sortedArrayToBST(mergedData, mergedKeys, 0, totalSize - 1, nullptr);
            this->size = totalSize;

        } catch (...) {
            delete[] data1; delete[] keys1;
            delete[] data2; delete[] keys2;
            delete[] mergedData; delete[] mergedKeys;
            throw; // SegmentationResort
        }

        delete[] data1; delete[] keys1;
        delete[] data2; delete[] keys2;
        delete[] mergedData; delete[] mergedKeys;
    }

    Iterator begin()
    {
        return Iterator(find_min().get());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }


    NodePtr findByRank(int rank) const {
    if (rank < 1 || rank > size) {
        return nullptr;
    }

    NodePtr current = root;

    while (current != nullptr) {
        int leftSize =
            current->leftSon
                ? current->leftSon->getRank()
                : 0;

        if (rank == leftSize + 1) {
            return current;
        }

        if (rank <= leftSize) {
            current = current->leftSon;
        } else {
            rank -= leftSize + 1;
            current = current->rightSon;
        }
    }

    return nullptr;
}



};

template<typename T, typename S>
  std::ostream& operator<<(std::ostream& os,
                         RankedTree<T,S>& tree)
{
    tree.printTree(os);
    return os;
}
#endif //RANKTREE_H