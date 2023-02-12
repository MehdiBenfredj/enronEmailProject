//
// Created by Mehdi on 10/02/2023.
//

#ifndef NEWENRONMAIL_WORKER_H
#define NEWENRONMAIL_WORKER_H

#include <string>
#include <set>
#include <unordered_map>
#include "Sender.h"

class Worker {
public:
    Worker();

    ~Worker();

    Sender * addSender(std::string const& sender, std::unordered_map<std::string, Sender*> & senders);

    std::pair<std::string,std::set<std::string>>parseEmail(std::string const& filePath);

    void addReceiver(Sender * &sender, std::string const& receiver);

    void job(std::string &path, std::unordered_map<std::string, Sender*> & senders);
};


#endif //NEWENRONMAIL_WORKER_H
