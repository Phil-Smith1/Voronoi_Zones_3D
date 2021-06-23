#pragma once

#include "Input.h"

typedef K::Vector_3 V3;

void Surrounding_Cloud ( Input const& input, int index, multimap<double, P3>& cloud );
