from cs50 import get_string

def main():
    count = 0
    l_count = 0
    w_count = 1
    s_count = 0

    text = get_string("Text: ")

    for c in text:
        if c.isalpha():
            l_count += 1
        elif c == " ":
            w_count += 1
        elif c == "." or c == "!" or c == "?":
            s_count += 1

    grade = round(0.0588 * (100 * l_count / w_count) - 0.296 * (100 * s_count / w_count) - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

if __name__ == "__main__":
    main()