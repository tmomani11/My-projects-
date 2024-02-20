#include "Model.h"
#include <string>
#include <cctype>
using namespace std;

Model::Model(){}
Model::~Model(){}

/* CheckConsonant()
 * Encodes a consonant based on Roverspraket rules
 * Return: true if its a consonant ,false if its not.
 * Parameters:
 *  char c: the consonant to be checked
 */
bool Model::CheckConsonant(char c) {
    c = std::tolower(c);  // Convert 'c' to lowercase

    return (
            // Check if 'c' is a consonant (not a, e, i, o, u)
            (c >= 'a' && c <= 'z' && c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
    );
}
/* translateSingleConsonant()
 * Encodes a consonant based on Roverspraket rules
 * Return: A translated string according to rules
 * Parameters: 
 *  char c: the consonant to be encoded
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
/* translateSingleVowel()
 * Encodes a vowel based on Roverspraket rules
 * Return: A string of the encoded vowel
 * Parameters: 
 *  char c: the vowel to be encoded
 */
string Model::translateSingleVowel(char c){
    string result(1, c);
    return result;

}




