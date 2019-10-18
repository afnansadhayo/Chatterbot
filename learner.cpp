#include "learner.h"
#include <iostream>
#include <fstream>

using namespace std;
/*
    The following function will look for the passed phrase in the memory file.
    If there is a match, the accompanying response, stored below the initial phrase, 
    will be outputed. 
    If the response cannot be found, the learner will repeat the phrase, and prompt
    the user to enter an ideal response. This response will be stored in the memory
    file along with the initial phrase. 
*/
void Learner::respond(string phrase){
    fstream memory;
    memory.open("memory/memory.txt", ios::in);    // Open the memory file for input

    // Search through the file until the end is reached
    while( !memory.eof() ){    // While not at end of file
        string identifier;
        getline(memory,identifier);    // Get next phrase
        
        if(identifier == phrase){    // Is it the phrase we are looking for
            string response;
            getline(memory,response);   // If so, get the response
            voice.say(response);   // Textually and audibly output the response!
            return;    // Leave the function
        }
    }

    memory.close();    // Looks like we couldn't find the phrase in memory. Close the file!
    memory.open("memory/memory.txt", ios::out | ios::app);    // Now open for output, and append at end of file
    memory << phrase << endl;    // Record initial phrase in memory

    voice.say(phrase);   // Repeat the phrase the user entered
    string userResponse;
    cout << "YOU: ";
    getline(cin, userResponse);    // Get the ideal response
    memory << userResponse << endl;    // Write the ideal response to memory
    memory.close();    // Close the file!
}

/*
    This function simply communicates a phrase textually and audibly
*/
void Learner::say(string phrase){
    this->voice.say(phrase);
}
