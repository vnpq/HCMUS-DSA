#include <string.h>
#include <time.h>
//#include "../external/doctest.h"
#include "CommandLine.h"

using namespace std;

const string algo = {};

int main(int argc, const char *argv[])
{
    if (argc > 4)
    {
        if (strcmp(argv[1], "-a") == 0)
        {
            if (argc == 5)
            {
                if (isdigit(argv[3][strlen(argv[3]) - 1]))
                {
                    // cout << "Command 3\n";
                    CommandLine3(argc, argv);
                }
                else
                {
                    // cout << "Command 1\n";
                    CommandLine1(argc, argv);
                }
            }
            else if (argc == 6)
            {
                // cout << "Command 2\n";
                CommandLine2(argc, argv);
            }
        }
        else if (strcmp(argv[1], "-c") == 0)
        {
            if (argc == 5)
            {
                // cout << "Command 4\n";
                CommandLine4(argc, argv);
            }
            else if (argc == 6)
            {
                // cout << "Command 5\n";
                CommandLine5(argc, argv);
            }
        }
    }
    else
    {
        // std::ofstream ofs("RandomOrder.csv");
        // int nSortAlgo = 11;
        // int nDataSize = 6;
        // int nDataOrder = 4;

        // const char *dataOrder[] = {"-rand", "-nsorted", "-sorted", "-rev"};
        // const char *sortingName[] = {"heap-sort", "radix-sort", "merge-sort", "bubble-sort", "selection-sort", "insertion-sort", "quick-sort", "shaker-sort", "shell-sort", "counting-sort", "flash-sort"};
        // const int dataSize[] = {10000, 30000, 50000, 100000, 300000, 500000};

        // std::string Orders[] = {"Random", "Nearly Sorted", "Sorted", "Reversed"};

        // const char *executionFile = ".\\sorting_analysis.exe";
        // const char *mode = "a";
        // const char *outputMode = "-both";

        // for (int order = 0; order < nDataOrder; ++order)
        // {
        //     ofs << Orders[order] << '\n';
        //     ofs << "Data size,";
        //     for (int i = 0; i < nDataSize; ++i)
        //         ofs << dataSize[i] << ',' << ',';
        //     ofs << '\n';

        //     ofs << "Resulting statics,";
        //     for (int i = 0; i < nDataSize; ++i)
        //         ofs << "Runtime,Comparison,";

        //     ofs << '\n';
        //     for (int algo = 0; algo < nSortAlgo; ++algo){
        //         ofs << sortingName[algo] << ',';
        //         for (int size = 0; size < nDataSize; ++size)
        //         {
        //             const char* sizeString = to_string(dataSize[size]).c_str();
        //             const char* m_argv[] = {executionFile, mode, sortingName[algo], sizeString, dataOrder[order], outputMode};
        //             CommandLine2_CSV(6, m_argv, ofs);
        //         }
        //         ofs << '\n';
        //     }
        //     ofs << '\n';
        // }

        // ofs.close();
        // doctest::Context context;
        // // !!! THIS IS JUST AN EXAMPLE SHOWING HOW DEFAULTS/OVERRIDES ARE SET !!!

        // // defaults
        // context.addFilter(
        //     "test-case-exclude",
        //     "*math*");  // exclude test cases with "math" in their name
        // context.setOption("abort-after",
        //                   5);  // stop test execution after 5 failed assertions
        // context.setOption("order-by", "name");  // sort the test cases by their name

        // context.applyCommandLine(argc, argv);

        // // overrides
        // context.setOption(
        //     "no-breaks", true);  // don't break in the debugger when assertions fail

        // int res = context.run();  // run

        // if (context.shouldExit())  // important - query flags (and --exit) rely on
        //                            // the user doing this
        //   return res;              // propagate the result of the tests

        // int client_stuff_return_code = 0;
        // // your program - if the testing framework is integrated in your production
        // // code

        // return res + client_stuff_return_code;  // the result from doctest is
        //                                         // propagated here as well
    }
}