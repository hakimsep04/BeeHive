#include "flower_field.h"
#include "beehive.h"

using namespace world;

unsigned int FlowerField::bee_monitor_counter_ = 0;

FlowerField::FlowerField() : mtx_{}, condition_variable_{} {}


void FlowerField::enter_field(bees::Worker *worker) {
    worker->get_Beehive()->get_logger()->log("*FF* " + worker->print_bee() + " enters field");
    std::unique_lock<std::mutex> lck{mtx_};
    if (bee_monitor_counter_ >= MAX_WORKER_BEES) {
        //Worker bees if the limit of 10 workers at once in the field is reached
        condition_variable_.wait(lck);
    }
    bee_monitor_counter_++;
}

void FlowerField::leave_field(bees::Worker *worker) {
    {
        std::lock_guard<std::mutex> lg{mtx_};
        bee_monitor_counter_--;
    }
    condition_variable_.notify_one();
    worker->get_Beehive()->get_logger()->log("*FF* " + worker->print_bee() + " leaves field");
}
