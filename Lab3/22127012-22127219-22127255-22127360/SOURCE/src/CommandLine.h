#ifndef SORTING_ANALYSIS_COMMAND_LINE_H
#define SORTING_ANALYSIS_COMMAND_LINE_H
#include "../include/SortContext.h"
#include "utils/DataGenerator.h"
#include "../include/common.h"
#include "string.h"
#include "iomanip"
#include <fstream>
#include <iostream>

void CommandLine1(int argc, const char* argv[]);
void CommandLine2(int argc, const char* argv[]);
void CommandLine2_CSV(int argc, const char* argv[], std::ofstream &ofs);

void CommandLine3(int argc, const char* argv[]);
void CommandLine4(int argc, const char* argv[]);
void CommandLine5(int argc, const char* argv[]);
SortingAlgorithm convertStringToEnum(char* algorithmName);

#endif