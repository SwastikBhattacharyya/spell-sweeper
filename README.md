# Spell Sweeper

Spell Sweeper is a spell checker for the English dictionary. It takes input from
a file and asks the user for corrections for misspelled words and then saves the
correct string into another specified file.

## Overview

Spell Sweeper is a simple command line spell checker written in C++. It is
implemented using the Damerau Levenshtein Distance and BK Tree. The dictionary is
created using a text file obtained from [dwyl's repository](https://github.com/dwyl/english-words).
Each word is processed into three parts, punctuations at the beginning, the word
itself, and punctuations at the end. The punctuations are used to reconstruct the
word after the correction is made. Each word is passed into the Bloom Filter to
check if it is a valid word. If the Bloom filter returns that the word is not
present, the BK Tree is used to suggest corrections. If the Bloom suggests that
the word may be present, the BK Tree is used to confirm the presence of the word.
If the word is not present in the dictionary, the user is asked for a correction.
The user can also choose to ignore the word or add the word to the dictionary,
prompting the BK Tree and Bloom Filter to be rebuilt.

![Spell Sweep](working.gif)

## Usage

To use Spell Sweeper, go to your terminal and run the following command:

`./spell_sweeper input_file output_file`
