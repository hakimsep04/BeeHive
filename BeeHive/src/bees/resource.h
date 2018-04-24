#ifndef RESOURCE_H
#define RESOURCE_H

#include "worker.h"

namespace bees{
    class Resource{
    public:
        Resource();

        void deposit(bees::Worker* worker);

        unsigned int get_nectar_gathered() const;

        unsigned int get_pollen_gathered() const;

        unsigned int get_total_nectar() const;

        unsigned int get_total_pollen() const;

        unsigned int consume_resource(unsigned int claim);

    private:
        unsigned int nectar_gathered_;
        unsigned int pollen_gathered_;
        unsigned int total_nectar_gathered_;
        unsigned int total_pollen_gathered_;
    };
}

#endif