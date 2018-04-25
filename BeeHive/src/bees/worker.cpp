#include <iostream>
#include "worker.h"
#include "../world/beehive.h"
using namespace bees;

using std::cout;
using std::endl;

Worker::Worker(Bee::Role role, world::Beehive *beehive): Bee::Bee(role, beehive) {
    resource_number_ = this->get_Beehive()->roll_dice(1,6);
}

int Worker::get_resource_number() const {
    return resource_number_;
}

void Worker::run() {
    while(world::Beehive::is_active){

        this->get_Beehive()->get_flower_field()->enter_field(this);

        this->get_Beehive()->get_logger()->log("Gathering resources" + std::to_string(this->get_id()));
        std::this_thread::sleep_for(std::chrono::seconds(resource_number_));

        this->get_Beehive()->get_flower_field()->leave_field(this);

        this->get_Beehive()->get_logger()->log("depositing resources" + std::to_string(this->get_id()));
        this->get_Beehive()->get_resource().deposit(this);

        unsigned int consumed_resource = this->get_Beehive()->get_resource().consume_resource(1);

        if(consumed_resource == 0){
            this->get_Beehive()->get_logger()->log("Perished" + std::to_string(this->get_id()));
            break;
        }

    }

}