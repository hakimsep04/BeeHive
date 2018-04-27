#ifndef DRONE_H
#define DRONE_H

#include "../world/beehive.h"

namespace bees {
    /*
     * Drone bee who's fated task is to reproduce with the queen and perish immediately after mating
     *
     * @author Abdul Hakim Shanavas @ RIT CS
     */
    class Drone : public Bee {
    public:
        /*
         * Create drone
         * @param Role role
         *        Beehive beehive
         */
        Drone(Bee::Role role, world::Beehive *beehive);
        /*
         * Routine for drone bee
         */
        void run() override;
        /*
         * Print the role and id of the drone
         */
        std::string print_bee() override;
    };
}


#endif