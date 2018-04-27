#ifndef FLOWER_FIELD_H
#define FLOWER_FIELD_H

#include <mutex>
#include "../bees/bee.h"
#include "../bees/worker.h"
#include <condition_variable>

namespace world {
    /*
     * A monitor to keep track of the worker bees
     *
     * @author Abdul Hakim Shanavas @ RIT CS
     */
    class FlowerField {
    public:
        /*
         * Create an instance of flower field
         */
        FlowerField();
        /*
         * Method for the worker bee to enter and gather resource.
         * Waits if all the 10 flowers are occupied.
         * @param worker
         */
        void enter_field(bees::Worker *worker);
        /*
         * Routine for the worker bee to leave the flower field
         * and notify other worker bees waiting for the flower
         * @param worker
         */
        void leave_field(bees::Worker *worker);
        /*
         * Maximum number of worker bees which can gather resources at a particular time
         */
        static const unsigned int MAX_WORKER_BEES = 10;

    private:
        std::mutex mtx_;
        std::condition_variable condition_variable_;
        static unsigned int bee_monitor_counter_;

    };
}

#endif