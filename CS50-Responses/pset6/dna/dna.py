# Takes a sequence of DNA, and checks for matches within a given DNA database by comparing 'short tandem repeats'

# sys to access command-line arguments and exit codes
# csv module to read from .csv files
import sys
import csv

# Dictionary of people, with a list of corresponding STR values
database = {}

# Dictionary, mapping STRs, and their highest counts
STR = {}


# Compares the STR counts in the sequence to people in the database, and returns any potential matching person
def findPerson():
    global database
    global STR

    for person in database:
        match = True
        for key in STR:
            if STR[key] == int(database[person][key]):
                continue
            else:
                match = False
                break
        if match == True:
            return person
        else:
            continue
        
    return "No match"


# Adds values from .csv file to dictionaries
def loadDatabase(location):
    global database
    global STR
    
    # Populates STR dictionary with STRs in .csv columns
    with open(f"{location}", "r") as file:
        reader = csv.DictReader(file)
        for key in next(reader):
            if key == 'name':
                continue
            else:
                bufferDict = {f"{key}": ""}
                STR.update(bufferDict)
    
    # Populates database array with dictionaries of people, and sub-dictionaries of their STRs
    # Sub-dictionaries must be initialized with an empty dictionary in order to add new key-values using update()
    with open(f"{location}", "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            emptyDict = {}
            database[row['name']] = emptyDict
            for key in row:
                if key == 'name':
                    continue
                bufferDict = {f"{key}": f"{row[f'{key}']}"}
                database[row['name']].update(bufferDict)


# Returns string of .txt file
def loadSequence(location):
    with open(f"{location}", "r") as file:
        return file.read()


# Returns the highest amount of times an STR appears sequentially within a sequence
def STRcount(STR, sequence):
    highestCount = 0
    lengthSTR = len(STR)
    lengthSequence = len(sequence)

    for position in range(lengthSequence):
        count = 0
        while sequence[position:position + lengthSTR] == STR:
            count += 1
            position += lengthSTR
        if count > highestCount:
            highestCount = count

    return highestCount


def main():
    # Checks if .csv and .txt arguments are inputted
    if len(sys.argv) != 3:
        print("Correct usage: Usage: python dna.py data.csv sequence.txt")
        sys.exit(0)

    loadDatabase(f"{sys.argv[1]}")

    DNA = loadSequence(f"{sys.argv[2]}")

    for key in STR:
        STR[key] = STRcount(key, DNA)

    print(findPerson())


main()