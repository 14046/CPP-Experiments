'''Program containing several sorting algorithms'''
import sys


def selection_sort(number_list):
    '''An implementation of selection sort -
    For every element in a list, looks for the smallest number
    between the i'th and last element, then swaps the two values
    '''
    length = len(number_list)
    for index in range(length):
        lowest_index = index
        for ith_index in range(index + 1, length):
            if number_list[ith_index] < number_list[lowest_index]:
                lowest_index = ith_index
        number_list[lowest_index], number_list[index] = number_list[index], number_list[lowest_index]
    return number_list


def insertion_sort(number_list):
    '''An implementation of insertion sort -
    Takes the next unsorted number in an array, and inserts it
    into its sorted subarray, beginning at the front of the array
    '''
    for index in range(len(number_list) - 1):
        next_number = number_list[index + 1]
        if next_number < number_list[index]:
            lowest_index = index
            for index_2, number_2 in reversed(list(enumerate(number_list[:index]))):
                if number_2 < number_list[lowest_index] and number_2 > next_number:
                    lowest_index = index_2
            number_list.pop(index + 1)
            number_list.insert(lowest_index, next_number)
    return number_list


def bubble_sort(number_list):
    '''An implementation of bubble sort -
    Every element is compared to its next element and is swapped if
    the first element is less than its following element. This persists 
    unless a pass is made where no swaps have been made, indicating a sorted state
    '''
    length = len(number_list)
    while True:
        sorted = True
        for index in range(length - 1):
            if number_list[index + 1] < number_list[index]:
                sorted = False
                number_list[index], number_list[index + 1] = number_list[index + 1], number_list[index]
        if sorted == True:
            return number_list


def populate_list(list):
    '''Populates list of numbers with numbers taken from
    command-line arguments, excluding the program name
    '''    
    for number in sys.argv:
        if sys.argv.index(number) == 0:
            continue
        else:
            list.append(int(number))


def main():
    # Checks for arguments inputted at command-line
    if len(sys.argv) == 1:
        print("Usage: python3 sort.py # # # ...")
        sys.exit(0)

    numbers = []
    populate_list(numbers)

    while True:
        choice = input("Choose a sorting algorithm (selection, insertion, bubble): ")
        if choice.lower() == "selection":
            numbers = selection_sort(numbers)
            break
        elif choice.lower() == "insertion":
            numbers = insertion_sort(numbers)
            break
        elif choice.lower() == "bubble":
            numbers = bubble_sort(numbers)
            break

    print(numbers)

main()