//
// Created by Mehdi on 10/02/2023.
//

#include "Sender.h"
using namespace std;

Sender::Sender(string mail) : m_email(mail)
{}

const std::string &Sender::getEmail() const {
    return m_email;
}

void Sender::setEmail(const std::string &email) {
    Sender::m_email = email;
}

const std::unordered_map<std::string, int> &Sender::getReceivers() const {
    return m_receivers;
}

void Sender::addReceiver(std::string const& receiver) {
    m_receivers[receiver]++;
}

bool Sender::operator==(const Sender& other) const {
    return m_email == other.m_email;
}

Sender::~Sender() {}