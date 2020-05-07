# @ author Devang Sharma
# Code for analyizing DNA

import csv
import sys


if len(sys.argv) != 3:
    print('Usage: python program CSV_file sequence')
# Making a list for storing the STRs

# Reading the CSV file
with open(sys.argv[1], 'r') as file:
    # Getting the STRs
    csv_file = csv.DictReader(file)
    str_list = csv_file.fieldnames.copy()
# Removing the 'names' field
names_field = str_list.pop(0)

max_strs = []
# Reading the sequence file
sequence_file = open(sys.argv[2], 'r')
dna = sequence_file.read()
for strs in str_list:
    str_len = len(strs)
    high = 0
    i = 0
    temp = 0
    # Temp will check the end of the DNA sequence
    while temp < len(dna):
        # compare will be used to compare the strs with the sequence
        compare = dna[i: str_len + i]
        counter = 0
        while compare == strs:
            # Setting new values for the variables
            counter += 1
            i += str_len
            compare = dna[i: str_len + i]
            temp += str_len
        #print(strs, counter)
        if counter > high:
            high = counter
        i += 1
        temp += 1
    max_strs.append(high)
with open(sys.argv[1], 'r') as database_file:
    csv_file = csv.reader(database_file)
    for rows in csv_file:
        # Popping the first item of the list
        names = rows.pop(0)
        int_rows = []
        # changing all the items in the rows list from type int to str
        most_str = []
        for i in max_strs:
            most_str.append(str(i))
        if rows == most_str:
            print(names)
            exit(1)
            
    print('No Match')
        