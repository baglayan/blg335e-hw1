// BLG 335E Analysis of Algorithms Project 1
//
// Name: Meriç Bağlayan
// Id  : 150190056
// Date: 2023-11-09

#include <chrono>
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

ofstream logFile("log.txt", ofstream::out);
bool verbose;

#pragma region Function declarations
/**
 * Function to swap two elements of type City in a vector<City>.
 * City &c1: First element to swap.
 * City &c2: Second element to swap.
 * Returns: None.
*/
void swapElements(City &c1, City &c2);

/**
 * Function to sort a vector<City> using insertion sort.
 * vector<City> &array: The vector to sort.
 * int n: The length of the vector.
 * Returns: None.
*/
void insertionSort(vector<City> &array, int n);

/**
 * Function to find the median of three given integers.
 * int i: First integer.
 * int j: Second integer.
 * int k: Third integer.
 * Returns: The median of the three integers.
 * Side effects: None.
*/
int findMedian(int i, int j, int k);

/**
 * Function to partition a vector<City> using a random element as the pivot.
 * vector<City> &array: The vector to partition.
 * int low: The lower bound of the vector.
 * int high: The upper bound of the vector.
 * Returns: The index of the pivot.
 * Side effects: None.
 *            Writes the pivot and the vector to the log file if verbose mode is enabled.
 *            See verboseLog() for more details.
*/
int randomizedPartition(vector<City> &array, int low, int high);

/**
 * Function to partition a vector<City> using the median of three random elements as the pivot.
 * vector<City> &array: The vector to partition.
 * int low: The lower bound of the vector.
 * int high: The upper bound of the vector.
 * Returns: The index of the pivot.
 * Side effects: None.
 *             Writes the pivot and the vector to the log file if verbose mode is enabled.
 *             See verboseLog() for more details.
*/
int medianPartition(vector<City> &array, int low, int high);

/**
 * Function to partition a vector<City> using the last element as the pivot.
 * vector<City> &array: The vector to partition.
 * int low: The lower bound of the vector.
 * int high: The upper bound of the vector.
 * Returns: The index of the pivot.
 * Side effects: None.
 *              Writes the pivot and the vector to the log file if verbose mode is enabled.
 *              See verboseLog() for more details.
*/
int partition(vector<City> &array, int low, int high);

/**
 * Function to sort a vector<City> using QuickSort.
 * vector<City> &array: The vector to sort.
 * int low: The lower bound of the vector.
 * int high: The upper bound of the vector.
 * int strategy: The pivot strategy to use.
 * Returns: None.
 * Side effects: None.
*/
void quickSort(vector<City> &array, int low, int high, int strategy);

/**
 * Function to sort a vector<City> using hybrid sort.
 * vector<City> &array: The vector to sort.
 * int low: The lower bound of the vector.
 * int high: The upper bound of the vector.
 * int threshold: The threshold value for hybrid sort.
 * int strategy: The pivot strategy to use.
 * Returns: None.
 *             Calls insertionSort() if the length of the vector is less than or equal to the threshold value.
 *            See insertionSort() for more details.
*/
void hybridSort(vector<City> &array, int low, int high, int threshold, int strategy);

/**
 * Function to print the pivot and the vector to the log file if verbose mode is enabled.
 * vector<City> array: The vector to print.
 * int length: The length of the vector.
 * int pivot: The pivot to print.
 * ofstream &logFile: The log file to print to.
 * bool verbose: The verbose mode flag.
 * Returns: None.
*/
void verboseLog(vector<City> array, int length, int pivot, ofstream &logFile, bool verbose);

/**
 * Function to display the time taken by QuickSort with the given pivot strategy and threshold value.
 * char strategy: The pivot strategy that was used.
 * int threshold: The threshold value that was used.
 * auto time: The time taken by QuickSort.
 * Returns: None.
*/
void displayTimeElapsed(char strategy, int threshold, auto time);

/**
 * Function to display the wrong usage message.
 * int argc: Number of command line arguments.
 * char **argv: Array of command line arguments.
 * Returns: None.
*/
void displayWrongUsageMessage(int argc, char **argv);

/**
 * Function to display the wrong file extension message.
 * Returns: None.
*/
void displayWrongFileExtensionMessage();

/**
 * Function to display the wrong strategy message.
 * Returns: None.
*/
void displayWrongStrategyMessage();

/**
 * Function to display the help message.
 * Returns: None.
*/
void claHelp();

/**
 * Function to display the version message.
 * Returns: None.
*/
void claVersion();
#pragma endregion

/**
 * Main driver function.
 * int argc: Number of command line arguments.
 * char **argv: Array of command line arguments.
 * Returns: EXIT_SUCCESS (0) if the program runs successfully, EXIT_FAILURE (1) otherwise.
*/
int main(int argc, char **argv)
{
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
    verbose = argc == 6 && (argv[VERBOSE][0] == 'v' || argv[VERBOSE][0] == 'V') ? true : false;

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
        istringstream stream(firstLine);
        City city;
        getline(stream, city.name, ';');
        stream >> city.population;
        cities.push_back(city);
    }

    string line;
    while (getline(datasetFile, line))
    {
        istringstream stream(line);
        City city;
        getline(stream, city.name, ';');
        stream >> city.population;
        cities.push_back(city);
    }

    datasetFile.close();

    auto start = chrono::high_resolution_clock::now();

    switch (threshold)
    {
    case 1:
        quickSort(cities, 0, cities.size() - 1, strategy);
        break;
    default:
        hybridSort(cities, 0, cities.size() - 1, threshold, strategy);
        break;
    }

    auto end = chrono::high_resolution_clock::now();
    auto timeElapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);

    displayTimeElapsed(argv[STRATEGY][0], threshold, timeElapsed.count());

    logFile.close();

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
void swapElements(City &c1, City &c2)
{
    City temp = c1;
    c1 = c2;
    c2 = temp;
}
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
            swapElements(array[i], array[j]);
        }
    }
    swapElements(array[high], array[i + 1]);
    verboseLog(array, high, pivot.population, logFile, verbose);
    return i + 1;
}

int randomizedPartition(vector<City> &array, int low, int high)
{
    srand(time(0));
    int pivot = (rand() % (high - low + 1)) + low;
    swapElements(array[high], array[pivot]);
    return partition(array, low, high);
}

int medianPartition(vector<City> &array, int low, int high)
{
    srand(time(0));
    int i = (rand() % (high - low + 1)) + low;
    int j = (rand() % (high - low + 1)) + low;
    int k = (rand() % (high - low + 1)) + low;
    swapElements(array[high], array[findMedian(i, j, k)]);
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
        int pivotIndex;
        switch (strategy)
        {
        case LAST:
            pivotIndex = partition(array, low, high);
            break;
        case RANDOM:
            pivotIndex = randomizedPartition(array, low, high);
            break;
        case MEDIAN:
            pivotIndex = medianPartition(array, low, high);
            break;
        default:
            break;
        }

        quickSort(array, low, pivotIndex - 1, strategy);
        quickSort(array, pivotIndex + 1, high, strategy);
    }
}

/**
 * Function to sort a vector<City> using hybrid sort.
 * vector<City> &array: The vector to sort.
 * int low: The lower bound of the vector.
 * int high: The upper bound of the vector.
 * int threshold: The threshold value for hybrid sort.
 * int strategy: The pivot strategy to use.
 * Returns: None.
 * Side effects: None.
 * 
*/
void hybridSort(vector<City> &array, int low, int high, int threshold, int strategy)
{
    if (high - low + 1 > threshold)
    {
        if (low < high)
        {
            int pivotIndex;
            switch (strategy)
            {
            case LAST:
                pivotIndex = partition(array, low, high);
                break;
            case RANDOM:
                pivotIndex = randomizedPartition(array, low, high);
                break;
            case MEDIAN:
                pivotIndex = medianPartition(array, low, high);
                break;
            default:
                break;
            }

            hybridSort(array, low, pivotIndex - 1, threshold, strategy);
            hybridSort(array, pivotIndex + 1, high, threshold, strategy);
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

void displayTimeElapsed(char strategy, int threshold, auto time)
{
    cout << "Time taken by QuickSort with pivot strategy '" << strategy << "' and threshold " << threshold << ": "
         << time << " ns." << endl;
}


void verboseLog(vector<City> array, int length, int pivot, ofstream &logFile, bool verbose)
{
    if (verbose)
    {
        logFile << "Pivot: " << pivot << " Array: ";
        logFile << "[";
        for (int i = 1; i <= length; i++)
        {
            logFile << array[i].population;
            if (i < length)
            {
                logFile << ", ";
            }
            else
            {
                logFile << "]" << endl;
            }
        }
    }
}

void claHelp()
{
    cout << "Usage: ./QuickSort <DATASET-FILE-NAME>.csv <l|r|m> <THRESHOLD VALUE> <OUTPUT-FILE-NAME>.csv [v]" << endl;
    cout << "Options:" << endl;
    cout << "  <DATASET-FILE-NAME>.csv: The name of the dataset file in CSV format." << endl;
    cout << "  <l|r|m>: The pivot strategy to use for QuickSort. 'l' for last element, 'r' for random, 'm' for median of three random." << endl;
    cout << "  <THRESHOLD VALUE>: The threshold value for hybrid sort. Elements below this threshold will be sorted using insertion sort." << endl;
    cout << "  <OUTPUT-FILE-NAME>.csv: The name of the output file to store the sorted dataset in CSV format." << endl;
    cout << "  [v]: Optional flag to enable verbose mode. Displays additional information during sorting." << endl;
    return;
}

void claVersion()
{
    cout << "==============================================" << endl;
    cout << "BLG 335E Analysis of Algorithms I Project 1" << endl;
    cout << "QuickSort" << endl;
    cout << "Submitted Version" << endl;
    cout << "==============================================" << endl;

    cout << "                      ,////," << endl;
    cout << "                      /// 6|" << endl;
    cout << "                      //  _|" << endl;
    cout << "                     _/_,-'" << endl;
    cout << "                _.-/'/   \\   ,/;," << endl;
    cout << "             ,-' /'  \\_   \\ / _/" << endl;
    cout << "             `\\ /     _/\\  ` /" << endl;
    cout << "               |     /,  `\\_/" << endl;
    cout << "               |     \\'" << endl;
    cout << "   /\\_        /`      /\\" << endl;
    cout << " /' /_``--.__/\\  `,. /  \\" << endl;
    cout << "|_/`  `-._     `\\/  `\\   `." << endl;
    cout << "          `-.__/'     `\\   |" << endl;
    cout << "                        `\\  \\" << endl;
    cout << "                          `\\ \\" << endl;
    cout << "                            \\_\\__" << endl;
    cout << "                             \\___)" << endl;
    return;
}
#pragma endregion