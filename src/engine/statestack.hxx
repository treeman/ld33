#pragma once

#include <cassert>
#include <stdexcept>
#include <memory>
#include <stack>
#include <map>
using namespace std;

#include "engine/state.hxx"

class state_missing_error : public logic_error {
public:
    state_missing_error(const char *s) noexcept : logic_error(s) { }
    state_missing_error(const string &s) noexcept : logic_error(s) { }
};

// This could be made general, but meh!
class StateStack {
public:
    virtual ~StateStack() = default;

    bool has_current() const { return !s.empty(); }
    shared_ptr<State> current() const {
        assert(has_current());
        return s.top();
    }
    void push(shared_ptr<State> next) {
        s.push(next);
    }
    void pop() {
        assert(!s.empty());
        s.pop();
    }
    void push_generated(string key) {
        auto it = generators.find(key);
        if (it == generators.end())
            throw state_missing_error(key);
        push(move(shared_ptr<State>(it->second())));
    }
    void add_generator(string key, function<State*()> gen) {
        generators.insert({key, gen});
    }
private:
    stack<shared_ptr<State>> s;
    map<string, function<State*()>> generators;
};

