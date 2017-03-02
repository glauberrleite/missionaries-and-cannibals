#include"node.h"

#include<iostream>

using namespace std;

int Node::getCost() {
  return this->cost;
}

int Node::getDepth() {
  return this->depth;
}

Node * Node::getParent(){
  return this->parent;
}

bool Node::isSolution() {
  if(this->worldState[0] == 0 &&
  this->worldState[1] == 0 &&
  this->worldState[2] == 3 &&
  this->worldState[3] == 3)
    return 1;
  return 0;
}

bool Node::isValid() {
  // Main Conditions
  if((this->worldState[0] != 0) &&
    (this->worldState[0] < this->worldState[1]))
    return 0;

  if((this->worldState[2] != 0) &&
    (this->worldState[2] < this->worldState[3]))
    return 0;

  // Avoid strange results
  for (int i = 0; i < 4; ++i)
    if(this->worldState[i] < 0 || this->worldState[i] > 3)
      return 0;

  // Trimming
  if((this->getDepth() >= 2) &&
    (this->worldState == this->parent->getParent()->getWorldState()))
    return 0;

  return 1;
}

std::vector<int> Node::getWorldState(){
  return this->worldState;
}

std::vector<Node *> Node::buildSuccessors(){

  std::vector<Node *> successors;

  int shipSide = this->worldState[4];

  Action start, end;
  if(shipSide == 0){
     // Ship is at left margin
     start = MR;
     end = MCR;

  } else {
    // Ship is at right margin
    start = ML;
    end = MCL;
  }

  for (unsigned int action = start; action <= end; ++action) {
    Node * candidate = new Node(this, static_cast<Action>(action));

    if(candidate->isValid()){
      successors.push_back(candidate);
    }
  }

  return successors;
}

Node::Node(Node * parent, Action action){

  this->parent = parent;

  if(parent == nullptr){

    this->worldState = {3, 3, 0, 0, 0};
    this->cost = 0;
    this->depth = 0;


  } else {

    this->worldState = parent->getWorldState();

    // Moving ship
    switch (action) {
      case ML ... MCL:
        this->worldState[4] = 0;
        break;
      case MR ... MCR:
        this->worldState[4] = 1;
        break;
      }

    // Moving people
    switch (action) {
      case ML: {
        this->worldState[0] += 1;
        this->worldState[2] -= 1;
        break;
      }
      case MML: {
        this->worldState[0] += 2;
        this->worldState[2] -= 2;
        break;
      }
      case CL: {
        this->worldState[1] += 1;
        this->worldState[3] -= 1;
        break;
      }
      case CCL: {
        this->worldState[1] += 2;
        this->worldState[3] -= 2;
        break;
      }
      case MCL: {
        this->worldState[0] += 1;
        this->worldState[1] += 1;
        this->worldState[2] -= 1;
        this->worldState[3] -= 1;
        break;
      }
      case MR: {
        this->worldState[0] -= 1;
        this->worldState[2] += 1;
        break;
      }
      case MMR: {
        this->worldState[0] -= 2;
        this->worldState[2] += 2;
        break;
      }
      case CR: {
        this->worldState[1] -= 1;
        this->worldState[3] += 1;
        break;
      }
      case CCR: {
        this->worldState[1] -= 2;
        this->worldState[3] += 2;
        break;
      }
      case MCR: {
        this->worldState[0] -= 1;
        this->worldState[1] -= 1;
        this->worldState[2] += 1;
        this->worldState[3] += 1;
        break;
      }
    }

    this->cost = parent->getCost() + 1;
    this->depth = parent->getDepth() + 1;

  }

}
