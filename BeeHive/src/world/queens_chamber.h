#ifndef QUEENS_CHAMBER_H
#define QUEENS_CHAMBER_H

#include <mutex>
#include "../bees/drone.h"
#include "../bees/queen.h"

namespace bees {
    class Drone;

    class Queen;
}

namespace world {
    class Queens_Chamber {
    public:
        Queens_Chamber();

        void chamber_drone(bees::Drone *drone);

        void chamber_queen();

        void free_drone_bees();

        int get_num_drone_bees() const;

    private:
        std::mutex queue_mtx_;
        std::condition_variable queue_condition_variable_;
        std::deque<bees::Drone *> drone_bee_collection_;
        bool is_queen_ready_;
    };
}

#endif