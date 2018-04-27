#ifndef RESOURCE_H
#define RESOURCE_H

#include "worker.h"
#include <mutex>

namespace bees{
    /*
     * # Nectar resource and # Pollen resource
     *
     * @author Abdul Hakim Shanavas @ RIT CS
     */
    class Resource{
    public:
        /*
         * Create an instance of resource for managing resources
         */
        Resource();
        /*
         * Depositing the gathered resources by worker bees
         * @param worker bee
         */
        void deposit(bees::Worker* worker);
        /*
         * Get the remaining nectar excluding the cosumed resource
         * @return nectar remaining
         */
        unsigned int get_nectar_gathered() const;
        /*
         * Get the remaining pollen excluding the consumed resurce
         * @return pollen remaining
         */
        unsigned int get_pollen_gathered() const;
        /*
         * Get the total nectar gathered by the worker bees including the consumed resource
         * @return total nectar gathered
         */
        unsigned int get_total_nectar() const;
        /*
         * Get the total pollen gathered by the worker bees including the consumed resource
         * @return total pollen gathered
         */
        unsigned int get_total_pollen() const;
        /*
         * Claim resource to consume and returns if the resource is available
         * @return available pair of nectar and pollen
         */
        unsigned int consume_resource(unsigned int claim);

    private:
        unsigned int nectar_gathered_;
        unsigned int pollen_gathered_;
        unsigned int total_nectar_gathered_;
        unsigned int total_pollen_gathered_;
        std::mutex mtx_;
    };
}

#endif