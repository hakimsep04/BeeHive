#include <iostream>
#include "worker.h"
#include "../world/beehive.h"

using namespace bees;

using std::cout;
using std::endl;


Worker::Worker(Bee::Role role, world::Beehive *beehive) : Bee::Bee(role, beehive), resource_number_{} {
    resource_number_ = this->get_Beehive()->roll_dice(1, 6);
    this->get_Beehive()->get_logger()->log("*B* " + this->print_bee() + " is born");
}

int Worker::get_resource_number() const {
    return resource_number_;
}

void Worker::run() {
    while (world::Beehive::is_active) {
        //Worker enters flower field to gather resource
        this->get_Beehive()->get_flower_field()->enter_field(this);
        //Worker sleeps for (# of resources it has to gather) eg., 3 seconds for gathering 3 resources
        std::this_thread::sleep_for(std::chrono::seconds(resource_number_));
        //Worker leaves the flower field and notifies the worker bee waiting to enter flower field
        this->get_Beehive()->get_flower_field()->leave_field(this);

        //Worker bee deposits the resource int beehive it gathered
        this->get_Beehive()->get_logger()->log("*BH* " + this->print_bee() + " deposits resources");
        this->get_Beehive()->get_resource()->deposit(this);

        //Worker attempts to refuel itself before it gathers resource again
        this->get_Beehive()->get_logger()->log("*W* " + this->print_bee() + " is refueling");
        unsigned int consumed_resource = this->get_Beehive()->get_resource()->consume_resource(1);

        //If worker does not consume enough resource to continue working, it perishes immediately
        if (consumed_resource == 0) {
            this->get_Beehive()->get_logger()->log("*BH* " + this->print_bee() + " perished!");
            this->get_Beehive()->add_perished_bees(this->print_bee());
            break;
        }

    }

}

std::string Worker::print_bee() {
    return std::string(*this) + "(" + std::to_string(this->resource_number_) + ") WORKER #" +
           std::to_string(this->get_id());
}