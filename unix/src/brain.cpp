#include <iostream>
#include <thread>   // Debug
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

// !!!UNIX SRC ONLY!!!

// *Delay* is the countdown to data destruction.
// *Mode* is the mode that the program operates in.
// Mode 0: Benign only display to active terminals.
// Mode 1: Active unlink all data.
// Mode 2: Active destroy all data.
// Mode 3: Active destroy all data and rewrite MBR.

int delay = 0;
int mode = 0;
vector<string> termlist;

int hookTerm()
{
    // Access the available tty, pts, and vty stdout.
    // Update active teminal list and directory listing.
    for (const auto & entry : filesystem::directory_iterator("/dev/pts/"))
        std::cout << entry.path() << std::endl;
    return 1;
}

int printTerms()
{
    return 1;
}

int isRoot()
{
    return 1;
}

int main(int argc, char *argv[])
{
    cout << "Brainwasher 1.0" << endl;
    if(argc != 3)
    {
        cout << "Syntax: bw.exe <delay> <mode>" << endl;
        return 1;
    }
    delay = strtol(argv[1], nullptr, 0);
    mode = strtol(argv[2], nullptr, 0);

    if(isRoot())
    {
        cout << "Mode: " << mode << endl;
        while(delay>0)
        {
            cout << delay << "\r";
            this_thread::sleep_for(1000ms);
            cout << "      " << "\r";
            delay--;
        }
    }else
    {
        cout << "Brainwashing failed - No root." << endl; 
        return 2;
    }
    return 0;
}