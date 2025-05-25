// usbcam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <thread>
#include <set>

std::set<std::string> get_removable_drives() {
    std::set<std::string> result;
    DWORD drives = GetLogicalDrives();
    for (char i = 0; i < 26; ++i) {
        if (drives & (1 << i)) {
            std::string drive = std::string(1, 'A' + i) + ":\\";
            if (GetDriveTypeA(drive.c_str()) == DRIVE_REMOVABLE) {
                result.insert(drive);
            }
        }
    }
    return result;
}

int main()
{
    std::set<std::string> a = get_removable_drives();
    std::cout << "Hello World!\n";
    for (std::string b : a)
    {
        std::cout << b<< std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
