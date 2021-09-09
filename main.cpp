#include <fstream>
#include <ostream>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "VocabCard.h"

using namespace std;

//Good
inline void WelcomeMesage() {
    cout << "\nThe purpose of this program is to test the\n";
    cout << "user's understanding of financial terms.\n";
    cout << "Would you like to upload a file (Y/N)?\n\n";

}

//Good
inline void Menu(){
    cout << "\nWhat type of test would you like to take?\n\n";    
    cout << "1. Term test\n";
    cout << "2. Definition test\n";
    cout << "3. Combination test\n\n";
}

//checks if there are any existing unused cards in the vector
//Good
inline bool checkUsed(vector<VocabCard>& allCards){
    for (int i = 0; i < allCards.size(); i++){
        if (allCards.at(i).getUsed() == false){
            return true;
        }
    }
    return false;
}

//checks to see if the key passed in can be found in the vector passed in
//Good
template <class T>
inline bool findInVec(vector<T>& v, T key){
    for (int i = 0; i < v.size(); i++){
        if (v.at(i) == key){
            return true;
        }
    }
    return false;
}

//checks if string passed in is a valid input
//Good
inline bool inputValid(string& input){
    if (input.size() > 1){
        return false;
    }
    if (input == "a" || input == "b" || input == "c" || input == "d"){
        return true;
    }
    return false;
}

//Good
inline bool inputValid2(string& input){

    if(input == "q" || input == "Q" || input == "M" || input == "m"){
        return true;
    }

    return false;

}

//Good
inline bool inputValid3(string& input){

    if(input == "Y" || input == "y" || input == "N" || input == "n"){
        return true;
    }

    return false;
}

//Good
inline bool inputValid4(string& input){

    if(input == "1" || input == "2" || input == "3"){
        return true;
    }

    return false;

}

//Function to quit program 
inline void QuitProgram(){
    exit(1);
}

inline void SaveData(int& correctAnswers, vector<int>& wrongAnswers, vector<VocabCard>& allCards){
    string userName = "";
    string dateOfUse = "";
    fstream log;
    log.open("SavedData.txt", fstream::app);
        if(!log.is_open()){
            cout << "Could not open 'TestList.txt'!\n";
            cout << "Exiting Program!\n\n";
            exit(1); 
        }
        cout << "Name: ";
        cin >> userName;
        cout << endl << "Date (MM/DD/YY): ";
        cin >> dateOfUse;
        log << "Name: " << userName << endl << "Date: " << dateOfUse << endl;
        log << "Correct Answers: " << correctAnswers << endl;
        log << "Terms you got wrong: " << wrongAnswers.size() << endl;
        log << "List of terms and their definitions:\n\n";
        for (int i = 0; i < wrongAnswers.size(); i++){
            log << allCards.at(wrongAnswers.at(i)).getTerm() << " - " << allCards.at(wrongAnswers.at(i)).getDefinition() << endl << endl;
        }
        log << endl;
        log.close();
}

inline void TermTest(vector<VocabCard>& allCards){
    srand(time(NULL));
    string input = "";
    vector <int> wrongAnswers;
    string saveData;
    int correctAnswers = 0;
    while(checkUsed(allCards)){
        vector<int> usedIndex; //stores the index numbers already used for answer choices
        int randTermIndex = rand() % allCards.size(); //selects random term to use
        while(allCards.at(randTermIndex).getUsed() == true){ //makes sure its not used
            randTermIndex = rand() % allCards.size();
        }
        allCards.at(randTermIndex).changeBoolToTrue(); //changes object element "used"
        usedIndex.push_back(randTermIndex); //pushes term into usedIndex vector
        cout << "Term: " << allCards.at(randTermIndex).getTerm() << endl << endl;
        int randomAnswerPosition = rand() % 4; //0-A, 1-B, 2-C, 3-D  This is for position for correct answer
        for (int i = 0; i < 4; i++){
            char letter = 97 + i; //used for display the answer choice for the specific definition
            if (i == randomAnswerPosition){ //displays correct answer
                cout << letter << ": " << allCards.at(randTermIndex).getDefinition() << endl;
                }
            else { //displays incorrect answers
                int randomIndex = rand() % allCards.size(); //picks random definition to display as dummy answer choice
                while(findInVec(usedIndex, randomIndex)){ //checks to make sure index not already used
                    randomIndex = rand() % allCards.size();
                }
                usedIndex.push_back(randomIndex); //pushes index into usedIndex vector
                cout << letter << ": " << allCards.at(randomIndex).getDefinition() << endl;
                }
            }
        cout << endl << "Pick the correct definition.\n"; //asks for user input of choice
        cout << "Press Q to quit\n\n";
        cin.clear();
        cin >> input;
        if(input == "q" || input == "Q"){
          QuitProgram();
        }
        while (inputValid(input) == false){ //checks for invalid input
            cout << "Invalid Input. Make sure you are inputting a capital letter A, B, C, or D." << endl;
            cout << "Pick the correct definition." << endl << endl;
            cin.clear();
            cin >> input;
        }
        char inputChar = input.at(0); //takes the letter
        char display = 97 + randomAnswerPosition; //just to display as a letter
        if (inputChar != 97 + randomAnswerPosition){
            cout << "Wrong Answer" << endl << "Correct answer is: " << display << endl << endl;
            wrongAnswers.push_back(randTermIndex);
        }
        else {
            cout << "You got it correct!" << endl << endl;
            correctAnswers++;
        }
    }
    cout << "You have finished the set." << endl; //after entire set is completed
    cout << "Definitions you got wrong: " << wrongAnswers.size() << endl;
    cout << "List of terms and their definitions:\n\n";
    for (int i = 0; i < wrongAnswers.size(); i++){
        cout << allCards.at(wrongAnswers.at(i)).getTerm() << " - " << allCards.at(wrongAnswers.at(i)).getDefinition() << endl << endl;
    }
    cout << endl;
    cout << "Would you like to save this data? (Y/N)\n";
    cin >> saveData;
    while(inputValid3(saveData) == false){
        cout << "Invalid Input!\n";
        cout << "Would you like to save this data? (Y/N)\n";
        cin >> saveData;
        cout << endl << endl;
    }
    if(saveData == "Y" || saveData == "y"){
        SaveData(correctAnswers, wrongAnswers, allCards);
    }
    correctAnswers = 0;
    wrongAnswers.clear();
}

inline void DefTest(vector<VocabCard>& allCards){
    srand(time(NULL));
    string input = "";
    vector <int> wrongAnswers;
    string saveData;
    int correctAnswers = 0;
    while(checkUsed(allCards)){
        vector<int> UsedIndex; // stores the index number already used for answer choices
        int randTermIndex = rand() % allCards.size(); //selects random term to use
        while(allCards.at(randTermIndex).getUsed() == true){ //while loop to determ whether or not term has been used
            randTermIndex = rand() % allCards.size();        //if so, find another term
        }
        allCards.at(randTermIndex).changeBoolToTrue(); //Changes the VocabCard object boolean data type to true
        UsedIndex.push_back(randTermIndex); //Stores the index in the vector
        cout << "Definition: " << allCards.at(randTermIndex).getDefinition() << endl << endl;
        int randomAnswerPosition = rand() % 4; // 0-A, 1-B, 2-C, 3-D, randomly selects the answers position
        for(int i = 0; i < 4; i++){
            char letter = 97 + i; //Used to display the answer cboice for the specific term
            if(i == randomAnswerPosition){ //displays the correct definition
                cout << letter << ". " << allCards.at(randTermIndex).getTerm() << endl;;
            }
            else{ //display incorrect definitions
                int randomIndex = rand() % allCards.size();
                while(findInVec(UsedIndex, randomIndex)){ //Loop to make sure the index has not been used already
                    randomIndex = rand() % allCards.size();
                }
                UsedIndex.push_back(randomIndex); //pushed index into used index vector
                cout << letter << ". " << allCards.at(randomIndex).getTerm() << endl;
            }
        }
        cout << "\nPick the correct term: " << endl;
        cout << "Press 'Q' to quit.\n\n";
        cin.clear();
        cin >> input;
        if(input == "q" || input == "Q"){
            QuitProgram();
        }
        while (inputValid(input) == false){ //checks for invalid input
            cout << "Invalid Input!" << endl;
            cout << "Pick the correct term." << endl << endl;
            cin.clear();
            cin >> input;
        }
        char inputChar = input.at(0); //Takes the letter?
        char display = 97 + randomAnswerPosition; //just to display as a letter
            if (inputChar != 97 + randomAnswerPosition){
                cout << "Wrong Answer" << endl << "Correct answer is: " << display << endl << endl;
                wrongAnswers.push_back(randTermIndex);
            }
            else {
                cout << "You got it correct!" << endl << endl;
                correctAnswers++;
            }
    }
    cout << "You have finished the definition test. " << "Correct Answers: " << correctAnswers << endl; //after entire set is completed
    cout << "Definitions you got wrong: " << wrongAnswers.size() << endl;
    cout << "List of terms and their definitions:\n\n";
    for (int i = 0; i < wrongAnswers.size(); i++){
        cout << allCards.at(wrongAnswers.at(i)).getTerm() << " - " << allCards.at(wrongAnswers.at(i)).getDefinition() << endl << endl;
    }
    cout << endl;
    cout << "Would you like to save this data? (Y/N)\n";
    cin >> saveData;
    while(inputValid3(saveData) == false){
        cout << "Invalid Input!\n";
        cout << "Would you like to save this data? (Y/N)\n";
        cin >> saveData;
        cout << endl << endl;
    }
    if(saveData == "Y" || saveData == "y"){
        SaveData(correctAnswers, wrongAnswers, allCards);
    }
    correctAnswers = 0;
    wrongAnswers.clear();
}

inline void CombTest(vector<VocabCard>& allCards){
    srand(time(NULL));
    string input = "";
    vector <int> wrongAnswers;
    string saveData;
    int correctAnswers = 0;
    while(checkUsed(allCards)){
        vector<int> UsedIndex; // stores the index number already used for answer choices
        int randTermIndex = rand() % allCards.size(); //selects random term to use
        while(allCards.at(randTermIndex).getUsed() == true){ //while loop to determ whether or not term has been used
            randTermIndex = rand() % allCards.size();        //if so, find another term
        }
        allCards.at(randTermIndex).changeBoolToTrue(); //Changes the VocabCard object boolean data type to true
        UsedIndex.push_back(randTermIndex); //Stores the index in the vector
        int randomSwitch = rand() % 2;
        if(randomSwitch == 1){
            cout << "Term: " << allCards.at(randTermIndex).getTerm() << endl << endl;
            int randomAnswerPosition = rand() % 4; //0-A, 1-B, 2-C, 3-D  This is for position for correct answer
            for (int i = 0; i < 4; i++){
                char letter = 97 + i; //used for display the answer choice for the specific definition
                if (i == randomAnswerPosition){ //displays correct answer
                    cout << letter << ": " << allCards.at(randTermIndex).getDefinition() << endl;
                }
                else { //displays incorrect answers
                    int randomIndex = rand() % allCards.size(); //picks random definition to display as dummy answer choice
                    while(findInVec(UsedIndex, randomIndex)){ //checks to make sure index not already used
                        randomIndex = rand() % allCards.size();
                    }
                    UsedIndex.push_back(randomIndex); //pushes index into usedIndex vector
                    cout << letter << ": " << allCards.at(randomIndex).getDefinition() << endl;
                    }
            }
            cout << endl << "Pick the correct definition." << endl; 
            cout << "Type Q or 'Quit' to quit.\n"<< endl; //asks for user input of choice
            cin.clear();
            cin >> input;
            if(input == "Q" || input == "q"){
                QuitProgram();
            }
            while (inputValid(input) == false){ //checks for invalid input
                cout << "Invalid Input!" << endl;
                cout << "Pick the correct definition." << endl << endl;
                cin.clear();
                cin >> input;
            }
            char inputChar = input.at(0); //takes the letter
            char display = 97 + randomAnswerPosition; //just to display as a letter
            if (inputChar != 97 + randomAnswerPosition){
                cout << "Wrong Answer" << endl << "Correct answer is: " << display << endl << endl;
                wrongAnswers.push_back(randTermIndex);
            }
            else {
                cout << "You got it correct!" << endl << endl;
                correctAnswers++;
            }
        }
        
        else{
            cout << "Definition: " << allCards.at(randTermIndex).getDefinition() << endl << endl;
            int randomAnswerPosition = rand() % 4; //0-A, 1-B, 2-C, 3-D  This is for position for correct answer
            for (int i = 0; i < 4; i++){
                char letter = 97 + i; //used for display the answer choice for the specific definition
                if (i == randomAnswerPosition){ //displays correct answer
                    cout << letter << ": " << allCards.at(randTermIndex).getTerm() << endl;
                }
                else { //displays incorrect answers
                    int randomIndex = rand() % allCards.size(); //picks random definition to display as dummy answer choice
                    while(findInVec(UsedIndex, randomIndex)){ //checks to make sure index not already used
                        randomIndex = rand() % allCards.size();
                    }
                    UsedIndex.push_back(randomIndex); //pushes index into usedIndex vector
                    cout << letter << ": " << allCards.at(randomIndex).getTerm() << endl;
                }
             }
            cout << endl << "Pick the correct definition." << endl; 
            cout << "Type Q or 'Quit' to quit.\n"<< endl; //asks for user input of choice
            cin.clear();
            cin >> input;
            if(input == "Q" || input == "q"){
                QuitProgram();
            }
            while (inputValid(input) == false){ //checks for invalid input
                cout << "Invalid Input!" << endl;
                cout << "Pick the correct definition." << endl << endl;
                cin.clear();
                cin >> input;
            }
            char inputChar = input.at(0); //takes the letter
            char display = 97 + randomAnswerPosition; //just to display as a letter
            if (inputChar != 97 + randomAnswerPosition){
               cout << "Wrong Answer" << endl << "Correct answer is: " << display << endl << endl;
                wrongAnswers.push_back(randTermIndex);
            }
            else {
                cout << "You got it correct!" << endl << endl;
                correctAnswers++;
            }
        }
    }
    cout << "You have finished the combination test. " << "Correct Answers: " << correctAnswers << endl; //after entire set is completed
    cout << "Terms you got wrong: " << wrongAnswers.size() << endl;
    cout << "List of terms and their definitions:\n\n";
    for (int i = 0; i < wrongAnswers.size(); i++){
        cout << allCards.at(wrongAnswers.at(i)).getTerm() << " - " << allCards.at(wrongAnswers.at(i)).getDefinition() << endl << endl;
    }
    cout << "Would you like to save this data? (Y/N)\n";
    cin >> saveData;
    while(inputValid3(saveData) == false){
        cout << "Invalid Input!\n";
        cout << "Would you like to save this data? (Y/N)\n";
        cin.clear();
        cin >> saveData;
        cout << endl << endl;
    }
    if(saveData == "Y" || saveData == "y"){
        SaveData(correctAnswers, wrongAnswers, allCards);
    }
    cout << endl;
    correctAnswers = 0;   
    wrongAnswers.clear();

}

inline void DecisionMaker(string& choice, vector<VocabCard>& allCards){
    if(choice == "1"){
        TermTest(allCards);
    }
     if(choice == "2"){
        DefTest(allCards);
    }
    if (choice  == "3"){
        CombTest(allCards);  
    }
}


int main () {

    srand(time(NULL));

    string choice = "";
    string secChoice = "";
    int ranIndex = 0;
    string term = "";
    string definition = "";
    string TestName = "";
    string inputFile = "";
    vector<string> ListOfTest;
    vector<VocabCard> allCards;
    vector<VocabCard> newSET;


    string answer = "";
    string again = "y";

    fstream inFS;
    inFS.open("TestList.txt");
    if(!inFS.is_open()){
        cout << "Could not open 'TestList.txt'\n";
        cout << "Exiting Program\n\n";
        exit(1);
    }

    while(getline(inFS, TestName)){
        ListOfTest.push_back(TestName);
    }

    inFS.close();



    while(again == "y" || again == "Y"){
        WelcomeMesage();
        cin >> answer;
        while(inputValid3(answer) == false){
            cout << "Invalid input!\n\n";
            WelcomeMesage();
            cin.clear();
            cin >> answer;
        }
        if(answer == "Y" || answer == "y"){
            string decide = "";
            cout << "\nEnter the filename: ";
            cin >> inputFile;
            inFS.open(inputFile);
            if(!inFS.is_open()){
                cout << "Could not open " << inputFile << "!" << endl;
                cout << "Exiting the program!\n";
                exit(1);
            }
            while(getline(inFS, term)){
                getline(inFS, definition);
                newSET.push_back(VocabCard(term, definition));
            }
            inFS.close();            
            cout << "\nFile successfully uploaded!\n";
            cout << "Would you like to:\n1. Only use this file\n2. Add to existing files\n";
            cin >> decide;
            while(inputValid4(decide) == false){
                cout << "Invalid Entry!\n";
                cout << "\nFile successfully uploaded!\n";
                cout << "Would you like to:\n1. Only use this file\n2. Add to existing files\n";
                cin.clear();
                cin >> decide;
            }
            if(decide == "1"){
                string againNew = "y";
                while(againNew == "y" || againNew == "Y"){
                vector<VocabCard> newSet2(newSET);
                Menu();
                cin >> choice;
                    while(inputValid4(choice) == false){
                        cout << "Invalid Entry!\n";
                        cout << "Please select one of the three choices\n\n";
                        Menu();
                        cin.clear();
                        cin >> choice;
                    }
                    cout << endl;
                    DecisionMaker(choice, newSET);
                    newSET = newSet2;
                    cout << endl;
                    cout << "Would you like to play again? (Y/N) ";
                    cin >> againNew;
                    while(inputValid3(againNew) == false){
                        cout << "Invalid Entry!\n";
                        cout << "Would you like to play again? (Y/N) ";
                        cin.clear();
                        cin >> againNew;
                    }  
                    if(againNew == "q" || againNew == "Q"){
                        QuitProgram();
                    }
                }
            }
            else{
                ListOfTest.push_back(inputFile);
            }
        }
        Menu();
        cin >> choice;
        while(inputValid4(choice) == false){
            cout << "Invalid Entry!\n";
            cout << "Please select one of the three choices\n\n";
            Menu();
            cin.clear();
            cin >> choice;
        }
        cout << endl;
        cout << "What type of test would you like to take?\n";
        cout << "1. Full Test\n2. Excerpt from test (11 terms and definitions)\n3. Series of excerpts\n\n";
        cin >> secChoice;
        while(inputValid4(secChoice) == false){
            cout << "Invalid Entry!\n";
            cout << "Please select one of the three choices\n\n";
            cout << "What type of test would you like to take?\n";
            cout << "1. Full Test\n2. Excerpt from test (11 terms and definitions)\n3. Series of excerpts\n\n";
            cin.clear();
            cin >> secChoice;
        }
        cout << endl;
        if(secChoice == "1"){
            inFS.open(ListOfTest.at(0));
            if(!inFS.is_open()){
                cout << "Could not open 'info.txt'\n";
                exit(1);
            }
            else{
                while(getline(inFS, term)) {
                        getline(inFS, definition);
                        allCards.push_back(VocabCard(term, definition));
                }
                inFS.close();
                vector<VocabCard> allCards2(allCards);   
                DecisionMaker(choice, allCards);
                allCards = allCards2;                
            }
        }
        else if(secChoice == "2"){
                ranIndex = rand() % ListOfTest.size();
                inFS.open(ListOfTest.at(ranIndex));
                if(!inFS.is_open()){
                    cout << "Could not open " << ListOfTest.at(ranIndex) << endl;
                    exit(1);
                }
                else{
                    while(getline(inFS, term)){
                        getline(inFS, definition);
                        allCards.push_back(VocabCard(term, definition));
                    }
                    inFS.close();   
                    DecisionMaker(choice, allCards);
                    allCards.clear();
                }
        }
        else{
            for(int i = 0; i < 20; i++){
                ranIndex = rand() % ListOfTest.size();
                inFS.open(ListOfTest.at(ranIndex));
                if(!inFS.is_open()){
                    cout << "Could not open " << ListOfTest.at(ranIndex) << endl;
                    exit(1);
                }
                else{
                    while(getline(inFS, term)){
                        getline(inFS, definition);
                        allCards.push_back(VocabCard(term, definition));
                    }
                    inFS.close();
                    DecisionMaker(choice, allCards); 
                    ListOfTest.erase(ListOfTest.begin() + ranIndex);
                    allCards.clear();                       
                }
            }
        }
        cout << endl;
        cout << "Would you like to play again (Y/N)? ";
        cin >> again;
        while(inputValid3(again) == false){
            cout << "Invalid Entry!\n";
            cout << "Would you like to play again (Y/N)? ";
            cin.clear();
            cin >> again;
        }             
    }    

    return 0;

}   