#include "world/beehive.h"

using namespace world;
using std::cout;
using std::endl;


int main(int argc, char* argv[]) {
    Beehive bh(0, 0, 1, 1);
    cout << "Start simulation" << endl;
    bh.start_simulation();
    cout << "Main thread sleeping" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Main thread awake and stop simulation" << endl;
    bh.end_simulation();

    //statistics
    cout << "Total Nectar gathered : " << bh.get_resource().get_total_nectar() << endl;
    cout << "Total Pollen gathered : " << bh.get_resource().get_total_pollen() << endl;
    cout << "Remaining Nectar : " << bh.get_resource().get_nectar_gathered() << endl;
    cout << "Remaining Pollen : " << bh.get_resource().get_pollen_gathered() << endl;


    return 0;
}
