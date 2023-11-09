// BLG 335E Analysis of Algorithms Project 1
//
// Name: Meriç Bağlayan
// Id  : 150190056
// Date: 2023-11-08

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <time.h>

using namespace std;

enum Args
{
    EXECUTABLE = 0,
    DATASET = 1,
    STRATEGY = 2,
    THRESHOLD = 3,
    OUTPUT = 4,
    VERBOSE = 5
};

enum Strategies
{
    LAST = 0,
    RANDOM = 1,
    MEDIAN = 2
};

struct City
{
    string name;
    int population;
};

#pragma region Function declarations
void insertionSort(vector<City> &array, int n);
int findMedian(int i, int j, int k);
int randomizedPartition(vector<City> &array, int low, int high);
int medianPartition(vector<City> &array, int low, int high);
int partition(vector<City> &array, int low, int high);
void quickSort(vector<City> &array, int low, int high, int strategy);
void hybridSort(vector<City> &array, int low, int high, int threshold, int strategy);

void displayWrongUsageMessage(int argc, char **argv);
void displayWrongFileExtensionMessage();
void displayWrongStrategyMessage();
void claHelp();
void claVersion();
#pragma endregion

int main(int argc, char **argv)
{
    // for (int i = 0; i < argc; i++) {
    //     cout << argv[i] << endl;
    //     cout << strcmp(argv[i], "--help") << endl;
    // }

    // vector<City> testQS = {5, 1, 24, 23, 90, 55};

    // hybridSort(testQS, 0, 5, 9, MEDIAN);

    // for (int i = 0; i < 6; i++)
    // {
    //     cout << testQS[i] << endl;
    // }

    int strategy;

    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        claHelp();
        return EXIT_SUCCESS;
    }
    else if (argc == 2 && strcmp(argv[1], "--version") == 0)
    {
        claVersion();
        return EXIT_SUCCESS;
    }
    else if (argc < 5 || argc > 6)
    {
        displayWrongUsageMessage(argc, argv);
        return EXIT_FAILURE;
    }
    else
    {
        const char *validStrategies = "lLrRmM";
        for (int i = 0; i < 7; i++)
        {
            if (argv[STRATEGY][0] == validStrategies[i])
            {
                if (i < 2)
                    strategy = LAST;
                else if (i >= 2 && i < 4)
                    strategy = RANDOM;
                else if (i >= 4 && i < 6)
                    strategy = MEDIAN;
                break;
            }
            else if (i == 6)
            {
                displayWrongStrategyMessage();
                return EXIT_FAILURE;
            }
        }
    }
    const char *DATASET_ARGUMENT = argv[DATASET];
    const char *OUTPUT_ARGUMENT = argv[OUTPUT];

    const char *DATASET_EXTENSION = DATASET_ARGUMENT + strlen(DATASET_ARGUMENT) - 4;
    const char *OUTPUT_EXTENSION = OUTPUT_ARGUMENT + strlen(OUTPUT_ARGUMENT) - 4;

    bool areFileExtensionsCorrect = strcmp(DATASET_EXTENSION, ".csv") == 0 && strcmp(OUTPUT_EXTENSION, ".csv") == 0;
    if (!areFileExtensionsCorrect)
    {
        displayWrongFileExtensionMessage();
        return EXIT_FAILURE;
    }

    const string datasetName = argv[DATASET];
    const int threshold = atoi(argv[THRESHOLD]);
    const string outputName = argv[OUTPUT];
    const bool verbose = argc == 6 && (argv[VERBOSE][0] == 'v' || argv[VERBOSE][0] == 'V') ? true : false;

    ifstream datasetFile(datasetName);

    if (!datasetFile.is_open())
    {
        cerr << "Could not open the dataset file " << datasetName << "." << endl;
        return EXIT_FAILURE;
    }

    vector<City> cities;

    string firstLine;
    getline(datasetFile, firstLine);

    if (!firstLine.empty() && firstLine[0] == '\xEF' && firstLine[1] == '\xBB' && firstLine[2] == '\xBF')
    {
        firstLine.erase(0, 3);
        istringstream iss(firstLine);
        City city;
        getline(iss, city.name, ';');
        iss >> city.population;
        cities.push_back(city);

    }

    string line;
    while (getline(datasetFile, line))
    {
        istringstream iss(line);
        City city;
        getline(iss, city.name, ';');
        iss >> city.population;
        cities.push_back(city);
    }

    datasetFile.close();

    switch (threshold)
    {
    case 1:
        quickSort(cities, 0, cities.size() - 1, strategy);
        break;
    default:
        hybridSort(cities, 0, cities.size() - 1, threshold, strategy);
        break;
    }

    ofstream outputFile(outputName, ofstream::out);

    if (!outputFile.is_open())
    {
        cerr << "Could not open the output file " << outputName << "." << endl;
        return EXIT_FAILURE;
    }

    for (const auto &city : cities)
    {
        outputFile << city.name << ";" << city.population << endl;
    }

    outputFile.close();

    return EXIT_SUCCESS;
}

#pragma region Sorting functions
void insertionSort(vector<City> &array, int n)
{
    for (int i = 1; i < n; i++)
    {
        City key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j].population > key.population)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int partition(vector<City> &array, int low, int high)
{
    City pivot = array[high];
    int i = low - 1;
    for (int j = low; j <= high; j++)
    {
        if (array[j].population < pivot.population)
        {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[high], array[i + 1]);
    return i + 1;
}

int randomizedPartition(vector<City> &array, int low, int high)
{
    srand(time(0));
    int pivot = (rand() % (high - low + 1)) + low;
    swap(array[high], array[pivot]);
    return partition(array, low, high);
}

int medianPartition(vector<City> &array, int low, int high)
{
    srand(time(0));
    int i = (rand() % (high - low + 1)) + low;
    int j = (rand() % (high - low + 1)) + low;
    int k = (rand() % (high - low + 1)) + low;
    swap(array[high], array[findMedian(i, j, k)]);
    return partition(array, low, high);
}

// Lightning fast sorting for 3 elements.
// Only three comparisons and no swaps
int findMedian(int i, int j, int k)
{
    if (i < j)
        if (i < k)
            if (j < k)
                return j;
            else
                return k;
        else
            return i;
    else if (i > k)
        if (j > k)
            return j;
        else
            return k;
    else
        return i;
}

void quickSort(vector<City> &array, int low, int high, int strategy)
{
    if (low < high)
    {
        int border;
        switch (strategy)
        {
        case LAST:
            border = partition(array, low, high);
            break;
        case RANDOM:
            border = randomizedPartition(array, low, high);
            break;
        case MEDIAN:
            border = medianPartition(array, low, high);
            break;
        default:
            break;
        }

        quickSort(array, low, border - 1, strategy);
        quickSort(array, border + 1, high, strategy);
    }
}

void hybridSort(vector<City> &array, int low, int high, int threshold, int strategy)
{
    if (high > threshold)
    {
        if (low < high)
        {
            int border;
            switch (strategy)
            {
            case LAST:
                border = partition(array, low, high);
                break;
            case RANDOM:
                border = randomizedPartition(array, low, high);
                break;
            case MEDIAN:
                border = medianPartition(array, low, high);
                break;
            default:
                break;
            }

            hybridSort(array, low, border - 1, threshold, strategy);
            hybridSort(array, border + 1, high, threshold, strategy);
        }
    }
    else
    {
        insertionSort(array, high);
    }
}
#pragma endregion

#pragma region Command line argument handler functions
void displayWrongFileExtensionMessage()
{
    cerr << "Files for dataset and output should have the extension '.csv'." << endl;
    return;
}

void displayWrongStrategyMessage()
{
    cerr << "You need to specify a valid pivot strategy, see --help for details." << endl;
}

void displayWrongUsageMessage(int argc, char **argv)
{
    switch (argc)
    {
    case 1:
        cerr << "Error: You need to specify commands before moving on. Use '--help' to view the available commands." << endl;
        break;
    case 2:
        cerr << "Error: Unknown argument: " << argv[1] << ". Use '--help' to view the available commands." << endl;
        break;
    default:
        cerr << "Error: Unknown arguments: ";
        for (int i = 1; i <= argc; i++)
        {
            cerr << argv[i];
            if (i < argc - 1)
            {
                cerr << ", ";
            }
            else
            {
                cerr << ". Use '--help' to view the available commands." << endl;
            }
        }
    }
    return;
}

void claHelp()
{
    cout << "Usage: ./QuickSort <DATASET-FILE-NAME>.csv <l|r|m> <THRESHOLD VALUE> <OUTPUT-FILE-NAME>.csv [v]" << endl;
    return;
}

void claVersion()
{
    cout << "BLG 335E Analysis of Algorithms I Project 1 in development" << endl;
    return;
}
#pragma endregion