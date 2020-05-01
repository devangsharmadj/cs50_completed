from cs50 import get_float

cash = get_float("Change Owed: ")
while cash <= 0:
    # Validating that the user gave valid input
    cash = get_float("Change Owed: ")

# Converting cash to int so that it is easier to do the arithematic
dollars = int(round(cash * 100))

coins = 0
while dollars > 0:
    # Doing the arithematic
    # While dollars is over 0
    if dollars >= 25:
        coins += 1
        dollars = dollars - 25
    elif dollars >= 10:
        coins += 1
        dollars = dollars - 10
    elif dollars >= 5:
        coins += 1
        dollars = dollars - 5
    else:
        coins += 1
        dollars = dollars - 1
print(f"{coins}")
       