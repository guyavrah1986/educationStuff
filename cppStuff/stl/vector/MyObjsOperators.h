#pragma once

#include <ostream>

#include "MyObj.h"
#include "MyObjNoDefualtCtor.h"

std::ostream& operator<<(std::ostream& out, const MyObjNoDefualtCtor& obj);
std::ostream& operator<<(std::ostream& out, const MyObj& obj);
