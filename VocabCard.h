#include <string>
#include <vector>
#include <iostream>

using namespace std;

#ifndef _VOCABCARD_H_
#define  _VOCABCARD_H_

class VocabCard {
  private:
    string term;
    string definition;
    bool used;
  public:
    VocabCard(string &, string &);
    string getTerm();
    string getDefinition();
    bool getUsed();
    void changeBoolToTrue();
    void changeBoolToFalse();
};

#endif