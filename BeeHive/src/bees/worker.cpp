#include <iostream>
#include "worker.h"
#include "../world/beehive.h"
using namespace bees;

using std::cout;
using std::endl;

bool Worker::active_ = true;
int Worker::counter_ = 0;

Worker::Worker(Bee::Role role, world::Beehive *beehive): Bee::Bee(role, beehive) {
    resource_number_ = this->get_Beehive()->roll_dice(1,6);
}

int Worker::get_resource_number() const {
    return resource_number_;
}

void Worker::run() {
    while(active_){

        this->get_Beehive()->get_flower_field().enter_field(this);

        this->get_Beehive()->get_logger().log("Gathering resources" + std::to_string(this->get_id()));
        std::this_thread::sleep_for(std::chrono::seconds(resource_number_));

        this->get_Beehive()->get_flower_field().leave_field(this);

        this->get_Beehive()->get_logger().log("depositing resources" + std::to_string(this->get_id()));

        counter_++;
        if(counter_ == 8){
            active_ = false;
            cout << "Worker halts" << endl;
        }

    }

}