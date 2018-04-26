#include "drone.h"

using namespace bees;

Drone::Drone(Bee::Role role, world::Beehive *beehive): Bee::Bee(role, beehive) {}

void Drone::run() {
    this->get_Beehive()->get_queens_chamber()->chamber_drone(this);
}

namespace  bees{
    std::ostream& operator<<(std::ostream &os, const Drone &drone) {
        return os << "DRONE #" << drone.get_id() << std::endl;
    }
}