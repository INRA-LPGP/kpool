#pragma once
#include "stdint.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <assert.h>

uint32_t fast_stoi(const char* str);

// Split a std::string into a std::vector of std::strings according to a specified delimiter (default: \t)
std::vector<std::string> split(std::string str, const std::string delimiter);

std::string get_canonical_form(std::string& sequence);

char complement(char n);
