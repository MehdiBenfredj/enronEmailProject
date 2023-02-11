#include <iostream>
#include <string>
#include <unordered_map>
#include "Sender.h"
#include "Worker.h"
#include <dirent.h>
#include <stack>
#include <set>
#include <thread>
#include <mutex>

using namespace std;

void getFiles(string const& directory, stack<string> & files) {
    DIR* dir = opendir(directory.c_str());

    if (dir == NULL) {
        cerr << "Error: Cannot open directory '" << directory << "'" << endl;
        return;
    }
    dirent* file;
    while ((file = readdir(dir)) != NULL) {
        if (file->d_name[0] == '.') {
            continue;
        }

        string file_path = directory + "/" + file->d_name;
        if (file->d_type == DT_DIR) {
            getFiles(file_path, files);
        } else if (file->d_type == DT_REG) {
            files.push(file_path);
        }
    }
    closedir(dir);
}



std::mutex myMutex;



int main() {
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Create files stack<string>
    stack<string> files;

    // Get file paths
    string directory("../../../../mehdi/Downloads/maildir");
    string dir("../email");
    getFiles(dir,files);

    // Create senders map
    unordered_map<string, Sender*> senders;

    // Create Worker
    Worker worker;

    ////////Worker Job/////////////
    while (!files.empty()) {
        worker.job(files.top(), senders);
        files.pop();
    }

    // printing Sender + receivers + count
    for(pair<string, Sender*> senderr : senders) {
        cout << senderr.second->getEmail() << endl;
        for(pair<string, int> rec : senderr.second->getReceivers()) {
            cout << rec.first << endl;
            cout << rec.second << endl;
        }
        delete(senderr.second);
    }

    cout << senders.size() << endl;

    // Stop timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // Output the elapsed time
    std::cout << "Elapsed time: " << elapsed_time.count() << " milliseconds" << std::endl;



    return 0;
}
