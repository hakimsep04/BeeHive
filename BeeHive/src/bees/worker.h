#ifndef WORKER_H
#define WORKER_H

#include "bee.h"
#include <mutex>


namespace bees{
    class Worker: public Bee {
    public:
        Worker(Bee::Role role, world::Beehive *beehive);

        void run() override;

        int get_resource_number() const override;

    private:
        friend std::ostream &operator << (std::ostream &os, const Worker &worker);

    private:
        int resource_number_;




    };
}

#endif