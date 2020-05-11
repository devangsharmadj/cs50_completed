import sys
from cs50 import SQL
import csv

# Verifying command line arguments
if len(sys.argv) != 2:
    print('Usage: python ./import.py csv file')
    exit(1)

# Opening SQL db
db = SQL("sqlite:///students.db")

with open(sys.argv[1], 'r') as file:
    csv_file = csv.DictReader(file)
    for row in csv_file:
        list_names = row['name'].split(' ')
        
        # Checking for middle name
        if len(list_names) == 2:
            list_names.insert(1, None)
        
        house = row['house']
        birth = row['birth']
        db.execute('INSERT INTO students (first , middle, last, house, birth) VALUES (?, ?, ?, ?, ?)',list_names[0], list_names[1], list_names[2], house, birth)
