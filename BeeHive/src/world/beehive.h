#ifndef BEEHIVE_H
#define BEEHIVE_H

#include <deque>
#include "../util/random.h"
#include "../bees/bee.h"
#include <thread>



namespace world{
    class Beehive{
    public:
        Beehive(unsigned long long seed, unsigned int drones, unsigned int nectar_worker, unsigned int pollen_worker);

        ~Beehive();

        std::deque<std::unique_ptr<bees::Bee>> get_bees();

        void add_bee(std::unique_ptr<bees::Bee> bee);

        unsigned int roll_dice(unsigned int min, unsigned int max);

        void start();

        void start_simulation();

        void end_simulation();

    private:
        unsigned int num_drones_;
        unsigned int num_nectar_worker_;
        unsigned int num_pollen_worker_;
        util::random random_;
        std::deque<std::unique_ptr<bees::Bee> > bee_collection_;
        std::deque<std::thread > bee_thread_collection_;

    };
}

#endif