#include "world/beehive.h"

using namespace world;
using std::cout;
using std::endl;
using std::stoull;
using std::stoi;

/*
 * The main class which inputs the seed, seconds, # drones, # nectar_workers, # pollen_workers
 * Also responsible for
 * 1. Creating the beehive to start the simulation
 * 2. Sleeping till the simulation time
 * 3. Signaling the beehive to stop the simulation
 * 4. Displaying the final statistics
 *
 * @author Abdul Hakim Shanavas @ RIT CS
 */

int main(int argc, char *argv[]) {
    //Checking the number of provided arguments
    if (argc < 5) {
        //Displaying a usage message due to the number of arguments is incorrect
        cout << "Usage: bee_main seed seconds drones nectar_workers pollen_workers" << endl;
    } else {
        //Reading the command line input
        unsigned long long seed = stoull(argv[1], 0, 0);
        unsigned long long seconds = stoull(argv[2], 0, 0);
        unsigned int drones = stoi(argv[3], 0, 0);
        unsigned int nectar_workers = stoi(argv[4], 0, 0);
        unsigned int pollen_workers = stoi(argv[5], 0, 0);

        //Display the command line arguments to standard output format
        cout << "Seed: " << seed << endl;
        cout << "Simulation time: " << seconds << " seconds" << endl;
        cout << "Starting drones: " << drones << endl;
        cout << "Starting nectar workers: " << nectar_workers << endl;
        cout << "Starting pollen workers: " << pollen_workers << endl;

        //Creating the beehive
        Beehive bh(seed, drones, nectar_workers, pollen_workers);

        //Telling the beehive to start the simulation
        bh.start_simulation();

        //Sleeping for the required simulation time
        std::this_thread::sleep_for(std::chrono::seconds(seconds));

        //Telling the beehive to end the simulation
        bh.end_simulation();

        //Display the final statistics
        cout << endl;
        cout << "STATISTICS" << endl;
        cout << "===========" << endl;
        bh.print_perished_bees();
        cout << "Nectar remaining " << bh.get_resource()->get_nectar_gathered() << endl;
        cout << "Pollen remaining " << bh.get_resource()->get_pollen_gathered() << endl;
        cout << "Nectar gathered " << bh.get_resource()->get_total_nectar() << endl;
        cout << "Pollen gathered " << bh.get_resource()->get_total_pollen() << endl;

    }
    return 0;
}
