#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;

// Collect debug values available for printing or stuff.
class Debug {
public:
    Debug();
    virtual ~Debug() { }

    // Use if we set it every update iteration.
    void tmp(string val);

    // Use if we're only setting it sometime
    void set_key(string key, string val);
    void del_key(string key);

    void tick();
private:
    void clear_tmp();
    virtual void log() = 0;
protected:
    vector<string> tmps;
    map<string, string> persistent;
};


