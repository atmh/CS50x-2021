import sys
import csv

def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    STR = []
    profile = []

    #open data file
    with open(sys.argv[1], mode = "r") as data:
        reader = csv.DictReader(data)
        STR = reader.fieldnames[1:]

        #append
        for row in reader:
            profile.append(row)

    dic = dict.fromkeys(STR, 0)

    #open sequence file
    with open(sys.argv[2], mode = "r") as seq:
        sequence = seq.readline()
        for i in STR:
            # update dic with repeats
            dic[i] = find_repeats(sequence, i)

    for pro in profile:
        count = 0

        for i in STR:
            if int(pro[i]) != dic[i]:
                continue
            count += 1

        if count == len(STR):
            print(pro['name'])
            exit(0)

    print("No match")
    sys.exit(1)

def find_repeats(sequence, s):
    length = len(s)
    count = 0
    for i in range(len(sequence)):
        repeat = 0

        if sequence[i : i + length] == s:
            repeat += 1
            while sequence[i : i + length] == sequence[i + length: i + (2 * length)]:
                i += length
                repeat += 1

        if count < repeat:
            count = repeat

    return count

if __name__ == "__main__":
    main()