#include <iostream>
#include "worker.h"
#include "../world/beehive.h"

using namespace bees;

using std::cout;
using std::endl;


Worker::Worker(Bee::Role role, world::Beehive *beehive) : Bee::Bee(role, beehive) {
    resource_number_ = this->get_Beehive()->roll_dice(1, 6);
    std::cout << "*B* " << this->print_bee() << " is born" << std::endl;
}

int Worker::get_resource_number() const {
    return resource_number_;
}

void Worker::run() {
    while (world::Beehive::is_active) {

        this->get_Beehive()->get_flower_field()->enter_field(this);

//        this->get_Beehive()->get_logger()->log("Gathering resources" + std::to_string(this->get_id()));
        std::this_thread::sleep_for(std::chrono::seconds(resource_number_));

        this->get_Beehive()->get_flower_field()->leave_field(this);


        this->get_Beehive()->get_logger()->log("*BH* " + this->print_bee() + " deposits resources" );
        this->get_Beehive()->get_resource()->deposit(this);

        this->get_Beehive()->get_logger()->log( "*W* " + this->print_bee() + " is refueling");
        unsigned int consumed_resource = this->get_Beehive()->get_resource()->consume_resource(1);

        if (consumed_resource == 0) {
            this->get_Beehive()->get_logger()->log( "*BH* " + this->print_bee() + " perished!" );
            break;
        }


    }

}

std::string Worker::print_bee() {
    return std::string(*this) + "(" + std::to_string(this->resource_number_) + ") WORKER #" + std::to_string(this->get_id());
}


namespace bees {
    std::ostream &operator<<(std::ostream &os, const Worker &worker) {
        return os << std::string(worker) << "(" << worker.resource_number_ << ") WORKER #" << worker.get_id() << endl;
    }
}