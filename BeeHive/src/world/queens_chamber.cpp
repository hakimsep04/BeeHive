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
    }
    drone_bee_collection_.pop_front();
    drone->get_Beehive()->get_logger()->log( "*QC* " + drone->print_bee() + " leaves chamber");

}

void Queens_Chamber::chamber_queen() {
    is_queen_ready_ = true;
    queue_condition_variable_.notify_all();
//    queen->get_Beehive()->get_logger()->log("*QC* Queen mates with " );
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Queens_Chamber::free_drone_bees() {
    is_queen_ready_ = true;
    while(!drone_bee_collection_.empty()){
//        std::cout << "queen trying to release :" <<drone_bee_collection_.size() << std::endl;
        queue_condition_variable_.notify_all();
    }
}

int Queens_Chamber::get_num_drone_bees() const {
    return static_cast<int>(drone_bee_collection_.size());
}

