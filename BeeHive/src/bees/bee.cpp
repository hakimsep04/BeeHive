#include <iostream>
#include "bee.h"
#include "worker.h"

using namespace bees;

using std::cout;
using std::endl;

Bee::Bee(Role role, world::Beehive *beehive):role_(role), beehive_(beehive) {}

Bee::~Bee() {}

Bee::Role Bee::get_role() const {
    return role_;
}

world::Beehive* Bee::get_Beehive() {
    return beehive_;
}

Bee::operator std::string() const {
    switch (role_){
        case QUEEN:
            return "QUEEN";
        case DRONES:
            return "DRONES";
        case NECTAR:
            return "NECTAR";
        case POLLEN:
            return "POLLEN";

    }
}

std::unique_ptr<Bee> Bee::createBee(Role role, world::Beehive *beehive) {
    switch (role){
        case NECTAR:
            return std::unique_ptr<bees::Bee>(new Worker(role, beehive));
        case POLLEN:
            return std::unique_ptr<bees::Bee>(new Worker(role, beehive));
    }
}