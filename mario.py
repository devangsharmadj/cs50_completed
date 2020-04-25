from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 7 or height < 0:
        height = get_int("Height: ")
    else:
        break

# Printing the pyramid
for i in range(height):
    for j in range(height):
        if height - 1 - i > j:
            print(" ", end="")
        else:
            print("#", end="")
    # Printed the first pyramid above
    print("  ", end="")
    # Printed the spaces in between
    # Printing the second pyramid Below
    for j in range(height):
        if j < i or j == i:
            print("#", end="")
        else:
            break
    # Printing a new line
    print()
