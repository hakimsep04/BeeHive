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

    protected:
        Bee (Role role);

    private:
        Role role_;

    };
}


#endif // BEE_H