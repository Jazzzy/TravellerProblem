//
// Created by Rubén Osorio López on 13/12/16.
//

#include "ListOfNeighbours.hpp"

ListOfNeighbours::ListOfNeighbours() {

    this->firstElement = nullptr;

}

ListOfNeighbours::~ListOfNeighbours() {
//    SolutionNode *auxNode;
//    SolutionNode *currentNode = this->firstElement;
//    while (currentNode != nullptr) {
//        auxNode = currentNode;
//        currentNode = currentNode->next;
//        free(auxNode);
//    }

}

Solution *ListOfNeighbours::getSolutionAt(int position) {
    SolutionNode *currentNode = this->firstElement;
    for (int i = 0; i < position; ++i) {
        currentNode = currentNode->next;
    }

    //cout << "Returning solution at position: " << position << endl;
    return currentNode->solution;
}

void ListOfNeighbours::insertSolution(Solution *solution) {

    if (this->firstElement == nullptr) {
        this->firstElement = (SolutionNode *) malloc(sizeof(SolutionNode));
        this->firstElement->solution = solution;
        this->firstElement->next = nullptr;
        return;
    }

    SolutionNode *newNode = (SolutionNode *) malloc(sizeof(SolutionNode));
    newNode->solution = solution;

    if (this->firstElement->solution->getCost() > newNode->solution->getCost()) {
        SolutionNode *auxNode = this->firstElement;
        this->firstElement = newNode;
        this->firstElement->next = auxNode;
        return;
    }

    SolutionNode *currentNode = this->firstElement;
    SolutionNode *nextNode = currentNode->next;
    while (nextNode != nullptr && nextNode->solution->getCost() < solution->getCost()) {
        currentNode = currentNode->next;
        nextNode = nextNode->next;
    }

    currentNode->next = newNode;
    newNode->next = nextNode;


}

void ListOfNeighbours::printSolutions() {

    SolutionNode *currentNode = this->firstElement;
    while (currentNode != nullptr) {
        cout << "PAIR: " << currentNode->solution->getGenePair().first << ","
             << currentNode->solution->getGenePair().second << "With cost" << currentNode->solution->getCost() << endl;
        currentNode = currentNode->next;
    }


}

void ListOfNeighbours::deleteAllBut(Solution *dontDelete) {

    SolutionNode *auxNode;
    SolutionNode *currentNode = this->firstElement;
    while (currentNode != nullptr) {
        auxNode = currentNode;
        currentNode = currentNode->next;
        if (dontDelete != auxNode->solution) {
            delete auxNode->solution;
        }
        free(auxNode);
    }

}
