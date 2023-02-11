//
// Created by Mehdi on 10/02/2023.
//

#ifndef NEWENRONMAIL_SENDER_H
#define NEWENRONMAIL_SENDER_H

#include <string>
#include <unordered_map>

class Sender {
private:
    std::string m_email;
    std::unordered_map<std::string, int> m_receivers;
public:
    Sender(std::string email);

    ~Sender();

    const std::string &getEmail() const;

    void setEmail(const std::string &email);

    const std::unordered_map<std::string, int> &getReceivers() const;

    bool operator==(const Sender& other) const;

    void addReceiver(std::string const& receiver);

};

namespace std {
    template<>
    struct hash<Sender> {
        std::size_t operator()(const Sender &sender) const {
            return std::hash<std::string>()(sender.getEmail());
        }
    };
}



#endif //NEWENRONMAIL_SENDER_H
