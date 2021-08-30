import sys


def selection_sort(number_list):
    '''An implementation of selection sort -
    The first loop iterates through all indexes of the list.
    The second loop iterates through all indexes from the current index to the last index.
    The number at the current index is then swapped with the next lowest number.
    '''
    length = len(number_list)
    for index in range(length):
        lowest_index = index
        for ith_index in range(index + 1, length):
            if number_list[ith_index] < number_list[lowest_index]:
                lowest_index = ith_index
        number_list[lowest_index], number_list[index] = number_list[index], number_list[lowest_index]
    return number_list


def populate_list(list):
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

    numbers = selection_sort(numbers)
    print(numbers)

main()