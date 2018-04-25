#include "flower_field.h"
#include "beehive.h"

using namespace world;

unsigned int FlowerField::bee_monitor_counter_ = 0;

FlowerField::FlowerField() : mtx_{}, condition_variable_{} {}

//void FlowerField::field(bees::Worker *worker) {
//    worker->get_Beehive()->get_logger().log("Enter field");
//    bee_monitor_counter_++;
//    if (bee_monitor_counter_ > MAX_WORKER_BEES) {
//        std::unique_lock<std::mutex> lck{mtx_};
//        worker->get_Beehive()->get_logger().log("Reached max number in flower field and waiting");
//        condition_variable_.wait(lck);
//    }
//    worker->get_Beehive()->get_logger().log("Gathering resources" + std::to_string(bee_monitor_counter_));
//    std::this_thread::sleep_for(std::chrono::seconds(worker->get_resource_number()));
//
//    {
//        std::lock_guard<std::mutex> lg{mtx_};
//        bee_monitor_counter_--;
//        condition_variable_.notify_one();
//    }
//    worker->get_Beehive()->get_logger().log("Leaving field");
//}


void FlowerField::enter_field(bees::Worker *worker) {
    worker->get_Beehive()->get_logger()->log("Entering field" + std::to_string(worker->get_id()));
    std::unique_lock<std::mutex> lck{mtx_};
    if (bee_monitor_counter_ > MAX_WORKER_BEES) {
        worker->get_Beehive()->get_logger()->log(
                "Reached max number in flower field and waiting" + std::to_string(worker->get_id()) + " #" +
                std::to_string(bee_monitor_counter_));
        condition_variable_.wait(lck);
    }
    bee_monitor_counter_++;
}

void FlowerField::leave_field(bees::Worker *worker) {
    std::lock_guard<std::mutex> lg{mtx_};
    bee_monitor_counter_--;
    condition_variable_.notify_one();
    worker->get_Beehive()->get_logger()->log("Leaving field" + std::to_string(worker->get_id()) + " #" + std::to_string(bee_monitor_counter_));
}
