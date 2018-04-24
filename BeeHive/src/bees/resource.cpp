#include "resource.h"

using namespace bees;


Resource::Resource():
        nectar_gathered_{0},
        pollen_gathered_{0},
        total_nectar_gathered_{0},
        total_pollen_gathered_{0}{}

void Resource::deposit(bees::Worker *worker) {
    if(worker->get_role() == bees::Bee::Role::NECTAR){
        nectar_gathered_ += worker->get_resource_number();
        total_nectar_gathered_ += worker->get_resource_number();
    }else{
        pollen_gathered_ += worker->get_resource_number();
        total_pollen_gathered_ += worker->get_resource_number();
    }
}

unsigned int Resource::consume_resource(unsigned int claim) {
    unsigned int claimed = 0;
    if(nectar_gathered_ >= claim && pollen_gathered_ >= claim){
        claimed = claim;
    }else{
        claimed = std::min(nectar_gathered_, pollen_gathered_);
    }
    nectar_gathered_ -= claim;
    pollen_gathered_ -= claim;

    return claimed;
}

unsigned int Resource::get_nectar_gathered() const {
    return nectar_gathered_;
}

unsigned int Resource::get_pollen_gathered() const {
    return pollen_gathered_;
}

unsigned int Resource::get_total_nectar() const {
    return total_nectar_gathered_;
}

unsigned int Resource::get_total_pollen() const {
    return total_pollen_gathered_;
}