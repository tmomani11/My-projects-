#include "Model.h"
#include <string>
#include <cctype>
using namespace std;

Model::Model() {
}
Model::~Model() {
}


/*
 * The translateSingleConsonant function encodes a consonant based on Rövarspråket rules.
 *
 * @param c: The consonant to be encoded.
 * @return: A translated string according to Rövarspråket rules.
 */
string Model::translateSingleConsonant(char c) {

        std::string encoding;
        encoding += c  ;
        encoding += 'o';
        encoding += tolower(c);

    return encoding;
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




