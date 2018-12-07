#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

string cleanWord(string word){
    string cleanWord = word;
    transform(cleanWord.begin(), cleanWord.end(), cleanWord.begin(), ::tolower);
    int length = cleanWord.size();
    for(int i = 0; i<length;i++){
        if(ispunct(cleanWord[i])){
            cleanWord.erase(i--, 1);
            length = cleanWord.size();
        }
    }
    return cleanWord;
}

int main() {
    int numWords = 6;
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();
    vector<string> chunk = vector<string>();
    getdir(dir,files);
    string word;
    int wordCount = 0;
    for (unsigned int i = 0;i < files.size();i++) {
        //skip the directory files
        if (files[i] == "." || files[i] == "..") {}
        else{
            ifstream inFile;
            inFile.open("C:\\Users\\Samuel Yeboah\\Desktop\\EE312\\Cheaters\\cmake-build-debug\\sm_doc_set\\" + files[i]);
            //adds first n words to vectors
            for(int i = 0; i<numWords;i++) {
                inFile >> word;
                word = cleanWord(word);
                chunk.push_back(word);
            }
            //adds one word vector and removes first element
            //hash the chunk before adding 6 more characters
            while(!inFile.eof()){
                inFile >> word;
                word = cleanWord(word);
                cout << word << "\n";
                chunk.erase(chunk.begin());
                chunk.push_back(word);
                //blakes code goes here
            }
        }
    }
    return 0;
}