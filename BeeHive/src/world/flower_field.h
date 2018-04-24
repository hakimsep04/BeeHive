#ifndef FLOWER_FIELD_H
#define FLOWER_FIELD_H

#include <mutex>
#include "../bees/bee.h"

namespace world{
    class FlowerField{
    public:

        FlowerField();

        void field(std::unique_ptr<bees::Bee> bee);

        static const unsigned int MAX_WORKER_BEES = 10;

    private:
        std::mutex mtx_;
        std::condition_variable condition_variable_;
        static unsigned int bee_monitor_counter_;


    };
}

#endif