#include "world/beehive.h"

using namespace world;
using std::cout;
using std::endl;


int main(int argc, char* argv[]) {
    Beehive bh(4, 4, 8, 8);
    cout << "Start simulation" << endl;
    bh.start_simulation();
    cout << "Main thread sleeping" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    cout << "Main thread awake and stop simulation" << endl;
    bh.end_simulation();
    return 0;
}
