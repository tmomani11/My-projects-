#include "Model.h"
#include <string>
#include <cctype>
using namespace std;

Model::Model(){}
Model::~Model(){}

/*
 * The CheckConsonant function checks if a character is a consonant.
 *
 * @param c: The character to be checked.
 * @return: True if the character is a consonant, false otherwise.
 */
bool Model::CheckConsonant(char c) {
    c = std::tolower(c);  // Convert 'c' to lowercase

    return (
            // Check if 'c' is a consonant (not a, e, i, o, u)
            (c >= 'a' && c <= 'z' && c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
    );
}
/*
 * The translateSingleConsonant function encodes a consonant based on Rövarspråket rules.
 *
 * @param c: The consonant to be encoded.
 * @return: A translated string according to Rövarspråket rules.
 */
string Model::translateSingleConsonant(char c) {
    if (CheckConsonant(c)) {
        bool isLowerCase = (c >= 'a' && c <= 'z');
        std::string encoding;
        encoding += c;
        if (isLowerCase) {
            encoding += 'o';
        } else {
            encoding += tolower('O');
        }
        encoding += tolower(c);
        return encoding;
    } else {
        return std::string(1, c);
    }
}
/*
 * The translateSingleVowel function encodes a vowel based on Rövarspråket rules.
 *
 * @param c: The vowel to be encoded.
 * @return: A string of the encoded vowel.
 */
string Model::translateSingleVowel(char c){
    string result(1, c);
    return result;
}




