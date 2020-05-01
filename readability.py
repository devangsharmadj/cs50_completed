# @ author Devang Sharma
# Finding the U.S.A. Grade level for any text
# Using Coleman - Liau index


def main():
    s = input('Text: ')
    word = 1
    sent = 0
    char = 0
    # iterating through the whole string and figuring out
    # The words, sentences and characters
    for i in s:
        if i == ' ':
            word += 1
        elif i == '.' or i == '!' or i == '?':
            sent += 1
        elif i.isalpha():
            char += 1
    # Calling the grade function for printing the grade
    if grade(word, sent, char) < 1:
        print('Before Grade 1')
    elif grade(word, sent, char) > 16:
        print('Grade 16+')
    else:
        print(f'Grade {grade(word, sent, char)}')
    # Code for the Coleman- Liaux index


def grade(w, s, l):
    # Doing calculations
    '''
    Info : Function for the Coleman - Liau index
    '''
    L = 100 * l / w
    S = 100 * s / w
    index = .0588 * L - .296 * S - 15.8
    result = round(index)
    return result


main()
