#include "queens_chamber.h"

using namespace world;

Queens_Chamber::Queens_Chamber():queue_mtx_{},
                                 queue_condition_variable_{},
                                 drone_bee_collection_{},
                                 is_queen_ready_{false} {}

void Queens_Chamber::chamber_drone(bees::Drone *drone) {
    {
        std::unique_lock<std::mutex> ul{queue_mtx_};
        drone_bee_collection_.push_back(drone);
        queue_condition_variable_.wait(ul, [&]{
            if(is_queen_ready_){
                return drone->get_id() == drone_bee_collection_[0]->get_id();
            }
        });
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    is_queen_ready_ = false;
    drone_bee_collection_.pop_front();
    drone->get_Beehive()->get_logger()->log("Passed the lock on drone");

}

void Queens_Chamber::chamber_queen(bees::Queen *queen) {
    is_queen_ready_ = true;
    queue_condition_variable_.notify_all();
    queen->get_Beehive()->get_logger()->log("Queen mating");
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Queens_Chamber::free_drone_bees(bees::Queen *queen) {
    while(!drone_bee_collection_.empty()){
        queue_condition_variable_.notify_all();
    }
}

int Queens_Chamber::get_num_drone_bees() const {
    return static_cast<int>(drone_bee_collection_.size());
}

