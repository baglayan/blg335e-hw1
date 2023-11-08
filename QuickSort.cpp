// BLG 335E Analysis of Algorithms Project 1
//
// Name: Meriç Bağlayan
// Id  : 150190056
// Date: 2023-11-08

#include <iostream>
#include <string.h>

using namespace std;

enum Args
{
    EXECUTABLE = 0,
    DATASET = 1,
    PIVOT_STRATEGY = 2,
    THRESHOLD = 3,
    OUTPUT = 4,
    VERBOSE = 5
};

void displayWrongUsageMessage(int argc, char **argv);
void displayWrongFileExtensionMessage();
void displayWrongPivotStrategyMessage();
void claHelp();
void claVersion();

int main(int argc, char **argv)
{
    // for (int i = 0; i < argc; i++) {
    //     cout << argv[i] << endl;
    //     cout << strcmp(argv[i], "--help") << endl;
    // }

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
        const char *validPivotStrategies = "lLrRmM";
        for (int i = 0; i < 7; i++)
        {
            if (argv[PIVOT_STRATEGY][0] == validPivotStrategies[i])
            {
                break;
            }
            else if (i == 6)
            {
                displayWrongPivotStrategyMessage();
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
    const char pivotStrategy = argv[PIVOT_STRATEGY][0];
    const int threshold = atoi(argv[THRESHOLD]);
    const string outputName = argv[OUTPUT];
    const bool verbose = argc == 6 && argv[VERBOSE][0] == 'v' ? true : false;

    return EXIT_SUCCESS;
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
        for (int i = 0; i <= argc; i++)
        {
            cerr << argv[i];
            if (i < argc)
            {
                cerr << ", ";
            }
            else
            {
                cerr << endl;
            }
        }
        cerr << ". Use '--help' to view the available commands." << endl;
    }
    return;
}

void displayWrongFileExtensionMessage()
{
    cerr << "Files for dataset and output should have the extension '.csv'." << endl;
    return;
}

void displayWrongPivotStrategyMessage()
{
    cerr << "You must specify a valid pivot strategy, see --help for details." << endl;
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