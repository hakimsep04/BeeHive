#include "queens_chamber.h"

using namespace world;

Queens_Chamber::Queens_Chamber():queue_mtx_{},
                                 queue_condition_variable_{},
                                 drone_bee_collection_{},
                                 is_queen_ready_{false} {}

void Queens_Chamber::chamber_drone(bees::Drone *drone) {
    drone->get_Beehive()->get_logger()->log( "*QC* " + drone->print_bee() + " enters chamber");
    {
        std::unique_lock<std::mutex> ul{queue_mtx_};
        drone_bee_collection_.push_back(drone);
        //Drone waits till the queen is ready and passes the lock if it is the first in the queue
        queue_condition_variable_.wait(ul, [&]{
            if(is_queen_ready_){
                return drone->get_id() == drone_bee_collection_[0]->get_id();
            }
        });
    }
    if(world::Beehive::is_active){
        drone->get_Beehive()->get_logger()->log("*QC* Queen mates with " + drone->print_bee());
        std::this_thread::sleep_for(std::chrono::seconds(2));
        is_queen_ready_ = false;
        drone->get_Beehive()->get_logger()->log( "*BH* " + drone->print_bee() + " perished!" );
        drone->get_Beehive()->add_perished_bees(drone->print_bee());
    }
    //Drone bee which is going to perish removes itself from the queue
    drone_bee_collection_.pop_front();
    drone->get_Beehive()->get_logger()->log( "*QC* " + drone->print_bee() + " leaves chamber");

}

void Queens_Chamber::chamber_queen() {
    is_queen_ready_ = true;
    //Queen notifies and release the first drone in the queue and mates with the drone
    queue_condition_variable_.notify_all();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Queens_Chamber::free_drone_bees() {
    is_queen_ready_ = true;
    while(!drone_bee_collection_.empty()){
        queue_condition_variable_.notify_all();
    }
}

int Queens_Chamber::get_num_drone_bees() const {
    return static_cast<int>(drone_bee_collection_.size());
}

