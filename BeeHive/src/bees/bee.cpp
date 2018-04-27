#include <iostream>
#include "bee.h"
#include "worker.h"
#include "queen.h"
#include "drone.h"

using namespace bees;

using std::cout;
using std::endl;

int Bee::bee_counter_ = 0;
int Bee::perished_bees_ = 0;

Bee::Bee(Role role, world::Beehive *beehive):role_(role), beehive_(beehive), id_{++bee_counter_} {}

Bee::~Bee() {
    perished_bees_++;
}

Bee::Role Bee::get_role() const {
    return role_;
}

int Bee::get_id() const {
    return id_;
}

world::Beehive* Bee::get_Beehive() const {
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
        case QUEEN:
            return std::unique_ptr<bees::Bee>(new Queen(role, beehive));
        case DRONES:
            return std::unique_ptr<bees::Bee>(new Drone(role, beehive));
        case NECTAR:
            return std::unique_ptr<bees::Bee>(new Worker(role, beehive));
        case POLLEN:
            return std::unique_ptr<bees::Bee>(new Worker(role, beehive));
    }
}

int Bee::get_resource_number() const {
    return 0;
}