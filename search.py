'''Program containing several searching algorithms'''
import sys

# List of numbers inputted at command-line
numbers = []


def populate_list():
    '''Populates list of numbers with numbers taken from
    command-line arguments, excluding the program name
    '''
    for arg in sys.argv:
        if (sys.argv.index(arg) == 0):
            continue
        else:
            numbers.append(int(arg))


def linear_search(target):
    # Implementation of linear search
    for number in numbers:
        if number == target:
            index = numbers.index(number)
            print(f"{target} is at index {str(index)}")
            return
    print("That number is not present in the list")


def binary_search(target, number_list):
    # Recursive implementation of binary search
    middle_index = len(number_list) // 2
    middle_number = number_list[middle_index]
    if middle_number == target:
        index = numbers.index(middle_number)
        print(f"{target} is at index {str(index)}")
    elif middle_index == 0:
        print("That number is not present in the list")
    elif middle_number < target:
        binary_search(target, number_list[-middle_index:])
    elif middle_number > target:
        binary_search(target, number_list[:middle_index])
        
    
def main():
    # Checks for 1+ command-line arguments
    if (len(sys.argv) == 1):
        print("Correct usage: python3 search.py # # # ...")
        sys.exit(0)

    populate_list()

    # Prompt for target number
    while True:
        try:
            number = int(input("Target number: "))
            break
        except ValueError:
            pass
    
    # Prompts for search algorithm
    while True:
        choice = input("Select search algorithm (linear, binary): ")
        if choice.lower() == "linear":
            linear_search(number)
            break
        elif choice.lower() == "binary":
            binary_search(number, numbers)
            break


main()