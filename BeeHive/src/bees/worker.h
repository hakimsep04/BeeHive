#ifndef WORKER_H
#define WORKER_H

#include "bee.h"

namespace bees{
    class Worker: public Bee {
    public:
        Worker(Bee::Role role, world::Beehive *beehive);

        void run() override;


    private:

        int resource_number_;
    };
}

#endif