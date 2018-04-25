#include "beehive.h"


using std::thread;
using namespace world;

bool Beehive::is_active = false;

Beehive::Beehive(unsigned long long seed, unsigned int drones, unsigned int nectar_worker,
                 unsigned int pollen_worker) : num_drones_(drones), num_nectar_worker_(nectar_worker),
                                               num_pollen_worker_(pollen_worker), random_(util::random(seed)),
                                               log_(new util::logger(std::cout)),
                                               bee_collection_(), bee_thread_collection_(),
                                               flower_field_(new world::FlowerField()),
                                               resource_(bees::Resource()) {

    for (unsigned int i = 0; i < num_drones_; i++) {
        //this->add_bee(bees::Bee::createBee(bees::Bee::Role::DRONES, this));
    }

    for (unsigned int i = 0; i < num_nectar_worker_; i++) {
        this->add_bee(bees::Bee::createBee(bees::Bee::Role::NECTAR, this));
    }

    for (unsigned int i = 0; i < num_pollen_worker_; i++) {
        this->add_bee(bees::Bee::createBee(bees::Bee::Role::POLLEN, this));
    }

}

Beehive::~Beehive() {
    delete log_;
    delete flower_field_;
}

unsigned int Beehive::roll_dice(unsigned int min, unsigned int max) {
    return random_.roll_dice(min, max);
}

void Beehive::add_bee(std::unique_ptr<bees::Bee> bee) {
    bee_collection_.push_back(std::move(bee));
}

util::logger* Beehive::get_logger() {
    return log_;
}

world::FlowerField* Beehive::get_flower_field() {
    return flower_field_;
}

bees::Resource& Beehive::get_resource() {
    return resource_;
}

void Beehive::start_simulation() {

    Beehive::is_active = true;
    //Starting threads for each bee object
    for (unsigned int i = 0; i < bee_collection_.size(); i++) {
        bee_thread_collection_.push_back(thread{&bees::Bee::run, std::move(bee_collection_[i])});
    }

}

void Beehive::end_simulation() {
    Beehive::is_active = false;
    for (unsigned int i = 0; i < bee_collection_.size(); i++) {
        bee_thread_collection_[i].join();
    }
}