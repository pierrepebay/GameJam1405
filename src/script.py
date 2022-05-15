f = open("map.txt", "r")
# read lines
lines = f.readlines()
# close file
f.close()
# split lines
for line in lines:
    print(" ".join(line))
