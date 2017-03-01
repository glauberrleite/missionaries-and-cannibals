#include<iostream>
#include<vector>
#include"node.h"

using namespace std;

vector<Node> frontier;

bool isDuplicate(Node &node){
  for (int i = 0; i < frontier.size(); ++i)
    if(node.getWorldState() == frontier[i].getWorldState())
      return 1;
  return 0;
}

void printWorldStatus(Node &node){
  for (int i = 0; i < node.getWorldState().size(); ++i)
    cout << node.getWorldState()[i];

  cout << '\n';
}

void printFrontier(){
  for (int i = 0; i < frontier.size(); ++i){
    printWorldStatus(frontier[i]);
    cout << " -- ";
    printWorldStatus(*(frontier[i].getParent()));
  }

  cout << "------\n";
}

Node * extensionSearch(Node &root){
  // Check if node is the solution
  if (root.isSolution())
    return &root;

  // Build successors
  vector<Node> successors = root.buildSuccessors();

  for(int i = 0; i < successors.size(); ++i){
    if(!isDuplicate(successors[i]))
      frontier.push_back(successors[i]);
  }

  // removing the root from the frontier
  frontier.erase(frontier.begin());
  printFrontier();

  // Choose who will be expanded
  return extensionSearch(frontier[0]);
}

void printPath(Node * node){
  if(node != nullptr) {

    printWorldStatus(*node);
    cout << '\n';

    printPath(node->getParent());
  }
}

int main(){

  // initial worldState = {3, 3, 0, 0, 0};

  Node node(nullptr);

  frontier.push_back(node);

  Node * result = extensionSearch(node);

  printWorldStatus(*(result->getParent()));
  //printPath(result);

  cout << "--------\n";
  cout << "Total Depth: ";
  cout << to_string(result->getDepth());
  cout << "\nTotal Cost: ";
  cout << to_string(result->getCost());
  cout << '\n';

  return 0;
}
