//Grep ohjelma
#include <iostream>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

void options_line_numbering_occurances(string, ifstream&);
void options_line_numbering(string, ifstream&);
void options_occurances(string, ifstream&);
void options_reverse(string, ifstream&);
void options_ignore_case(string, ifstream&);
void options_everything(string, ifstream&);
bool finding_occurances(string, string);

int main(int argc, char* argv[]) {
    if (argc == 1) {

        string statement, characters;
        size_t position;

        cout << "Give a string from which to search for: ";
        getline(cin, statement);

        cout << "Give search string: ";
        getline(cin, characters);

        position = statement.find(characters); // Finds if string characters is included in string statement which results to the starting position of the found string.
        // Compares the found position to string null position if they are not the same string statement includes string characters.
        if (position != string::npos) {
            cout << "\"" << characters << "\" found in \"" << statement << "\" in position " << position << endl;
        }

        else {
            cout << "\"" << characters << "\" can't be found in \"" << statement << "\"\n";
        }
    }

    else if (argc == 3) {
        string wordtofind = argv[1], line;
        ifstream inputFile;
        bool found = false;

        inputFile.open(argv[2]);

        if (inputFile) {
            // Does this if open was succesfull.

            while (getline(inputFile, line)) {
                //Goes through the file line by line.
                if (line.find(wordtofind) != string::npos) {
                    cout << line << endl;
                    found = true;
                }
            }

            // If nothing was found prints this.
            if (found == false) {
                cout << "\"" << wordtofind << "\" can't be found in the file\n";
            }

            inputFile.close();
        }
        // If file couldn't be opened.
        else {
            cout << "Error opening the file.\n";
        }
    }

    else if (argc == 4) {
        string wordtofind = argv[2], option = argv[1];
        ifstream inputFile;

        // Ensures that nothing goes wrong opening the file.
        try {
            inputFile.open(argv[3]);
            // If file can't be opened.
            if (!inputFile) {
                throw - 1;
            }
        }
        catch (int e) {
            // Exeption for file not opening correctly.
            cout << "An exception occurred. Exception Nr. " << e << endl;
            cout << "File " << "\"" << argv[3] << "\"" << " could not be found\n";
            return 1;
        }

        if (option == "-ol") {
            options_line_numbering(wordtofind, inputFile);
        }

        else if (option == "-oo") {
            options_occurances(wordtofind, inputFile);
        }

        else if (option == "-olo") {
            options_line_numbering_occurances(wordtofind, inputFile);
        }

        else if (option == "-or") {
            options_reverse(wordtofind, inputFile);
        }

        else if (option == "-oi") {
            options_ignore_case(wordtofind, inputFile);
        }

        else if (option == "-olori") {
            options_everything(wordtofind, inputFile);
        }

        inputFile.close();
    }

    // If user gives wrong number of arguments in the cmd line.
    else {
        cout << "Wrong number of cmd line arguments given.\n";
    }

    return 0;
}

void options_line_numbering_occurances(string word, ifstream& file) {
    int counter = 0, line_number = 0;
    string line;
    bool found = false;

    while (getline(file, line)) {
        line_number++; // Counts the line numbers.

        if (line.find(word) != string::npos) {
            cout << line_number << ":\t" << line << endl;
            found = true;
            counter++; // Counts the amount of lines found containing the given string.
        }
    }

    cout << "\nOccurrences of lines containing \"" << word << "\": " << counter << endl;

    if (found == false) {
        cout << "\"" << word << "\" can't be found in the file\n";
    }
}

void options_line_numbering(string word, ifstream& file) {
    int line_number = 0;
    string line;
    bool found = false;

    while (getline(file, line)) {
        line_number++;

        if (line.find(word) != string::npos) {
            cout << line_number << ":\t" << line << endl;
            found = true;
        }
    }

    if (found == false) {
        cout << "\"" << word << "\" can't be found in the file\n";
    }
}
void options_occurances(string word, ifstream& file) {
    int counter = 0;
    string line;
    bool found = false;

    while (getline(file, line)) {

        if (line.find(word) != string::npos) {
            cout << line << endl;
            found = true;
            counter++;
        }
    }

    cout << "\nOccurrences of lines containing \"" << word << "\": " << counter << endl;

    if (found == false) {
        cout << "\"" << word << "\" can't be found in the file\n";
    }
}

void options_reverse(string word, ifstream& file) {
    string line;
    bool found;

    while (getline(file, line)) {
        found = false;
        if (line.find(word) != string::npos) {
            found = true;
        }

        // Prints everything unless the string is found.
        if (found == false) {
            cout << line << endl;
        }
    }
}

void options_ignore_case(string word, ifstream& file) {
    string line;
    bool notfound = true;

    while (getline(file, line)) {
        if (finding_occurances(word, line) == true) {
            cout << line << endl;
            notfound = false;
        }
    }

    if (notfound == true) {
        cout << "\"" << word << "\" can't be found in the file\n";
    }
}

bool finding_occurances(string word, string fileline) {
    bool found;
    // Transforms parameter strings to lowercase.
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    transform(fileline.begin(), fileline.end(), fileline.begin(), ::tolower);

    if (fileline.find(word) != string::npos) {
        found = true;
    }
    else {
        found = false;
    }

    return found;
}

void options_everything(string word, ifstream& file) {
    int counter = 0, line_number = 0;
    string line;
    bool found;

    while (getline(file, line)) {
        found = false;
        line_number++;

        if (finding_occurances(word, line) == true) {
            found = true;
            counter++;
        }

        if (found == false) {
            cout << line_number << ":" << line << endl;
        }
    }

    cout << "\nOccurrences of lines NOT containing \"" << word << "\": "
        << line_number - counter << endl;
}