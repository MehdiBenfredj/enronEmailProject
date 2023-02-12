#include <iostream>
#include <string>
#include <unordered_map>
#include "Sender.h"
#include "Worker.h"
#include <dirent.h>
#include <stack>
#include <thread>
#include <mutex>
#include <fstream>


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



mutex myMutex;
string popFromStack(stack<string> & files, unordered_map<string, Sender*> & senders) {
    const std::lock_guard<std::mutex> lock(myMutex);
    string filename;
    if(!files.empty()){
        filename = files.top();
        files.pop();
    }
    return filename;
}

void doWork(stack<string> & files, unordered_map<string, Sender*> & senders) {
    while(true) {
        string filename = popFromStack(files, senders);
        if (!filename.empty()) {
            Worker worker;
            worker.job(filename, senders);
        } else {
            break;
        }

    }
}


int main() {
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Create files stack<string>
    stack<string> files;

    // Get file paths
    string directory("../../../../mehdi/Downloads/maildir");
    string dir("../email");
    getFiles(directory,files);

    // Create senders map
    unordered_map<string, Sender*> senders;


    // Creation des threads 5
    std::thread threads[12];
    for (auto & i : threads) {
        i = thread([&files, &senders]() { doWork(files, senders); });
    }

    // Wait for all threads to finish
    for (auto & thread : threads) {
        thread.join();
    }

    // Create writing file
    std::ofstream outfile;
    outfile.open("../result.txt");

    // Si erreur d'ouverture
    if(outfile.bad()) {
        cout << "cannot open result file"; // on quitte
    } else {
        for (pair<string, Sender *> sender : senders) {
            cout << sender.first << endl;
            outfile << sender.first << endl;
            for (pair<string,int> receiver : sender.second->getReceivers()) {
                cout << receiver.second << ":" << receiver.first << endl;
                outfile << receiver.second << ":" << receiver.first << endl;
            }

            outfile << endl;
        }
    }



    // Fermeture du fichier
    outfile.close();

    // Stop timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // Output the elapsed time
    std::cout << "Elapsed time: " << elapsed_time.count() << " milliseconds" << std::endl;



    return 0;
}
