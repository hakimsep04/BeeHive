#include "world/beehive.h"

using namespace world;
using std::cout;
using std::endl;
using std::stoull;
using std::stoi;


int main(int argc, char* argv[]) {
    if(argc < 5){
        cout << "Usage: bee_main seed seconds drones nectar_workers pollen_workers" << endl;
    }else{

            unsigned long long seed = stoull(argv[1],0,0);
            unsigned long long seconds = stoull(argv[2],0,0);
            unsigned int drones = stoi(argv[3],0,0);
            unsigned int nectar_workers = stoi(argv[4],0,0);
            unsigned int pollen_workers = stoi(argv[5],0,0);

            cout << "Seed: " << seed << endl;
            cout << "Simulation time: " << seconds << " seconds" << endl;
            cout << "Starting drones: " << drones << endl;
            cout << "Starting nectar workers: " << nectar_workers << endl;
            cout << "Starting pollen workers: " << pollen_workers << endl;

            Beehive bh(seed, drones, nectar_workers, pollen_workers);
            cout << "Start simulation" << endl;
            bh.start_simulation();
            cout << "Main thread sleeping" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
            cout << "Main thread awake and stop simulation" << endl;
            bh.end_simulation();

            //statistics
            cout << "Bees born : " << bh.get_bees()->front()->get_bees_born() << endl;
            cout << "Bees perished : " << bh.get_bees()->front()->get_perished_bees() << endl;
            cout << "Nectar remaining " << bh.get_resource()->get_nectar_gathered() << endl;
            cout << "Pollen remaining " << bh.get_resource()->get_pollen_gathered() << endl;
            cout << "Nectar gathered " << bh.get_resource()->get_total_nectar() << endl;
            cout << "Pollen gathered " << bh.get_resource()->get_total_pollen() << endl;



    }



    return 0;
}
