#ifndef WORKER_H
#define WORKER_H

#include "bee.h"
#include <mutex>


namespace bees {
    /*
     * Each worker bee is responsible for gathering either nectar or pollen resource
     * randomly between 1 and 6 units and deposit into the beehive
     *
     * @author Abdul Hakim Shanavas @ RIT CS
     */
    class Worker : public Bee {
    public:
        /*
         * Create worker bee
         * @param Role role
         *        Beehive beehive
         */
        Worker(Bee::Role role, world::Beehive *beehive);
        /*
         * Routine for worker bee to enter flower field
         * and gather resource and deposit it into beehive
         */
        void run() override;
        /*
         * Get the resource number allocated for the worker bee
         * @return # resource allocated
         */
        int get_resource_number() const override;
        /*
         * Get the worker bee role, resource # allocated and unique id
         */
        std::string print_bee() override;

    private:
        int resource_number_;
    };
}

#endif