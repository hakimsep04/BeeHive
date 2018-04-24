#include "flower_field.h"

using namespace world;

unsigned int FlowerField::bee_monitor_counter_ = 0;
FlowerField::FlowerField(): mtx_{}, condition_variable_{}{}

void FlowerField::field(std::unique_ptr<bees::Bee> bee) {

}