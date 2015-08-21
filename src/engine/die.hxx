#pragma once

#include <string>
using namespace std;

#include "locator.hxx"
#include "fmt.hxx"

// Critical errors etc.
// Use instead of using exceptions when we know we don't want to continue.
// May change later.
void die(string msg) {
    L_("\nAborting due to critical error.\n%s\n", msg.c_str());
    if (Locator::has_window()) {
        auto &w = Locator::get_window();
        w.close();
    }
    exit(EXIT_FAILURE);
}

// printf with type checking.
template<typename... Ts>
void die(const char *f, const Ts&... ts) { die(fmt(f, ts...)); }

