#include "CommandLine.h"
#include "iomanip"

void readFromFile(int *&m_array, int &m_size, const char *fileName)
{
    std::ifstream ifs(fileName);
    if (!ifs.is_open())
    {
        std::cerr << "Cannot Open File\n";
        return;
    }
    ifs >> m_size;
    delete[] m_array;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        ifs >> m_array[i];
    }
    ifs.close();
}

void writeArrayToFile(int *array, int array_size, const char *file)
{
    std::ofstream ofs;
    ofs.open("input.txt");
    ofs << array_size << '\n';
    for (int i = 0; i < array_size; ++i)
        ofs << array[i] << ' ';
    ofs.close();
}

SortingAlgorithm convertStringToEnum(const char *algorithmName)
{
    if (strcmp(algorithmName, "bubble-sort") == 0)
    {
        return SortingAlgorithm::BubbleSort;
    }
    else if (strcmp(algorithmName, "radix-sort") == 0)
    {
        return SortingAlgorithm::RadixSort;
    }
    else if (strcmp(algorithmName, "merge-sort") == 0)
    {
        return SortingAlgorithm::MergeSort;
    }
    else if (strcmp(algorithmName, "flash-sort") == 0)
    {
        return SortingAlgorithm::FlashSort;
    }
    else if (strcmp(algorithmName, "bubble-sort") == 0)
    {
        return SortingAlgorithm::BubbleSort;
    }
    else if (strcmp(algorithmName, "insertion-sort") == 0)
    {
        return SortingAlgorithm::InsertionSort;
    }
    else if (strcmp(algorithmName, "selection-sort") == 0)
    {
        return SortingAlgorithm::SelectionSort;
    }
    else if (strcmp(algorithmName, "shell-sort") == 0)
    {
        return SortingAlgorithm::ShellSort;
    }
    else if (strcmp(algorithmName, "shaker-sort") == 0)
    {
        return SortingAlgorithm::ShakerSort;
    }
    else if (strcmp(algorithmName, "heap-sort") == 0)
    {
        return SortingAlgorithm::HeapSort;
    }
    else if (strcmp(algorithmName, "counting-sort") == 0)
    {
        return SortingAlgorithm::CountingSort;
    }
    return SortingAlgorithm::QuickSort;
}

void CommandLine1(int argc, const char *argv[])
{
    int *array = nullptr, size = 0;
    readFromFile(array, size, argv[3]);

    SortContext sortingObject;
    sortingObject.setStrategy(convertStringToEnum(argv[2]), array, size);
    if (sortingObject.getStrategy() == nullptr)
    {
        std::cerr << "Invalid algorithm!\n";
        return;
    }
    sortingObject.sort();

    SortContext compareObject;
    compareObject.setStrategy(convertStringToEnum(argv[2]), array, size);
    compareObject.sortWithComparison();

    // write to "output.txt"
    sortingObject.writeToFile("output.txt");

    // display
    std::cout << "ALGORITHM MODE\n";
    std::cout << "ALGORITHM: " << argv[2] << "\n";
    std::cout << "Input file: " << argv[3] << "\n";
    std::cout << "Input size: " << size << "\n";
    std::cout << "-------------------------\n";
    if (strcmp(argv[4], "-time") == 0 || strcmp(argv[4], "-both") == 0)
         std::cout << "Running Time: " << std::fixed << std::setprecision(5) << sortingObject.getDuration()
                      << " s\n";
    if (strcmp(argv[4], "-comp") == 0 || strcmp(argv[4], "-both") == 0)
        std::cout << "Comparisions: " << compareObject.getComparison() << "\n";
    delete[] array;
}

void CommandLine2(int argc, const char *argv[])
{
    int array_size = std::atoi(argv[3]);
    int *array = new int[array_size];
    if (strcmp(argv[4], "-rand") == 0)
    {
        GenerateRandomData(array, array_size);
    }
    else if (strcmp(argv[4], "-nsorted") == 0)
    {
        GenerateNearlySortedData(array, array_size);
    }
    else if (strcmp(argv[4], "-sorted") == 0)
    {
        GenerateSortedData(array, array_size);
    }
    else if (strcmp(argv[4], "-rev") == 0)
    {
        GenerateReverseData(array, array_size);
    }
    writeArrayToFile(array, array_size, "input.txt");

    SortContext sortingObject;
    sortingObject.setStrategy(convertStringToEnum(argv[2]), array, array_size);
    if (sortingObject.getStrategy() == nullptr)
    {
        std::cerr << "Invalid algorithm!\n";
        return;
    }
    sortingObject.sort();

    // write to "output.txt"
    sortingObject.writeToFile("ouput.txt");

    SortContext compareObject;
    compareObject.setStrategy(convertStringToEnum(argv[2]), array, array_size);
    compareObject.sortWithComparison();

    // display
    std::cout << "ALGORITHM MODE\n";
    std::cout << "ALGORITHM: " << argv[2] << "\n";
    std::cout << "Input size: " << argv[3] << "\n";
    std::cout << "Input order: " << argv[4] << "\n";

    std::cout << "-------------------------\n";
    if (strcmp(argv[5], "-time") == 0 || strcmp(argv[5], "-both") == 0)
         std::cout << "Running Time: " << std::fixed << std::setprecision(5) << sortingObject.getDuration()
                      << " s\n";
    if (strcmp(argv[5], "-comp") == 0 || strcmp(argv[5], "-both") == 0)
        std::cout << "Comparisions: " << compareObject.getComparison() << "\n";

    // deallocation
    delete[] array;
}

void CommandLine2_CSV(int argc, const char* argv[], std::ofstream &ofs)
{
    int array_size = std::atoi(argv[3]);
    int *array = new int[array_size];
    if (strcmp(argv[4], "-rand") == 0)
    {
        GenerateRandomData(array, array_size);
    }
    else if (strcmp(argv[4], "-nsorted") == 0)
    {
        GenerateNearlySortedData(array, array_size);
    }
    else if (strcmp(argv[4], "-sorted") == 0)
    {
        GenerateSortedData(array, array_size);
    }
    else if (strcmp(argv[4], "-rev") == 0)
    {
        GenerateReverseData(array, array_size);
    }

    SortContext sortingObject;
    sortingObject.setStrategy(convertStringToEnum(argv[2]), array, array_size);
    if (sortingObject.getStrategy() == nullptr)
    {
        std::cerr << "Invalid algorithm!\n";
        return;
    }
    sortingObject.sort();

    // write to "output.txt"

    SortContext compareObject;
    compareObject.setStrategy(convertStringToEnum(argv[2]), array, array_size);
    compareObject.sortWithComparison();

    // display
    if (!ofs.is_open())
    {
        std::cout << "NOOOOOOOOO\n";
    }
    ofs << std::fixed << std::setprecision(5) << sortingObject.getDuration() << "s,";
    ofs << compareObject.getComparison() << ",";
    // deallocation
    delete[] array;
}

void CommandLine3(int argc, const char *argv[])
{
    int array_size = std::atoi(argv[3]);
    int *array = new int[array_size];
    std::string Orders[] = {"Randomize", "Nearly Sorted", "Sorted", "Reversed"};

    std::cout << "ALGORITHM MODE\n";
    std::cout << "ALGORITHM: " << argv[2] << "\n";
    std::cout << "Input size: " << argv[3] << "\n";

    int num[] = {0, 3, 1, 2};

    for (int i = 0; i < 4; i++)
    {
        GenerateData(array, array_size, num[i]);

        std::ofstream ofs("input_" + std::to_string(i + 1) + ".txt");
        ofs << array_size << "\n";
        for (int i = 0; i < array_size; i++)
        {
            ofs << array[i] << " ";
        }
        ofs.close();

        SortContext sortingObject;
        sortingObject.setStrategy(convertStringToEnum(argv[2]), array, array_size);
        if (sortingObject.getStrategy() == nullptr)
        {
            std::cerr << "Invalid algorithm!\n";
            break;
        }
        sortingObject.sort();

        SortContext compareObject;
        compareObject.setStrategy(convertStringToEnum(argv[2]), array, array_size);
        compareObject.sortWithComparison();

        // display
        std::cout << "\nInput order: " << Orders[i] << "\n";
        std::cout << "-------------------------\n";
        if (strcmp(argv[4], "-time") == 0 || strcmp(argv[4], "-both") == 0)
            std::cout << "Running Time: " << std::fixed << std::setprecision(5) << sortingObject.getDuration()
                      << " s\n";
        if (strcmp(argv[4], "-comp") == 0 || strcmp(argv[4], "-both") == 0)
            std::cout << "Comparisions: " << compareObject.getComparison() << "\n";
    }
    // deallocation
    delete[] array;
}

void CommandLine4(int argc, const char *argv[])
{
    // [Execution file] -c [Algorithm 1] [Algorithm 2] [Given input]
    // get input data
    std::ifstream ifs;
    int array_size;
    int *array = nullptr;

    ifs.open(argv[4]);
    ifs >> array_size;
    array = new int[array_size];
    for (int i = 0; i < array_size; ++i)
        ifs >> array[i];
    ifs.close();

    // sorting
    SortContext first_algo;
    first_algo.setStrategy(convertStringToEnum(argv[2]), array, array_size);
    SortContext second_algo;
    second_algo.setStrategy(convertStringToEnum(argv[3]), array, array_size);
    SortContext first_comparison;
    first_comparison.setStrategy(convertStringToEnum(argv[2]), array, array_size);
    SortContext second_comparison;
    second_comparison.setStrategy(convertStringToEnum(argv[3]), array, array_size);

    if (first_algo.getStrategy() == nullptr || second_algo.getStrategy() == nullptr)
    {
        std::cerr << "Invalid algorithm!\n";
        return;
    }

    first_algo.sort();
    second_algo.sort();
    first_comparison.sortWithComparison();
    second_comparison.sortWithComparison();

    // display
    std::cout << "COMPARE MODE\n";
    std::cout << "Algorithm: " << argv[2] << " | " << argv[3] << '\n';
    std::cout << "Input file: " << argv[4] << '\n';
    std::cout << "Input size: " << array_size << '\n';
    std::cout << "Running time: " << std::fixed << std::setprecision(5) << first_algo.getDuration() << " s | " << second_algo.getDuration() << " s\n";
    std::cout << "Comparisions: " << first_comparison.getComparison() << " | " << second_comparison.getComparison() << '\n';
}

void CommandLine5(int argc, const char *argv[])
{
    // [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
    int array_size = std::atoi(argv[4]);
    int *array = new int[array_size];
    const char* dataOrder[] = {"-rand", "-sorted", "-rev", "-nsorted", "undefined"};
    for (int i = 0; i < 5; ++i)
    {
        if (strcmp(dataOrder[i], argv[5]) == 0 || i == 4){
            GenerateData(array, array_size, i);
            break;
        }
    }

    const char* filename = "input.txt"; 
    writeArrayToFile(array, array_size, filename);
    SortContext first_algo;
    first_algo.setStrategy(convertStringToEnum(argv[2]), array, array_size);
    SortContext second_algo;
    second_algo.setStrategy(convertStringToEnum(argv[3]), array, array_size);
    SortContext first_comparison;
    first_comparison.setStrategy(convertStringToEnum(argv[2]), array, array_size);
    SortContext second_comparison;
    second_comparison.setStrategy(convertStringToEnum(argv[3]), array, array_size);

    if (first_algo.getStrategy() == nullptr || second_algo.getStrategy() == nullptr)
    {
        std::cerr << "Invalid algorithm!\n";
        return;
    }

    first_algo.sort();
    second_algo.sort();
    first_comparison.sortWithComparison();
    second_comparison.sortWithComparison();

    // display
    std::cout << "COMPARE MODE\n";
    std::cout << "Algorithm: " << argv[2] << " | " << argv[3] << '\n';
    std::cout << "Input Order: " << argv[5] << '\n';
    std::cout << "Input size: " << array_size << '\n';
    std::cout << "Running time: " << std::fixed << std::setprecision(5) << first_algo.getDuration() << " s | " << second_algo.getDuration() << " s\n";
    std::cout << "Comparisions: " << first_comparison.getComparison() << " | " << second_comparison.getComparison() << '\n';
}
