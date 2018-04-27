#include "drone.h"

using namespace bees;

Drone::Drone(Bee::Role role, world::Beehive *beehive): Bee::Bee(role, beehive) {
    std::cout << "*B* " << this->print_bee() << " is born" << std::endl;
}

void Drone::run() {
    this->get_Beehive()->get_queens_chamber()->chamber_drone(this);
    this->get_Beehive()->get_logger()->log( "*BH* " + this->print_bee() + " perished!" );
}

std::string Drone::print_bee() {
    return "DRONE #" + std::to_string(this->get_id());
}

namespace  bees{
    std::ostream& operator<<(std::ostream &os, const Drone &drone) {
        return os << "DRONE #" << drone.get_id() << std::endl;
    }
}