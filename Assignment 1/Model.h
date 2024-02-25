#ifndef MODEL_H
#define MODEL_H

#include <string>
class Model{
    public:
    Model(); // Default constructor
    virtual ~Model(); // Virtual destructor

    // Translates a single consonant character.
    // @param c The consonant to translate.
    // @return The translated consonant as a string.
      std::string translateSingleConsonant(char c);

     // Translates a single vowel character.
    // @param c The vowel to translate.
    // @return The translated vowel as a string.
      std::string translateSingleVowel(char c);

private:

};
#endif