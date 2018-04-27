#ifndef QUEEN_H
#define QUEEN_H

#include "../world/beehive.h"

namespace bees{
    /*
     * Queen bee mates with the drone bee if certain conditions are met
     * and reproduce more bees randomly between 1 and 5
     *
     * @author Abdul Hakim Shanavas @ RIT CS
     */
    class Queen: public Bee{
    public:
        /*
         * Create queen bee
         * @param Role role
         *        Beehive beehive
         */
        Queen(Bee::Role role, world::Beehive *beehive);
        /*
         * Routine for queen bee to check the condition for mating
         * and mating with drone and reproducing more bees
         */
        void run() override;
        /*
         * Get the string of queen role and it's id
         */
        std::string print_bee() override;


    };
}

#endif