# Given a text, computes its grade level, according to the Coleman-Liau index

# get_string for string inputs
# re module for letter, word, and sentence matching with strings
from cs50 import get_string
import re

# Global variables
letters = 0
words = 0
sentences = 0


# Counts letters
def countLetters(text):
    global letters
    matches = re.findall("\w", text)
    for letter in matches:
        letters += 1
        
        
# Counts words
def countWords(text):
    global words
    matches = re.findall("[\s\\n]", text)
    for word in matches:
        words += 1
    words += 1


# Counts sentences
def countSentences(text):
    global sentences
    matches = re.findall("[.!?]", text)
    for sentence in matches:
        sentences += 1


# Runs Coleman-Liau index, and returns grade level
def colemanLiau():
    global letters, words, sentences
    L = (letters / words) * 100
    S = (sentences / words) * 100
    return round(0.0588 * L - 0.296 * S - 15.8)
    
    
# Takes a grade level, and prints corresponding result
def printGrade(grade):
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


# Main function
def main():
    text = get_string("Text: ")
    countLetters(text)
    countWords(text)
    countSentences(text)
    
    grade = colemanLiau()
    printGrade(grade)
    
    
# Runs main()
main()