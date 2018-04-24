#include <iostream>
#include "bee.h"
#include "worker.h"

using namespace bees;

using std::cout;
using std::endl;

Bee::Bee(Role role):role_(role) {}

Bee::Role Bee::get_role() const {
    return role_;
}

std::string Bee::operator std::string() const {
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
            return new Worker(role, beehive);
        case POLLEN:
            return new Worker(role, beehive);
    }
}