#include<vector>
#include"action.h"

class Node {
  public:
    Node(Node * parent = nullptr, Action action = ML);
    int getCost();
    int getDepth();
    Node * getParent();
    bool isSolution();
    std::vector<int> getWorldState();
    std::vector<Node *> buildSuccessors();
    bool isValid();
  private:
    Node * parent;
    std::vector<int> worldState;
    int cost;
    int depth;

};
