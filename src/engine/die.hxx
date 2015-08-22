#pragma once

#include <string>
using namespace std;

#include "locator.hxx"
#include "fmt.hxx"

// Critical errors etc.
// Use instead of using exceptions when we know we don't want to continue.
// May change later.
void die(string msg);

// printf with type checking.
template<typename... Ts>
void die(const char *f, const Ts&... ts) { die(fmt(f, ts...)); }

