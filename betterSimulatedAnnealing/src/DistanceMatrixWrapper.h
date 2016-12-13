#ifndef DISTANCEMATRIXWRAPPER_H
#define DISTANCEMATRIXWRAPPER_H



#define MU 0.005

void initWrapper();

float getWeightedCost(unsigned int x, unsigned int y);

void addFrec(unsigned int x, unsigned int y);

void destroyWrapper();

double frecParameter();

#endif //TRAVELLERPROBLEM_BETTERTABUSEARCH_DISTANCEMATRIXWRAPPER_H
