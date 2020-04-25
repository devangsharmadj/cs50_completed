from cs50 import get_int

height = get_int("Height: ")
while True:
    if height > 8 or height < 1:
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
    print()