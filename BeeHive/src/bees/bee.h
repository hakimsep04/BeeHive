#ifndef BEE_H
#define BEE_H

#include <string>

namespace world{
    class Beehive;
}

namespace bees{
    class Bee{
    public:

        enum Role
        {
            QUEEN,
            DRONES,
            NECTAR,
            POLLEN
        };

        Role get_role() const;

        virtual ~Bee();

        operator std::string() const;

        static std::unique_ptr<Bee> createBee (Role role, world::Beehive *beehive);

        virtual void run() = 0;

        world::Beehive * get_Beehive();

    protected:
        Bee (Role role, world::Beehive *beehive);

    private:
        Role role_;
        world::Beehive *beehive_;

    };
}


#endif // BEE_H