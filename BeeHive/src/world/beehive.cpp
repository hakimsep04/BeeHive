#include "beehive.h"


using std::thread;
using namespace world;
using std::cout;
using std::endl;

bool Beehive::is_active = false;

Beehive::Beehive(unsigned long long seed, unsigned int drones, unsigned int nectar_worker,
                 unsigned int pollen_worker) : num_drones_(drones), num_nectar_worker_(nectar_worker),
                                               num_pollen_worker_(pollen_worker), random_(util::random(seed)),
                                               log_(new util::logger(std::cout)),
                                               bee_collection_(), bee_thread_collection_(),
                                               flower_field_(new world::FlowerField()),
                                               resource_(new bees::Resource()),
                                               queens_chamber_(new world::Queens_Chamber()) {

    this->add_bee(bees::Bee::createBee(bees::Bee::Role::QUEEN, this));

    for (unsigned int i = 0; i < num_drones_; i++) {
        this->add_bee(bees::Bee::createBee(bees::Bee::Role::DRONES, this));
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
    delete resource_;
    delete queens_chamber_;
}

std::deque<std::unique_ptr<bees::Bee>>* Beehive::get_bees() {
    return &bee_collection_;
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

bees::Resource* Beehive::get_resource() {
    return resource_;
}

world::Queens_Chamber* Beehive::get_queens_chamber() {
    return queens_chamber_;
}

void Beehive::add_bee_thread(std::unique_ptr<bees::Bee> bee) {
    bee_thread_collection_.emplace_back(thread{&bees::Bee::run, std::move(bee)});
}

void Beehive::start_simulation() {
    std::cout << "*BH* Beehive begins buzzing!" << std::endl;
    Beehive::is_active = true;
    //Starting threads for each bee object
    for (unsigned int i = 0; i < bee_collection_.size(); i++) {
        bee_thread_collection_.emplace_back(thread{&bees::Bee::run, std::move(bee_collection_[i])});
    }
}

void Beehive::end_simulation() {
    Beehive::is_active = false;
    for (unsigned int i = 0; i < bee_thread_collection_.size(); i++) {
        if(bee_thread_collection_[i].joinable()){
            bee_thread_collection_[i].join();
        }
    }
    std::cout << "*BH* Beehive stops buzzing!" << std::endl;
}