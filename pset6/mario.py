from cs50 import get_int

h = 0
while (h < 1 or h > 8):
    h = get_int("Height: ")

for i in range(1, h+1):
    for j in range(h-i):
        print(" ", end = "")
    for cur in range(i):
        print("#", end = "")
    print("  ", end = "")
    for cur in range(i):
        print("#", end = "")
    print()
