#include <iostream>
#include "worker.h"
#include "../world/beehive.h"

using namespace bees;

using std::cout;
using std::endl;


Worker::Worker(Bee::Role role, world::Beehive *beehive) : Bee::Bee(role, beehive) {
    resource_number_ = this->get_Beehive()->roll_dice(1, 6);
    this->get_Beehive()->get_logger()->log("*B* " + this->print_bee() + " is born");
}

int Worker::get_resource_number() const {
    return resource_number_;
}

void Worker::run() {
    while (world::Beehive::is_active) {

        this->get_Beehive()->get_flower_field()->enter_field(this);

        std::this_thread::sleep_for(std::chrono::seconds(resource_number_));

        this->get_Beehive()->get_flower_field()->leave_field(this);


        this->get_Beehive()->get_logger()->log("*BH* " + this->print_bee() + " deposits resources");
        this->get_Beehive()->get_resource()->deposit(this);

        this->get_Beehive()->get_logger()->log("*W* " + this->print_bee() + " is refueling");
        unsigned int consumed_resource = this->get_Beehive()->get_resource()->consume_resource(1);

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