from cs50 import get_int
from math import floor

def main():
    # Variables
    n = 0
    digits = 0
    temp = 0
    boo = False

    # Prompt for number
    n = get_int("Number: ");

    # count digits
    temp = n;
    count = 0;
    sum = 0;
    while temp > 0:
        # odd digits
        if count % 2 == 1:
            hello = temp % 10 * 2
            if hello > 9:
                hello -= 9
            sum += hello
        # even digits
        else:
            sum += temp % 10
        temp = floor(temp / 10)
        count += 1

    # print validity
    if sum % 10 == 0:
    # amex
        if count == 15 and (floor(n / 10000000000000) == 34 or floor(n / 10000000000000) == 37):
            print("AMEX");
            boo = True;
        # visa
        elif count == 13 and floor(n / 1000000000000) == 4:
            print("VISA");
            boo = True;
        # visa / master
        elif count == 16:
            f = floor(n / 100000000000000);
            if floor(n / 1000000000000000) == 4:
                print("VISA");
                boo = True;
            elif (f == 51 or f == 52 or f == 53 or f == 54 or f == 55):
                print("MASTERCARD");
                boo = True;
    if not boo:
        print("INVALID")

if __name__ == "__main__":
    main()