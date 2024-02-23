# Rövarspråket Translator

## Overview

This C++ program translates American English text stored in a plain text file to Rövarspråket, also known as "The Robber Language" in English. The translation follows specific rules where every consonant is doubled, and an 'o' is inserted in between. Vowels are left intact.

## Program Structure

The program consists of three main classes:

### 1. Model Class

- **File:** `Model.h`, `Model.cpp`
- **Public Methods:**
    - Default constructor
    - Default destructor
    - `translateSingleConsonant(char)` - Takes a single consonant character as input and returns its encoding in Rövarspråket with preserved capitalization.
    - `translateSingleVowel(char)` - Takes a single vowel character as input and returns its encoding in Rövarspråket with preserved capitalization.

### 2. Translator Class

- **File:** `Translator.h`, `Translator.cpp`
- **Public Methods:**
    - Default constructor
    - Default destructor
    - `translateEnglishWord(string)` - Takes a single English word as input and returns its Rövarspråket translation.
    - `translateEnglishSentence(string)` - Takes a single English sentence as input and returns its Rövarspråket translation, accounting for punctuation.

### 3. FileProcessor Class

- **File:** `FileProcessor.h`, `FileProcessor.cpp`
- **Public Methods:**
    - Default constructor
    - Default destructor
    - `processFile(string inputFile, string outputFile)` - Takes an input file (English) and an output file (where the Rövarspråket translation will be written). Produces an HTML file with the original English text in bold followed by an empty line, and the Rövarspråket translation in italics.

## How to Run

1. Compile the program using a C++ compiler. (e.g., `g++ *.cpp -o rover`)
2. Execute the compiled program (e.g., `./rover input.txt output.html`).
3. The program will read an input file, translate the text to Rövarspråket, and create an HTML file with the translation.
