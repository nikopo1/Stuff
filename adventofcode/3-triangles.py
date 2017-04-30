#!/usr/bin/python

fname = "3-triangles.in"

total = 0
count = 0
content = []

with open(fname) as f:
    content = f.readlines()

ints = []

for line in content:
    tmp = []
    for integer in line.split():
        tmp.append(int(integer))
    ints.append(tmp)

ints = [list(i) for i in zip(*ints)]
ints = sum(ints, [])

print len(ints)

num_triangles = len(ints) / 3

for triangle in range(0, num_triangles):
    valid = True
    triangle *= 3

    for i in range(0, 3):
        for j in range(0, 3):
            for k in range(0, 3):
                if i != j and j != k and i != k:
                    if ints[triangle + i] + ints[triangle + j] <= ints[triangle + k] and valid == True:
                        valid = False

    if valid == True:
        count += 1

    total += 1

print "Total: " + str(total)
print "Valid: " + str(count)

