#include "queen.h"

using namespace bees;


Queen::Queen(Bee::Role role, world::Beehive *beehive):Bee::Bee(role, beehive) {
    std::cout << "*B* " << this->print_bee() << " is born" << std::endl;
}

void Queen::run() {
    while(world::Beehive::is_active){
        if(this->get_Beehive()->get_queens_chamber()->get_num_drone_bees() > 0){
            if(this->get_Beehive()->get_resource()->consume_resource(1) == 1){
                this->get_Beehive()->get_queens_chamber()->chamber_queen();
                unsigned int claim = this->get_Beehive()->roll_dice(1,5);
                unsigned int claimed = this->get_Beehive()->get_resource()->consume_resource(claim);
                for(unsigned int i = 0; i < claimed; i++){
                    unsigned int probability = this->get_Beehive()->roll_dice(1,10);
                    if(probability < 7){
                        this->get_Beehive()->add_bee_thread(bees::Bee::createBee(bees::Bee::Role::DRONES, this->get_Beehive()));
                    }else if(probability < 9){
                        this->get_Beehive()->add_bee_thread(bees::Bee::createBee(bees::Bee::Role::NECTAR, this->get_Beehive()));
                    } else if(probability < 11){
                        this->get_Beehive()->add_bee_thread(bees::Bee::createBee(bees::Bee::Role::POLLEN, this->get_Beehive()));
                    }
                    std::cout << "*Q* Queen birthed " << claimed << " children" << std::endl;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    this->get_Beehive()->get_queens_chamber()->free_drone_bees();
}

std::string Queen::print_bee() {
    return "QUEEN #" + std::to_string(this->get_id());
}

namespace bees{
    std::ostream& operator<<(std::ostream &os, const Queen &queen) {
        return os << "QUEEN #" << queen.get_id() << std::endl;
    }
}