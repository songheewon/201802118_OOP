#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <iterator>
#include <sstream>
#include "UI.h"
#include "ShiftPage.h"
#include "fileUsing.h"

#define MAXBYTE 75
#define FILE_NAME "test.txt"
#define SAVING_FILE_NAME "save.txt"

using namespace std;

class fileUsing {
private:
    vector<string> splitWords;
    vector<int> wordLength;
    vector<string> splitLine;
    vector<int> lineNum;
    string fileName;
public:
    fileUsing(string fileName);
    string fileRead();
    vector<string> getWords();
    vector<int> getWordLength();
    vector<string> getLine();
    vector<int> getLineNum();
    
};

fileUsing::fileUsing(string fileName) {
    this->fileName = fileName;
}

string fileUsing::fileRead() {
    ifstream read(this->fileName);
    string toReturn;
    if (read.is_open()) {
        string buf;
        while (!read.eof()) {
            getline(read, buf);
            toReturn += buf;
        }
    }
    else {
        cout << "** Cannot Open The File **" << endl;
    }
    read.close();
    ofstream write(SAVING_FILE_NAME);
    if (write.is_open()) {
        write << toReturn;
    }
    else {
        cout << "** Cannot Open The File **" << endl;
    }
    write.close();
    return toReturn;
}

vector<string> fileUsing::getWords() { // Split to Words
    string text = fileRead();
    istringstream ss(text);
    string buf;
    while (getline(ss, buf, ' ')) {
        splitWords.push_back(buf);
    }
    return splitWords;
}

vector<int> fileUsing::getWordLength() { // Calculate Length of Words
    this->getWords();
    for (int i = 0; i < this->splitWords.size(); i++) {
        wordLength.push_back(splitWords[i].size());
    }
    return wordLength;
}

vector<string> fileUsing::getLine() {
    this->getWordLength();
    string line = "";
    int stackLength = 0;
    int wordCnt = 0;
    for (int i = 0; i < this->splitWords.size(); i++) {
        wordCnt++; // To Check Spacing
        stackLength += wordLength[i];
        if (stackLength + wordCnt > MAXBYTE) { // Should Think about Spacing
            splitLine.push_back(line);
            line = "";
            stackLength = 0;
            wordCnt = 0;
            i--;
        }
        else {
            line += splitWords[i] + " ";
            if (i == this->splitWords.size() - 1) {
                splitLine.push_back(line);
            }
        }
    }
    return splitLine;
}

vector<int> fileUsing::getLineNum() {
    this->getLine();
    for (int i = 0; i < this->splitLine.size(); i++) {
        lineNum.push_back(i + 1);
    }
    return lineNum;
}

class UI {
private:
    string toSave;
public:
    UI();
    void prettyPrint(int line, string message);
    void goToNextPage(int currentLine);
    void goToPreviousPage(int currentLine);
    void SaveAndTerminate();
};

UI::UI() {
    toSave = "";
    prettyPrint(0, "");
}

void UI::prettyPrint(int line, string message) {
    system("cls");
    for (int i = 0; i < 20; i++) {
        fileUsing file(SAVING_FILE_NAME);
        if (line + i > file.getLine().size() - 1) { // Last Line
            break;
        }
        if (line + i < 9) {
            cout << " " << file.getLineNum()[line + i] << "| " << file.getLine()[line + i] << endl;
        }
        else {
            cout << file.getLineNum()[line + i] << "| " << file.getLine()[line + i] << endl;
        }
    }
    cout << endl << endl;
    cout << "======================================================================================" << endl;
    cout << "n: next page, p: previous page, i: insert, d: delete, s: search, t: save and terminate" << endl;
    cout << "======================================================================================" << endl;
    cout << "Console Message : " << message << endl;
    cout << "======================================================================================" << endl;
    cout << "Input : ";
    string input;
    try {
        cin >> input;
        if(input.at(0) != 'n' && input.at(0) != 'p'
            && input.at(0) != 'i' && input.at(0) != 'd'
            && input.at(0) != 's' && input.at(0) != 't')
        throw input;
    }
    catch (char exception) {
        prettyPrint(line, "Not Accepted Command");
    }

    switch (input.at(0)) {
    case 'n':
        goToNextPage(line);
        break;
    case 'p':
        goToPreviousPage(line);
        break;
    case 'i':
        // insert
        break;
    case 'd':
        // delete
        break;
    case 's':
        // search
        break;
    case 't':
        //terminate
        break;
    }
    
}

void UI::goToNextPage(int currentLine) {
    fileUsing file(SAVING_FILE_NAME);
    if (currentLine + 20 > file.getLine().size()) {
        UI::prettyPrint(currentLine, "Last Page");
    }
    else {
        UI::prettyPrint(currentLine + 20, "Command Success");
    }
}

void UI::goToPreviousPage(int currentLine) {
    if (currentLine - 20 < 0) {
        if (currentLine == 0) {
            prettyPrint(currentLine, "First Page");
        }
        else {
            prettyPrint(0, "Command Success");
        }
    }
    else {
        prettyPrint(currentLine - 20, "Command Success");
    }
}

void UI::SaveAndTerminate() {
    ofstream write(SAVING_FILE_NAME);
    if (write.is_open()) {
        write << this->toSave;
    }
    else {
        cout << "** Cannot Open The File **" << endl;
    }
    write.close();
}

int main() {
    UI ui;
    return 0;
}
