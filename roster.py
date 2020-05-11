import sys
from cs50 import SQL


# Opening SQL db
db = SQL("sqlite:///students.db")

# Verifying command line arguments
if len(sys.argv) != 2:
    print('Usage: python ./roster.py house')
    exit(1)

roster = db.execute("SELECT first, middle, last, birth FROM (SELECT first, middle, last, birth FROM students WHERE house = ?) ORDER BY last, first ", sys.argv[1])
for rows in roster:
    if rows.get('middle') == None:
        print(rows['first'], end=' ')
        print(rows['last'], end=', ')
        print('born', end=' ')
        print(rows['birth'])
        
    else:
        print(rows['first'], end=' ')
        print(rows['middle'], end=' ')
        print(rows['last'], end=', ')
        print('born', end=' ')
        print(rows['birth'])
        