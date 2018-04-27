#ifndef BEEHIVE_H
#define BEEHIVE_H

#include <deque>
#include "../util/random.h"
#include "../util/logger.h"
#include "../bees/bee.h"
#include "flower_field.h"
#include "../bees/resource.h"
#include "queens_chamber.h"
#include <thread>

namespace world{
    class Queens_Chamber;
}

namespace world{
    /*
     * A central class responsible for
     * 1. Creating and managing the bees
     * 2. Creating flower field and queen's chamber for the bees to access
     * 3. Thread safe routines for managing resources
     * 4. Instance of thread safe logger for printing messages
     *
     * @author Abdul Hakim Shanavas @ RIT CS
     */
    class Beehive{
    public:
        /*
         * Create beehive
         * @param seed
         *        # drones
         *        # nectar_worker
         *        # pollen_worker
         */
        Beehive(unsigned long long seed, unsigned int drones, unsigned int nectar_worker, unsigned int pollen_worker);
        /*
         * Beehive destructor which calls the destructor of
         * flower field, queens chamber, resource, logger
         */
        ~Beehive();
        /*
         * Add a newly born bee to the collection of bees
         */
        void add_bee(std::unique_ptr<bees::Bee> bee);
        /*
         * Start a new thread for each new bee created and add the thread to the collection
         * to be able to join those threads when the simulation ends
         */
        void add_bee_thread(std::unique_ptr<bees::Bee> bee);
        /*
         * Role dice to generate a random between the given range
         * @param Min range
         *        Max range
         * @return randomly generated number between the range provided
         */
        unsigned int roll_dice(unsigned int min, unsigned int max);
        /*
         * Start the simulation by creating the threads for each bee object
         * and running them in the foreground
         */
        void start_simulation();
        /*
         * End the simulation by joining all the threads
         */
        void end_simulation();
        /*
         * Get instance of logger for printing thread safe messages
         * @return logger
         */
        util::logger* get_logger();
        /*
         * Get instance of flower field
         * @return flower field
         */
        world::FlowerField* get_flower_field();
        /*
         * Get the instance of resource object which has the
         * # nectar and # pollen resources
         * @return resource
         */
        bees::Resource* get_resource();
        /*
         * Get the instance of queen's chamber
         * @return queen's chamber
         */
        world::Queens_Chamber* get_queens_chamber();
        /*
         * Add the role and id of the perished bee's to the collection
         */
        void add_perished_bees(std::string bee);
        /*
         * Prints the perished bee's in the order they perished
         */
        void print_perished_bees();
        /*
         * Boolean to keep track whether the simulation is active or not
         */
        static bool is_active;

    private:
        unsigned int num_drones_;
        unsigned int num_nectar_worker_;
        unsigned int num_pollen_worker_;
        util::random random_;
        util::logger *log_;
        std::deque<std::unique_ptr<bees::Bee> > bee_collection_;
        std::deque<std::thread > bee_thread_collection_;
        world::FlowerField *flower_field_;
        bees::Resource *resource_;
        world::Queens_Chamber *queens_chamber_;
        std::deque<std::string> perished_bees_;
        std::mutex perished_bees_mtx_;
    };
}

#endif