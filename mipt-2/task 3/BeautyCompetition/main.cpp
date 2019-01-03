//
//  main.cpp
//  BeautyCompetition
//
//  Created by Andrey Danilov on 15.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <assert.h>
using namespace std;

class ParticipantName;
class ParticipantScore;


class Participant{
public:
    ParticipantName *name;
    ParticipantScore *score;
    Participant(ParticipantName *n, ParticipantScore *s){
        name = n;
        score = s;
    }
};

class ParticipantName{
public:
    string name;
    int id;
    static vector<Participant> *participants;
    ParticipantName(string n, int id = -1){
        name = n;
        this->id = id;
    }
    ParticipantName(ParticipantName&& other){
        name = other.name;
        id = other.id;
        (*participants)[id].name = this;
    }
    ParticipantName&& operator= (ParticipantName&& other){
        name = other.name;
        id = other.id;
        (*participants)[id].name = this;
        return move(*this);
    }
    bool operator < (const ParticipantName& other) const{
        return name < other.name;
    }
};

class ParticipantScore{
public:
    int score;
    int id;
    static vector<Participant> *participants;
    ParticipantScore(int s, int id = -1){
        score = s;
        this->id = id;
    }
    ParticipantScore(ParticipantScore&& other){
        score = other.score;
        id = other.id;
        (*participants)[id].score = this;
    }
    ParticipantScore&& operator= (ParticipantScore&& other){
        score = other.score;
        id = other.id;
        (*participants)[id].score = this;
        return move(*this);
    }
    bool operator < (const ParticipantScore& other) const{
        if(id >= 0 && other.id >= 0)
            return (score < other.score) || (score == other.score &&
                                             (*participants)[id].name > (*participants)[other.id].name);
        return score < other.score;
    }
};

class Vip{
public:
    string number;
    int counter;
    Vip(string n){
        number = n;
        counter = 0;
    }
    bool operator < (const Vip &other) const{
        return number < other.number;
    }
};

bool validNumber(set<Vip> &VipVoters, set<string> &Voters, string number){
    set<Vip>::iterator it = VipVoters.find(number);
    if(it != VipVoters.end()){
        if(it->counter < 3){
            Vip vip = *it;
            VipVoters.erase(it);
            ++vip.counter;
            VipVoters.insert(vip);
            return true;
        }
        else
            return false;
    }
    else{
        if(Voters.count(number) == 0){
            Voters.insert(number);
            return true;
        }
        else
            return false;
    }
    
}

vector<Participant> *ParticipantName::participants;
vector<Participant> *ParticipantScore::participants;

int main(int argc, const char * argv[]) {
    cout    << "Commands available:\n"
            << "REGISTER <name>\n"
            << "VIP <number>\n"
            << "VOTE <name> <number>\n"
            << "KICK <name>\n"
            << "TOP <number>\n"
            << "EXIT\n";
    string command;
    vector<Participant> participants;
    set<ParticipantName> participantNameSet;
    set<ParticipantScore> participantScoreSet;
    set<Vip> VipVoters;
    set<string> Voters;
    int id = 0;
    ParticipantScore::participants = ParticipantName::participants = &participants;
    while(true){
        cin >> command;
        if(command == "REGISTER"){
            string participantName;
            cin >> participantName;
            if(participantNameSet.count(participantName) == 0){
                cout << "OK\n";
                ParticipantName name(participantName, id);
                ParticipantScore score(0, id);
                participants.push_back(Participant(&name, &score));
                ++id;
                participantNameSet.insert(move(name));
                participantScoreSet.insert(move(score));
            }
            else{
                cout << "ALREADY REGISTERED\n";
            }
        }
        else if(command == "VIP"){
            string number;
            cin >> number;
            if(VipVoters.count(number) == 0){
                VipVoters.insert(number);
                cout << "OK\n";
            }
            else{
                cout << "ALREADY VIP\n";
            }
        }
        else if(command == "VOTE"){
            string name, number;
            cin >> name >> number;
            if(participantNameSet.count(name) == 0){
                cout << "NOT REGISTERED\n";
                continue;
            }
            if(validNumber(VipVoters, Voters, number)){
                int id = participantNameSet.find(name)->id;
                ParticipantScore score = move(*participants[id].score);
                participantScoreSet.erase(score);
                ++score.score;
                participantScoreSet.insert(move(score));
                cout << score.score << "\n";
            }
            else{
                cout << "NO MORE VOTES\n";
            }
        }
        else if(command == "KICK"){
            string name;
            cin >> name;
            if(participantNameSet.count(name) == 0){
                cout << "NOT REGISTERED\n";
            }
            else{
                int id = participantNameSet.find(name)->id;
                participantNameSet.erase(*participants[id].name);
                participantScoreSet.erase(*participants[id].score);
                cout << "OK\n";
            }
        }
        else if(command == "TOP"){
            int limit;
            cin >> limit;
            int i = 0;
            for(auto it = participantScoreSet.rbegin(); i < limit && it != participantScoreSet.rend(); ++i, ++it){
                cout << participants[it->id].name->name << " " << it->score << "\n";
            }
        }
        else if(command == "EXIT"){
            cout << "OK\n";
            return 0;
        }
    }
}