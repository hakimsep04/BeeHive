#include "queen.h"

using namespace bees;


Queen::Queen(Bee::Role role, world::Beehive *beehive):Bee::Bee(role, beehive) {
    //Print a message when the queen is born
    this->get_Beehive()->get_logger()->log("*B* " + this->print_bee() + " is born");
}

void Queen::run() {
    //Check for the simulation is active or not
    while(world::Beehive::is_active){
        //Checking the condition 1 of whether a drone is available for queen to mate
        if(this->get_Beehive()->get_queens_chamber()->get_num_drone_bees() > 0){
            //Checking the second condtion whether there is atleast one resource
            // of both nectar and pollen to consume in-order to mate with the drone
            if(this->get_Beehive()->get_resource()->consume_resource(1) == 1){
                //When both the conditions are met, queen enters the queen chamber
                this->get_Beehive()->get_queens_chamber()->chamber_queen();
                //Once the queen mates with drone, it randomly tries to produce more bees between 1 and 5
                unsigned int claim = this->get_Beehive()->roll_dice(1,5);
                //In order the re-produce queen tries to consume resource
                //Eg: To reproduce one bee, one nectar and pollen is required
                unsigned int claimed = this->get_Beehive()->get_resource()->consume_resource(claim);
                for(unsigned int i = 0; i < claimed; i++){
                    //Queen calculates the probability of creating the type of bee
                    unsigned int probability = this->get_Beehive()->roll_dice(1,10);
                    //60% probability for creating drone bee
                    if(probability < 7){
                        this->get_Beehive()->add_bee_thread(bees::Bee::createBee(bees::Bee::Role::DRONES, this->get_Beehive()));
                    //20% probability for creating nectar_worker bee
                    }else if(probability < 9){
                        this->get_Beehive()->add_bee_thread(bees::Bee::createBee(bees::Bee::Role::NECTAR, this->get_Beehive()));
                    //20% probability for creating pollen_worker bee
                    } else if(probability < 11){
                        this->get_Beehive()->add_bee_thread(bees::Bee::createBee(bees::Bee::Role::POLLEN, this->get_Beehive()));
                    }
                }
                //Display a message of how many queen bees the queen has given birthed to
                this->get_Beehive()->get_logger()->log("*Q* Queen birthed " + std::to_string(claimed) + " children");
            }
        }
        //Queen sleeps for one second before attempting to mate again
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    //Queen releases all the drone bees which haven't mated with queen when the simulation ends
    this->get_Beehive()->get_queens_chamber()->free_drone_bees();
}

std::string Queen::print_bee() {
    return "QUEEN #" + std::to_string(this->get_id());
}