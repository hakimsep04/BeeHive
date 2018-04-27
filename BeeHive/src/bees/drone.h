#ifndef DRONE_H
#define DRONE_H

#include "../world/beehive.h"

namespace bees{
    class Drone:public Bee{
    public:
        Drone(Bee::Role role, world::Beehive *beehive);
        void run() override;

        std::string print_bee() override;

    private:
        friend std::ostream &operator << (std::ostream &os, const Drone &drone);
    };
}


#endif