#include "lexer.h"
#include "output.h"
#include "parser.h"
#include "version.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

string
getMode(const int argc, const char **argv) {
    if (argc == 1)
        return "interactive";
    else if (string(argv[1]) == "-v" || string(argv[1]) == "--version")
        return "version";
    else if (string(argv[1]) == "-h" || string(argv[1]) == "--help")
        return "help";
    else
        return "command";
}

void
printUsage() {
    cout << "Usage: micro1-as                (interactive mode)" << endl;
    cout << " Or  : micro1-as <source_code>  (command mode)" << endl;
    cout << " Or  : micro1-as (-v|--version) (print version)" << endl;
    cout << " Or  : micro1-as (-h|--help)    (help mode; print this message)" << endl;
}

string
removeExtension(const string filename) {
    if (string::size_type pos = filename.find_last_of("."); pos != std::string::npos) {
        return filename.substr(0, pos);
    }
    else {
        return filename;
    }
}

bool
assemble(const string filename, const bool flagWritingListingFile) {
    std::ifstream ifs(filename);
    if (ifs.fail()) {
        cerr << "ERROR: FILE NOT FOUND" << endl;
        return false;
    }

    auto tokens = micro1::tokenize(ifs);
    auto lines  = micro1::parse(tokens);
    
    if (flagWritingListingFile) {
        micro1::writeListingFile(lines, removeExtension(filename) + ".a");
    }
    else {
        micro1::printSyntaxError(lines);
    }

    return micro1::writeObjectFile(lines, removeExtension(filename) + ".b");
}

int
main(const int argc, const char **argv) {
    auto mode = getMode(argc, argv);

    if (mode == "help") {
        printUsage();
    }
    else if (mode == "version") {
        micro1::printVersion();
    }
    else if (mode == "interactive") {
        micro1::printVersion();

        char yn;
        string line;
        do {
            cout << endl << " SOURCE FILE NAME ? ";
            string filename;
            std::getline(cin, filename);

            cout << endl << " START ?";
            std::getline(cin, line);
            if (assemble(filename, true)) {
                cout << " NORMAL TERMINATION !" << endl;
            }

            cout << endl << " CONTINUE ? ";
            do {
                cout << "(Y/N):";
                std::getline(cin, line);
                yn = (line.length() > 0) ? std::tolower(line[0]) : 0;
            } while (yn != 'y' && yn != 'n');
        } while (yn == 'y');
    }
    else if (mode == "command") {
        if (!assemble(string(argv[1]), false))
            return 1;
    }

    return 0;
}