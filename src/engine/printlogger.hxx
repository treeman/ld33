#pragma once

#include "log.hxx"

class Printlogger : public Logger {
private:
    virtual void write(string s) override {
        // Implement c++ style...
        // Meh!
        printf("%s", s.c_str());
        fflush(stdout);
    }
};

