#ifndef RANDOMGANERATOR_H
#define RANDOMGANERATOR_H

#include <utility>
#include <vector>

class RandomGanerator {
public:
    RandomGanerator();

    RandomGanerator(char *file);

    int *getRandomArray();

    std::pair<int, int> getRandomPair();

    int getRandomInt();

    double getRandomDouble();

    int getRandomCity();

    int getRandomPosition();

    int getRandomCross();

    virtual ~RandomGanerator();

private:
    std::vector<double> *randVec;

    double getNextReadFloat();


};

#endif /* RANDOMGANERATOR_H */

