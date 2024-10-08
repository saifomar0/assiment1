/*
 *Assigmnet 1*
student:saif elden omar emam
ID:20230183


problem 1 : The program takes a word from the user and should oytput just one space between the words and just the first char is capital
and "." in the end of the input


problem 4  (Sieve of Eratosthenes for Prime Numbers)  : this problem should print the prime numbers by delet the multiply of the prime numbers

problem 7 (The game of dominos ): this problem takes number of dominos and the dots of it and it schould return true if
the pieces can make a chian or not and print the chain and return faluse if it cant make a chain



problem 10 : this program have a list of banned arabic words when the user input its text file it replace the
banned words by encrepted words



*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <string>
#include <codecvt>
#include <map>
using namespace std;


int proplem1()
{
    cout<<endl<<"Enter your word"<<endl;
    string word;
    getline(cin, word);
    bool flag = true;

    for (int i = 0; i < word.length(); i++)
    {

        if (isupper(word[i]))
        {
            word[i]= tolower(word[i]);
        }
        if(isalpha(word.back()))
        {
            word+=".";
        }
        if(!isalpha(word.back()))
        {
            word.pop_back();
            word+=".";

        }
        if( isspace(word[i]) && isspace(word[i-1]) )
        {
            flag = false;
        }
        else if (flag==true)
        {
            word[0]= toupper(word[0]);
            cout << word[i];
        }
        flag = true;
    }

    return 0;
}

int problem2()
{
    cout<<endl<<"Enter a number"<<endl;
    int num;
    cin >>num;
    // Create a vector to mark prime numbersmaking all to 1
    vector<int> nums(num+1, 1);

    for (int i = 2; i*i<= num; i++)
    {
       // Mark multiples of each prime number as 0 (non prime)
        for (int j = i*i; j<= num; j += i)
        {
            nums[j] = 0;
        }

    }

    for(int t=2;t<nums.size();t++)
    {
        if(nums[t]==1) // Check if the number is marked as prime
        {
            cout << t  << " ";
        }



    }

    return 0;



}

//========================================*7*===========================

struct dominopies {
    int leftDots,rightDots;
};
// convert a string like  into a dominoopiec object
dominopies parseDomino(const string& str) {
    dominopies domino;
    stringstream ss(str);
    char separator; //  hold the separator ( | )
    ss >> domino.leftDots >> separator >> domino.rightDots; // Read the values from the string

    // Check that the numbers are between 0 and 6
    if ((domino.leftDots < 0 || domino.leftDots > 6) || (domino.rightDots < 0 || domino.rightDots > 6)) {
        cout<<("Domino values must be between 0 and 6.");
    }
    return domino;
}

//  function to check if all domino pieces can be used
bool canuse(vector<dominopies> &dominos, vector<bool> &used, int currentDots, int usedCount, vector<string> &chain) {
    // Check if all pieces have been used
    if (usedCount == dominos.size()) {
        return true; // Return true if all pieces are used
    }

    // Loop throgh all domino pieces
    for (int i = 0; i < dominos.size(); i++) {
        // Check if the crrent pieceis avilable
        if (!used[i] && (dominos[i].leftDots == currentDots || dominos[i].rightDots == currentDots)) {
            used[i] = true;
            // Store  in achain
            string currentChain = to_string(dominos[i].leftDots) + "|" + to_string(dominos[i].rightDots);
            chain.push_back(currentChain);

            // Check if all pieces can be used
            if (canuse(dominos, used, dominos[i].rightDots, usedCount + 1, chain) ||
                canuse(dominos, used, dominos[i].leftDots, usedCount + 1, chain)) {
                return true; // If all pieces are used, return true
                }

            // remove the crrent piece from the chain and mark it as unused
            chain.pop_back();
            used[i] = false; //  if not all pieces can be used
        }
    }

    return false;
}

//  function to chck if all  thedomino pieces can be used to form a chain
bool canformchain (vector<dominopies> &dominos, vector<string> & chain) {
    vector<bool> used(dominos.size(), false); // Track used pices

    // Try starting the chain from each domino piece
    for (int i = 0; i < dominos.size(); i++)
        {
        used[i] = true; // Start with using this piece

        // Store the first piece in the chain
        string currentChain = to_string(dominos[i].leftDots) + "|" + to_string( dominos[i]. rightDots);
        chain.push_back(currentChain);
        // Check if all pieces can be used
        if (canuse( dominos, used, dominos [i].rightDots, 1, chain) ||
            canuse(dominos, used, dominos[i] .leftDots, 1, chain)) {
            return true;
        }

        // remove the first piece from the chain
        chain.pop_back();
        used[i] = false; //if not all pieces can be used
    }

    return false;
}

int problem7()
{int n;
    cout << "enter the number of dominos  "<<endl;
    cin >> n;

    vector<dominopies> dominos;
    string input; // Variable to hold input
    vector<string> chain; // Vector to hold the resulting chain

    // Get user input for the domino pieces
    cout << "Please enter the domino pieces like 5|6" << endl;
    for (int i = 0; i < n; i++) {
        cin >> input;
        try {
            dominos.push_back(parseDomino(input)); // Convert the string to funton domin and add it to the vector
        } catch (invalid_argument &e) {
            cout << e.what() << endl; // print  error if the input is invald
            i--;
        }
    }

    // Check if its possible to form a domino chain
    if (canformchain(dominos, chain))
    {
        cout << "true" << endl;
        cout << "The chain is: ";
        for (const auto& piece : chain) {
            cout << piece << " ";
        }
        cout << endl;
    } else
    {
        cout << "false" << endl;
    }
    return 0;
}
int problem10()

{

    locale::global(locale(""));
    wstring file_name;
    cout << "Enter the file name or path" << endl;
    getline(wcin, file_name);


    // Open the file containing word replacements
    wifstream replace_file("bann.txt");
    replace_file.imbue(locale(replace_file.getloc(), new codecvt_utf8<wchar_t>));


    // Map to store replacmnts
    map<wstring, wstring> replace_map;
    wstring word, replacement;

    while (replace_file >> word >> replacement)
    {
        // Add each pair to the map
        replace_map[word] = replacement;
    }
    replace_file.close();

    wifstream input((file_name.data()));
    input.imbue(locale(input.getloc(), new codecvt_utf8<wchar_t>));
    wofstream output("yar.txt");
    output.imbue(locale(output.getloc(), new codecvt_utf8<wchar_t>));
    wstring line, currentWord;

    while (getline(input, line))
    {
        // Read the line into a stream
        wistringstream iss(line);
        wstring newLine;

        while (iss >> currentWord)
        {
            // Check if the current word has a replacement
            if (replace_map.find(currentWord) != replace_map.end())
            {
                newLine += replace_map[currentWord];
            }
            else
            {
                newLine += currentWord;
            }

            newLine += L" ";
        }
        output << newLine << endl;
    }
    wcout << "File processed and output writtenn";
    input.close();
    output.close();
    return 0;


}



int main()
{
    int n;
    bool flag = true;

    cout<<"For Problem (1) enter (1)"<<endl<<"For Problem (prime numbers) enter (4)"<<endl<<
    "For Problem (7)  (The game of dominos) enter (7)"<<endl<<"For Problem (10)  (Message Altering to Avoid Censorship.) enter (10)"<<endl;

    while (flag) {
        cin >> n;
        cin.ignore();

        if (n != 1 && n != 4 && n != 7 && n != 10) {
            cout << "Please enter a valid input" << endl;
        } else {
            flag = false;
        }
    }



    switch (n)
    {
        case 1:
            proplem1();
            break;

        case 4:
            problem2();
            break;
        case 7:
            problem7();
            break;
        case 10:
            problem10();
            break;

    }


    return 0;
}

