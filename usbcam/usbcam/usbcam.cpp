// usbcam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifdef _WIN32
    // Code to execute if the OS is Windows (32-bit or 64-bit)
    // _WIN32 is defined by the compiler when compiling for Windows.
    #include <windows.h>
    #define move q 
#else
    // Code to execute if the OS is not Windows
    #include <linux.h>
#endif
#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <set>
#include "camera.h"
#define multithread false
using namespace std;

using namespace filesystem;
std::vector<std::string> split(const std::string& str, const std::string& delimiters) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = 0;

    while (end < str.size()) {
        // Skip delimiter characters
        while (end < str.size() && delimiters.find(str[end]) != std::string::npos) {
            ++end;
        }
        start = end;
        // Find the next delimiter
        while (end < str.size() && delimiters.find(str[end]) == std::string::npos) {
            ++end;
        }
        if (end > start) {
            tokens.push_back(str.substr(start, end - start));
        }
    }

    return tokens;
}
static bool ispresent(const string find, string from)
{
    const filesystem::path dir = path{ from };
    for (const auto& entry : directory_iterator(dir))
    {
        if (exists(from+find))
        {
            return true;
        }
    }
    return false;
}
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
static void copy_files(const std::string& from, const std::string& to) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(from)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension().string();
            if (ext == ".jpg" || ext == ".png" || ext == ".mp4" || ext == ".log") {
                std::filesystem::copy_file(entry.path(), to + "\\" + entry.path().filename().string());
                std::cout << "Copied: " << entry.path() << std::endl;
            }
        }
    }
}
static void copy_files_log(const std::string& from, const std::string& to)
{

}
static void list_files(const std::string& from) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(from)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().string();
            cout << ext << endl;
        }
    }
}
static void movefiles(const std::string& from, const std::string& to)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(from)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension().string();
            if (ext == ".log")
            {
                string date = entry.path().stem().string();
                create_directory(date);
            }
            if (ext == ".jpg" || ext == ".png" || ext == ".MP4" ) {
                std::filesystem::rename(entry.path(), to + "\\" + entry.path().filename().string());
                std::cout << "Copied: " << entry.path() << std::endl;
            }
        }
    }

}

static void movelogs(const std::string& from, const std::string& to)
{
      for (const auto& entry : std::filesystem::recursive_directory_iterator(from)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension().string();
            if (ext == ".txt")
            {
                string date = entry.path().stem().string();
                path dest = path(to + "\\" + date + "\\" + entry.path().filename().string());
                if (!ispresent("\\"+date, to))
                {
                    create_directory(to+"\\"+date);
                    std::filesystem::rename(entry.path(),dest);
                    std::cout << "Copied: " << entry.path() << std::endl;
                }
                else
                {
                    
                    std::filesystem::rename(entry.path(), dest);
                    std::cout << "Copied: " << entry.path() << std::endl;
                }

            }
        }
    }

}
static void moveandsort( const std::string& from, const std::string& to)
{
    // y m d
    //last 2 digits of year on vid

   
    // Convert to a more human-readable format (e.g., system_clock::time_point)
    for (const auto& entry : std::filesystem::recursive_directory_iterator(from)) { 
        
        
        
        
        
        auto last_write_time = std::filesystem::last_write_time(entry);
        string sctp = format("{}", last_write_time);
        sctp = sctp.substr(0, 10);
        vector<string> splitup = split(sctp,"-");
        string date = splitup[0] + splitup[1] + splitup[2];
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension().string();
            if (ext == ".log")
            {
                string date = entry.path().stem().string();
                create_directory(date);
            }
            if (ext == ".JPG" || ext == ".PNG" || ext == ".MP4"||ext==".WAV") {
                std::filesystem::rename(entry.path(), to + "\\" +date+"\\" + entry.path().filename().string());
                std::cout << "Copied: " << entry.path() << std::endl;
            }
        }
    }
}
enum camera_model
{
    boblov_m
};
thread threads;
boblov boblov_cameras;
const static string boblov_cam_vid_path = "FILE\\100china";
const std::string log_path = "LOG";
const static string vids = "E:\\pics and videos\\body camera\\unsorted";
const static string bodycam_sorted_vids = "E:\\pics and videos\\body camera\\sorted";
vector<string> extensions = { ".jpg" ,".png",".mp4",".log" };
int main()
{
    vector<camerainfo> types = { boblov_cameras };
    vector<string> valid_drives;
    std::set<std::string> a = get_removable_drives();
    std::cout << "Hello World!\n";
    for (std::string removeabledrive : a) // for each removable drive
    {
        
        std::cout << removeabledrive <<" "<< std::endl;
        //list_files(b + cam_vid_path);
        if (ispresent(boblov_cam_vid_path, removeabledrive))
        {
           if(multithread)valid_drives.push_back(removeabledrive);
           else
           {
               movelogs(removeabledrive + log_path, bodycam_sorted_vids);
               moveandsort(removeabledrive+boblov_cam_vid_path, bodycam_sorted_vids);

           }
        }
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
