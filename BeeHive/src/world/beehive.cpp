#include "beehive.h"


using std::thread;
using namespace world;

Beehive::Beehive(unsigned long long seed, unsigned int drones, unsigned int nectar_worker,
                 unsigned int pollen_worker) : num_drones_{drones}, num_nectar_worker_{nectar_worker},
                                               num_pollen_worker_{pollen_worker}, random_(util::random(seed)),
                                               bee_collection_{}, bee_thread_collection_{} {

}

//Beehive::Beehive(unsigned long long seed):random_(util::random(seed)) , bee_collection_{} {
//    for(int i = 0; i < 3; i++){
//        this->add_bee(bees::Bee::createBee(bees::Bee::Role::NECTAR, this));
//    }
//    for(int i = 0; i < 2; i++){
//        this->add_bee(bees::Bee::createBee(bees::Bee::Role::POLLEN, this));
//    }
//}

unsigned int Beehive::roll_dice(unsigned int min, unsigned int max) {
    return random_.roll_dice(min, max);
}

void Beehive::add_bee(std::unique_ptr<bees::Bee> bee) {
    bee_collection_.push_back(bee);
}

void Beehive::start() {
    for (int i = 0; i < bee_collection_.size(); i++) {
        thread{&bees::Bee::run, this};
    }
}

void Beehive::start_simulation() {
    //Bee objects creation

    //Create queen object
    //create drone objects
    for(int i = 0; i< num_drones_; i++){
        //this->add_bee(bees::Bee::createBee(bees::Bee::Role::DRONES, this));
    }

    for(int i = 0; i< num_nectar_worker_; i++){
        this->add_bee(bees::Bee::createBee(bees::Bee::Role::NECTAR, this));
    }

    for(int i = 0; i< num_pollen_worker_; i++){
        this->add_bee(bees::Bee::createBee(bees::Bee::Role::POLLEN, this));
    }

    for(int i =0; i< bee_collection_.size(); i++){
        bee_thread_collection_.push_back(thread{&bees::Bee::run, bee_collection_[i]});
    }


    //Starting threads for each bee object


}

void Beehive::end_simulation() {

}