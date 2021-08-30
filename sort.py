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
    length = len(number_list)
    for count, number in enumerate(number_list):
        if count == length - 1:
            break
        next_number = number_list[count + 1]
        if next_number < number:
            lowest_index = count
            for count_2, number_2 in reversed(list(enumerate(number_list[:count]))):
                if number_2 < number_list[lowest_index] and number_2 > next_number:
                    lowest_index = count_2
            number_list.pop(count + 1)
            number_list.insert(lowest_index, next_number)
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

    numbers = insertion_sort(numbers)
    print(numbers)

main()