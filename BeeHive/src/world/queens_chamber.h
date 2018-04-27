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
    /*
     * A sophisticated monitor which facilitates the reproduction of Queen and Drone bees
     *
     * @author Abdul Hakim Shanavas @ RIT CS
     */
    class Queens_Chamber {
    public:
        /*
         * Create an instance of queen's chamber
         */
        Queens_Chamber();
        /*
         * Routine through which the drone bees enter the chamber
         * and adds itself to the queue and waits till the queen is ready to mate
         * @param drone
         */
        void chamber_drone(bees::Drone *drone);
        /*
         * Routine for the queen to acces the chamber
         * and release the first drone in the queue to mate
         */
        void chamber_queen();
        /*
         * Routine for releasing all the drone bees which has not mated with the queen
         */
        void free_drone_bees();
        /*
         * Get the number of drones waiting to mate with the queen
         * @return # drones in queue
         */
        int get_num_drone_bees() const;

    private:
        std::mutex queue_mtx_;
        std::condition_variable queue_condition_variable_;
        std::deque<bees::Drone *> drone_bee_collection_;
        bool is_queen_ready_;
    };
}

#endif