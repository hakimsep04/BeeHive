#ifndef QUEEN_H
#define QUEEN_H

#include "../world/beehive.h"

namespace bees{
    class Queen: public Bee{
    public:
        Queen(Bee::Role role, world::Beehive *beehive);

        void run() override;

        std::string print_bee() override;

    private:
        friend std::ostream &operator << (std::ostream &os, const Queen &queen);
    };
}

#endif