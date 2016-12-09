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

    virtual ~RandomGanerator();

private:
    std::vector<float> *randVec;

    float getNextReadFloat();


};

#endif /* RANDOMGANERATOR_H */

