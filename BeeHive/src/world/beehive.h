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
    class Beehive{
    public:
        Beehive(unsigned long long seed, unsigned int drones, unsigned int nectar_worker, unsigned int pollen_worker);

        ~Beehive();

        std::deque<std::unique_ptr<bees::Bee>>* get_bees();

        void add_bee(std::unique_ptr<bees::Bee> bee);

        void add_bee_thread(std::unique_ptr<bees::Bee> bee);

        unsigned int roll_dice(unsigned int min, unsigned int max);

        void start_simulation();

        void end_simulation();

        util::logger* get_logger();

        world::FlowerField* get_flower_field();

        bees::Resource* get_resource();

        world::Queens_Chamber* get_queens_chamber();

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


    };
}

#endif