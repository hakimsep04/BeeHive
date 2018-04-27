#ifndef BEE_H
#define BEE_H

#include <string>
#include <memory>

namespace world {
    class Beehive;
}

namespace bees {
    /*
     * An abstract bee class which is the base class for Queen, Drone and Worker bees
     *
     * @author Abdul Hakim Shanavas @ RIT CS
     */
    class Bee {
    public:
        /*
         * Bee role
         * Enumerator
         * Queen
         * Drones
         * Nectar_Worker
         * Pollen_Worker
         */
        enum Role {
            QUEEN,
            DRONES,
            NECTAR,
            POLLEN
        };
        /*
         * get bee role
         * @return Role role
         */
        Role get_role() const;
        /*
         * Virtual bee destructor
         */
        virtual ~Bee();
        /*
         * A string conversion operator that returns the string name of the role, e.g.
         * "QUEEN", "DRONES, "NECTAR", "POLLEN"
         */
        operator std::string() const;
        /*
         * Create the bee
         * @param Role role
         *        Beehive beehive
         * @return Bee unique pointer
         */
        static std::unique_ptr<Bee> createBee(Role role, world::Beehive *beehive);
        /*
         * Pure virtual run method
         */
        virtual void run() = 0;
        /*
         * Virtual method to get the resource number allocated to worker bee
         * @return number of resource
         */
        virtual int get_resource_number() const;
        /*
         * pure virtual print method to print the bee
         */
        virtual std::string print_bee() = 0;
        /*
         * Get the id of each bee
         * @return bee's unique id
         */
        int get_id() const;
        /*
         * Get the instance of Beehive
         * @return beehive
         */
        world::Beehive *get_Beehive() const;


    protected:
        /*
         * Create bee
         * @param : Role role
         *          Beehive beehive
         */
        Bee(Role role, world::Beehive *beehive);

    private:
        Role role_;
        world::Beehive *beehive_;
        int id_;
        static int bee_counter_;


    };
}


#endif // BEE_H