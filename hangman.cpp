#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include <string>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "assets.h"
using namespace std;

string load_random_word(string path)
{
    int lineCount = 0;
    string word;
    vector <string> v;
    ifstream file(path);
    if (file.is_open())
    {
        while (getline(file, word))
            v.push_back(word);

        int randomLine = rand() % v.size();

        word = v.at(randomLine);
        file.close();
    }
    return word;
}

bool check_and_print(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.size(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    cout << s << '\n';
    return won;
}

int tries_left(string word, string guessed)
{
    int turn = 0;
    for (int i = 0; i < guessed.size(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
            turn++;
    }
    return turn;
}

void print_letter(string input, char a, char b)
{
    string s;
    for (char i = a; i <= b; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += toupper(i);
            s += " ";
        }
        else
            s += "  ";
    }
    cout << s << '\n';
}

void print_available_letters(string input)
{
    cout << "\n Available letters: \n\n";
    print_letter(input, 'a', 'm');
    print_letter(input, 'n', 'z');
    cout << '\n';
}

void draw_hangman(int tries)
{
    cout << figure[tries];
}

void hangman()
{
    srand(time(NULL));

    string guesses;
    string secret_word;
    int tries = 0;
    bool win = false;
    secret_word = load_random_word("words.txt");

    while (1)
    {
        system("cls");
        draw_hangman(tries);
        print_available_letters(guesses);

        win = check_and_print(secret_word, guesses);

        if (win)
            break;

        char your_guess;
        cout << ">";
        cin >> your_guess;

        if (isupper(your_guess))
            your_guess = tolower(your_guess);
        if (guesses.find(your_guess) == string::npos)
            guesses += your_guess;

        tries = tries_left(secret_word, guesses);

        if (tries == 7)
        {
            system("cls");
            draw_hangman(tries);
            print_available_letters(guesses);
            break;
        }
    }

    if (win)
        cout << "\nYOU WON!\n";
    else
    {
        cout << "\nGAME OVER\n";
        cout << "Answer: " << secret_word << '\n';
    }
}
void run_game()
{
    for (int i = 4; i >= 1; --i)
    {
        cout << logo << "\n\n";

        if (i == 4)
            cout << "Game start in:";
        else
            cout << "Game start in: " << i << "...";

        Sleep(1000);
        system("cls");
    }
    hangman();
}
int main()
{
    int exit = 0;
    while (exit != 2)
    {
        run_game();
        cout << '\n' << box;
        cin >> exit;
        system("cls");
    }
    system("cls");
    cout << "THANK FOR PLAYING <3";
    return 0;
}