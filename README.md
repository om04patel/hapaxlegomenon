# Hapax Legomena Finder
The Hapax Legomena Finder is a C program designed to identify and list hapax legomena from one or more text files. A hapax legomenon is a word that occurs only once in a document. This tool parses the text, counts the occurrences of each word, and outputs words that meet the hapax legomenon criteria.

# Features
-Multi-file Processing: Handles multiple text files in a single run.

-Word Length Filtering: Allows filtering of hapax legomena by word length.

-Detailed Statistics: Provides a total word count and lists of hapax legomena.

-Command-line Interface: Easy-to-use command-line options for flexible operation.

# Usage
hapax <options> <datafile> <datafile> ...
# Options
-d: Print all data loaded before printing hapax legomena.

-h: Display help information.

-l <N>: Only print hapax legomena of length <N>. If not specified, all hapax legomena are printed.

# Examples

Example 1: Basic Usage

./hapax smalldata.txt

Output:

Total word count 10
Tally loaded
Hapax legomena from file 'smalldata.txt':
    a
    is
    line
    test
    this
    three
    there
    where

Example 2: Filter by Word Length

./hapax -l 4 smalldata.txt

Output: 

Total word count 10
Tally loaded
Hapax legomena from file 'smalldata.txt':
    line
    test
    this

# Implementation Details

Data Structures

-Linked Lists: Used to store and manage words of varying lengths.

-Arrays of Linked Lists: An array where each index corresponds to a word length, and each element is a linked list of words of that length.

Program Flow

1.) Command Line Parsing: Handle input options and filenames.

2.) Word Extraction: Use the provided word extractor to parse words from files.

3.) Word Counting: Tally the occurrences of each word using linked lists.

4.) Hapax Identification: Identify words that occur only once.

5.) Output: Print or save the hapax legomena based on the command-line options.

# Building the Project
To compile he project, use the provided makefile:

make

To clean up the build files:

make clean

# Dependencies
-C compiler supporting C11 standard.

-make utility.

-valgrind (for memory leak detection and debugging).
