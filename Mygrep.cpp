//Grep ohjelma
#include <iostream>
#include<string>
#include<fstream>

using namespace std;

void options_line_numbering_occurances(string, ifstream &);
void options_line_numbering(string, ifstream&);
void options_occurances(string, ifstream&);

int main(int argc, char* argv[]) { 
    if (argc == 1) {

        string statement, characters;
        int position;

        cout << "Give a string from which to search for: ";
        getline(cin, statement);

        cout << "Give search string: ";
        getline(cin, characters);

        position = statement.find(characters);
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
            while (getline(inputFile, line)) {
                if (line.find(wordtofind) != string::npos) {
                    cout << line << endl;
                    found = true;
                }
            }
            
            if (found == false) {
                cout << "\"" << wordtofind << "\" can't be found in the file\n";
            }

            inputFile.close();
        }
        else {
            cout << "Error opening the file.\n";
        }
    }

    else if (argc == 4) {
        string wordtofind = argv[2], option = argv[1];
        ifstream inputFile;

        inputFile.open(argv[3]);

        if (inputFile) {

            if (option == "-ol") {
                options_line_numbering(wordtofind, inputFile);
            }

            else if (option == "-oo") {
                options_occurances(wordtofind, inputFile);
            }

            else if (option == "-olo") {
                options_line_numbering_occurances(wordtofind, inputFile);
            }

            inputFile.close();
        }
        else {
            cout << "Error opening the file.\n";
        }
    }
    

    else {
        cout << "Wrong cmd line arguments given.\n";
    }

    return 0;
}

void options_line_numbering_occurances(string word, ifstream& file) {
    int counter = 0, line_number = 0;
    string line;
    bool found = false;

    while (getline(file, line)) {
        line_number++;

        if (line.find(word) != string::npos) {
            cout << line_number << ":\t" << line << endl;
            found = true;
            counter++;
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