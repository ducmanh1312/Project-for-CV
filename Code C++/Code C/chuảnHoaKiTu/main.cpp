#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
using namespace std;

#include <algorithm>

string standardizeQuestion(string question)
{
    // Remove non-letter, non-number, non-space, non-comma, non-question mark characters
    for (int i = 0; i < question.size(); i++)
    {
        if (!isalnum(question[i]) && question[i] != ' ' && question[i] != ',' && question[i] != '?')
        {
            question[i] = ' ';
        }
    }

    // Remove space at the beginning and end of the sentence
    while (question.front() == ' ')
        question.erase(question.begin());
    while (question.back() == ' ')
        question.pop_back();

    // Capitalize first letter of each sentence and make all other letters lowercase
    for (int i = 0; i < question.size(); i++)
    {
        if (isalpha(question[i]))
        {
            if (i == 0)
                question[i] = toupper(question[i]);
            else
                question[i] = tolower(question[i]);
        }
    }

    // Remove extra spaces
    question.erase(unique(question.begin(), question.end(),
                          [](char a, char b)
                          { return a == b && a == ' '; }),
                   question.end());

    // Ensure there is a letter or number after a space
    for (int i = 0; i < question.size(); i++)
    {
        if (question[i] == ' ' && (i == 0 || !isalnum(question[i - 1])) && !isalnum(question[i + 1]))
        {
            question.erase(question.begin() + i);
            i--;
        }
    }

    // Ensure there is a letter or number before a comma and only 1 space after a comma
    for (int i = 0; i < question.size(); i++)
    {
        if (question[i] == ',')
        {
            if (i < question.length() - 1 && question[i + 1] != ' ')
            {
                question.insert(i + 1, " ");
                
            }

            if (!isalnum(question[i - 1]))
            {
                question.erase(question.begin() + i - 1);
            }
        }
    }

    // Add a question mark to the end of the sentence if it is missing,
    // or replace a question mark in the middle of the sentence with a space
    if (question[question.size() - 1] != '?')
    {
        question += '?';
    }
    for (int i = 0; i < question.size() - 1; i++)
    {
        if (question[i] == '?')
        {
            question[i] = ' ';
        }
    }

    // Remove extra spaces
    question.erase(unique(question.begin(), question.end(),
                          [](char a, char b)
                          { return a == b && a == ' '; }),
                   question.end());

    while(!isalpha(question[question.size()-2])) 
    {
        question.erase(question.end()-2);
    }
        

    return question;
}
/*






    // Ensure there is a letter or number after a space
    for (int i = 0; i < question.size(); i++) {
        if (question[i] == ' ' && (i == 0 || !isalnum(question[i-1])) && !isalnum(question[i+1])) {
            question.erase(question.begin()+i);
            i--;
        }
    }


    // Add a question mark to the end of the sentence if it is missing,
    // or replace a question mark in the middle of the sentence with a space
    if (question[question.size()-1] != '?') {
        question += '?';
    } else {
        for (int i = 0; i < question.size()-1; i++) {
            if (question[i] == '?' && question[i+1] != ' ') {
                question[i] = ' ';
            }
        }
    }


}
*/

int main()
{
    string question = " this  is not   a     relevant question , is it???";
    cout << standardizeQuestion(question) << endl;
    // Output: "How are you today? I am, fine, thank you?"
    return 0;
}

/*
    string output = String.substr(0, String.length()/2)

    for(int x: $array )

    set<vector<int>> st;

    sort(arr.begin(),arr.end()); // thay đổi arr gốc

    reverse(String.begin(),String.end()); // thay đổi string gốc
    String.erase(input.length()-1,1); // thay đổi string gốc

    template <class val>
    void swapVal(val &a , val &b)
*/