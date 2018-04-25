#ifndef BEE_H
#define BEE_H

#include <string>
#include <memory>

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

        virtual int get_resource_number() const = 0;

        int get_id() const;

        world::Beehive * get_Beehive() const ;

    protected:
        Bee (Role role, world::Beehive *beehive);

    private:
        Role role_;
        world::Beehive *beehive_;
        int id_;
        static int bee_counter_;

    };
}


#endif // BEE_H