#ifndef FLOWER_FIELD_H
#define FLOWER_FIELD_H

#include <mutex>
#include "../bees/bee.h"
#include "../bees/worker.h"

namespace world{
    class FlowerField{
    public:

        FlowerField();

//        void field(bees::Worker* worker);

        void enter_field(bees::Worker* worker);
        void leave_field(bees::Worker* worker);

        static const unsigned int MAX_WORKER_BEES = 10;

    private:
        std::mutex mtx_;
        std::condition_variable condition_variable_;
        static unsigned int bee_monitor_counter_;

    };
}

#endif