#include "drone.h"

using namespace bees;

Drone::Drone(Bee::Role role, world::Beehive *beehive): Bee::Bee(role, beehive) {
    this->get_Beehive()->get_logger()->log("*B* " + this->print_bee() + " is born");
}

void Drone::run() {
    this->get_Beehive()->get_queens_chamber()->chamber_drone(this);
}

std::string Drone::print_bee() {
    return "DRONE #" + std::to_string(this->get_id());
}