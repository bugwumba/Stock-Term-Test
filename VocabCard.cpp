#include "VocabCard.h"

using namespace std;

VocabCard::VocabCard(string& term, string& definition){
    this->term = term;
    this->definition = definition;
    this->used = false;
}

string VocabCard::getTerm(){
    return this->term;
}

string VocabCard::getDefinition(){
    return this->definition;
}

bool VocabCard::getUsed(){
    return this->used;
}

void VocabCard::changeBoolToTrue(){
    this->used = true;
}

void VocabCard::changeBoolToFalse(){
    this->used = false;
}