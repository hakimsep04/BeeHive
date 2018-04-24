#include <iostream>
#include "worker.h"
#include "../world/beehive.h"
using namespace bees;

using std::cout;
using std::endl;

Worker::Worker(Bee::Role role, world::Beehive *beehive): Bee::Bee(role, beehive) {
    resource_number_ = this->get_Beehive()->roll_dice(1,6);
}

void Worker::run() {
    cout << "Worker run method" << endl;
}