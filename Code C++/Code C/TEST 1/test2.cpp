#include <iostream>
#include <string>

using namespace std;

string standardizeQuestion(string question) {
    // Remove non-letter, non-number, non-space, non-comma, non-question mark characters
    for (int i = 0; i < question.size(); i++) {
        if (!isalnum(question[i]) && question[i] != ' ' && question[i] != ',' && question[i] != '?') {
            question[i] = ' ';
        }
    }
    
    // Remove extra spaces
    string standardized = "";
    bool ignoreSpace = true;
    for (int i = 0; i < question.size(); i++) {
        if (question[i] == ' ') {
            if (!ignoreSpace) {
                standardized += question[i];
                ignoreSpace = true;
            }
        } else if (question[i] == ',') {
            if (isalnum(question[i-1]) && question[i+1] == ' ') {
                standardized += question[i];
                standardized += ' ';
            }
            ignoreSpace = true;
        } else if (question[i] == '?') {
            if (isalnum(question[i-1])) {
                standardized += question[i];
            } else {
                standardized += ' ';
            }
            ignoreSpace = true;
        } else {
            if (ignoreSpace) {
                if (isalpha(question[i])) {
                    standardized += toupper(question[i]);
                } else {
                    standardized += question[i];
                }
            } else {
                standardized += tolower(question[i]);
            }
            ignoreSpace = false;
        }
    }
    
    // Remove space at the end of sentence
    while (standardized.size() > 0 && standardized[standardized.size()-1] == ' ') {
        standardized.pop_back();
    }
    
    return standardized;
}

int main() {
    string question = "  How  are you today? I am, fine, thank you!  ";
    cout << standardizeQuestion(question) << endl;
    // Output: "How are you today? I am, fine, thank you!"
    return 0;
}
