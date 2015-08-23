#include "locator.hxx"
#include "debug.hxx"

Debug::Debug() { }

void Debug::tmp(string val) {
    tmps.push_back(val);
}

void Debug::set_key(string key, string val) {
    persistent[key] = val;
}
void Debug::del_key(string key) {
    persistent.erase(key);
}

void Debug::tick() {
    log();
    clear_tmp();
}

void Debug::clear_tmp() {
    tmps.clear();
}

