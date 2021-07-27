// The program must be executed at the command-line, following with the word you want to solve as the argument.

#include <iostream>
#include <string>

using namespace std;

// Global Variables
int length, guesses;

// Global functions
void encrypt(char *word);
void getAnswer(char *word);
int play(int guesses, char *word, char key[1]);
int endGame();

int main(int argc, char *argv[])
{
    // Checks if one argument is inputted into command line
    if (argc < 2)
    {
        cout << "Enter a word";
        return 0;
    }
    else if (argc > 2)
    {
        cout << "Enter only one word";
        return 0;
    }
    else
    {
        length = strlen(argv[1]);
        guesses = length;
        char hiddenWord[length];
        strcpy(hiddenWord, argv[1]);

        encrypt(hiddenWord);
        play(length, hiddenWord, argv[1]);
        endGame();
    }
}

// Sets hidden word to underscores
void encrypt(char *word)
{
    for (int i = 0; i < length; i++)
    {
        word[i] = '_';
    }
}

// Prints out current answer
void getAnswer(char *word)
{
    cout << "The answer so far is ";
    for (int i = 0; i <= length; i++)
    {
        cout << word[i] << " ";
    }
    cout << endl;
}

// Starts 'game'
int play(int length, char *word, char key[1])
{
    int guesses = 4, correct = 0;
    char guess;
    bool increment;

    cout << "I'm thinking of a secret word.\n" <<
    "Try and guess the word. You can guess one letter at a time.\n" <<
    "Each time you guess I will show you which letters have been \ncorrectly guessed and which letters are still missing.\n";
    cout << "You will have " << 4 << " guesses to guess all of the letters. Good luck!" << endl;
    getAnswer(word);

    while(guesses > 0)
    {
        // Iterates guess through key, and replaces letters in ciphertext with correct guess
        cout << "Guess a letter (" << guesses << " guesses remaining): ";
        cin >> guess;
        for (int i = 0; i <= length; i++)
        {
            if (guess == key[i] && word[i] == '_')
            {
                word[i] = guess;
                correct++;
                increment = true;
            } 
        }
        if (increment == true)
        {
            guesses++;
            increment = false;
        }
        getAnswer(word);
        if (correct == length)
        {
            cout << "Good job! You found the word " << key << "!" << endl;
            return 0;
        }
        else
        {
            guesses--;
            continue;
        }
    }
    cout << "Not quite, the correct answer was " << key << ". Better luck next time" << endl;
    return 0;
}

// Prompts for enter key to end game
int endGame()
{
    char end;
    cout << "Press enter to end the game. ";
    cin.ignore();
    if (cin.get() == '\n')
    {
        return 0;
    }
    else
    {
        endGame();
        return 0;
    }
    
}