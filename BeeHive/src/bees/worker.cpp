#include <iostream>
#include "worker.h"
#include "../world/beehive.h"
using namespace bees;

using std::cout;
using std::endl;

Worker::Worker(Bee::Role type, world::Beehive *beehive): Bee::Bee(type), beehive_(beehive) {
    resource_number_ = beehive_->roll_dice(1,6);
}

void Worker::run() {
    cout << "Worker run method" << endl;
}