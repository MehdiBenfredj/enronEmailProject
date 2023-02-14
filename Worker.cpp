//
// Created by Mehdi on 10/02/2023.
//

#include "Worker.h"
#include "iostream"
#include <fstream>
#include <set>
#include <mutex>
#include "unableToOpenFileException.h"

using namespace std;
std::mutex workerMutex;

Worker::Worker()
{}

Worker::~Worker() = default;


void Worker::addReceiver(Sender * &sender, string const& receiver) {
    const std::lock_guard<std::mutex> lock(workerMutex);
    sender->addReceiver(receiver);
}

Sender * Worker::addSender(string const& sender, unordered_map<string, Sender*> & senders) {
    const std::lock_guard<std::mutex> lock(workerMutex);
    try {
        return senders.at(sender);
    } catch (out_of_range& e) {
        auto * senderPointer = new Sender(sender);
        senders[sender] = senderPointer;
        return senderPointer;
    }
}

void Worker::rm_nonprinting (std::string& str)
{
    str.erase (std::remove_if (str.begin(), str.end(),
                               [](unsigned char c){
                                   return !std::isprint(c);
                               }),
               str.end());
}

pair<string, set<string> > Worker::parseEmail(string const& filePath) {
    string sender;
    set<string> emails;
    ifstream file(filePath);
    string line;
    string champs;

    try {
        if (file.is_open()) {
            while (getline(file, line)) {
                if (line.rfind("X", 0) == 0) {
                    break;
                }
                else if (line.find("From:") == 0) {
                    string from(line.substr(6));
                    //rm_nonprinting(from) ;
                    sender = from;
                }
                else if (line.find("To:") == 0) {
                    champs = line.substr(4);
                    while (getline(file, line)) {
                        if (line.rfind("X", 0) == 0) {
                            break;
                        }
                        if(!isupper(line[0])) {
                            champs += line;
                        } else {
                            // declaring character array (+1 for null terminator)
                            char* str = new char[champs.length() + 1];
                            // copying the contents of the
                            // string to char array
                            strcpy(str, champs.c_str());
                            char *token = strtok(str, ", ");
                            while (token != NULL)
                            {
                                string token_string(token);
                                token_string.erase(std::remove(token_string.begin(), token_string.end(), '\t'), token_string.end());
                                emails.insert(token_string);
                                token = strtok(NULL, ", ");

                            }
                            champs.clear();
                            break;
                        }
                    }
                }
                else if (line.find("Cc:") == 0) {
                    champs = line.substr(4);
                    bool entered = false;
                    while (getline(file, line)) {
                        if (line.rfind("X", 0) == 0) {
                            break;
                        }
                        entered = true;
                        if(!isupper(line[0])) {
                            champs += line;
                        } else {
                            char* str = new char[champs.length() + 1];
                            // copying the contents of the
                            // string to char array
                            strcpy(str, champs.c_str());
                            char *token = strtok(str, ", ");
                            while (token != NULL)
                            {
                                string token_string(token);
                                token_string.erase(std::remove(token_string.begin(), token_string.end(), '\t'), token_string.end());
                                token = strtok(NULL, ", ");
                                emails.insert(token_string);
                            }
                            champs.clear();
                            break;
                        }
                    }
                    if(!entered) {
                        char* str = new char[champs.length() + 1];
                        // copying the contents of the
                        // string to char array
                        strcpy(str, champs.c_str());
                        char *token = strtok(str, ", ");
                        while (token != NULL)
                        {
                            string token_string(token);
                            token_string.erase(std::remove(token_string.begin(), token_string.end(), '\t'), token_string.end());
                            token = strtok(NULL, ", ");
                            emails.insert(token_string);
                        }
                        champs.clear();
                    }
                }
                else if (line.find("Bcc:") == 0) {
                    champs = line.substr(4);
                    bool entered = false;
                    while (getline(file, line)) {
                        if (line.rfind("X", 0) == 0) {
                            break;
                        }
                        entered = true;
                        if(!isupper(line[0])) {
                            champs += line;
                        } else {
                            char* str = new char[champs.length() + 1];

                            // copying the contents of the
                            // string to char array
                            strcpy(str, champs.c_str());
                            char *token = strtok(str, ", ");
                            while (token != NULL)
                            {
                                string token_string(token);
                                token_string.erase(std::remove(token_string.begin(), token_string.end(), '\t'), token_string.end());
                                token = strtok(NULL, ", ");
                                emails.insert(token_string);
                            }
                            champs.clear();
                            break;
                        }
                    }
                    if(!entered) {
                        char* str = new char[champs.length() + 1];
                        // copying the contents of the
                        // string to char array
                        strcpy(str, champs.c_str());
                        char *token = strtok(str, ", ");
                        while (token != NULL)
                        {
                            string token_string(token);
                            token_string.erase(std::remove(token_string.begin(), token_string.end(), '\t'), token_string.end());
                            token = strtok(NULL, ", ");
                            emails.insert(token_string);
                        }
                        champs.clear();
                    }
                }
            }
            file.close();
            return make_pair(sender, emails);

        } else {
            unableToOpenFileException erreur(filePath);
            throw(erreur);
        }
    } catch (unableToOpenFileException &erreur) {
        cout << erreur.what() << endl;
        cout << erreur.cause << endl;
    }
}

void Worker::job(std::string &path, std::unordered_map<std::string, Sender*> & senders) {
    // Parsing the file
    pair<string, set<string> > result = parseEmail(path);

    // Add the sender
    Sender * sender = addSender(result.first, senders);

    // Add receivers to the sender
    for (const string& receiver : result.second) {
        addReceiver(sender, receiver);
    }
}


