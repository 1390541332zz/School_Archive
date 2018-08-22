#!/usr/bin/python3

from statistics import mean
import random

from matplotlib.ticker import MaxNLocator
import matplotlib.pyplot as plt

def print_bin(x, name):
    print("\n{}:{}".format(name, len(x)))
    print("[{}]".format(", ".join(map(str, x))))
    print("avg: {}".format(mean(x)))
    print("min: {}".format(min(x)))
    print("max: {}".format(max(x)))

rand_val = []
rand_ratio = 0

for i in range(100):
    x = random.randint(0,999)
    while x in rand_val:
        rand_ratio += 1
        x = random.randint(0,999)
    rand_val.append(x)
rand_ratio /= (rand_ratio + 100)
bin_200  = list(filter(lambda x: (x >=   0) and (x <  200), rand_val))
bin_400  = list(filter(lambda x: (x >= 200) and (x <  400), rand_val))
bin_600  = list(filter(lambda x: (x >= 400) and (x <  600), rand_val))
bin_800  = list(filter(lambda x: (x >= 600) and (x <  800), rand_val))
bin_1000 = list(filter(lambda x: (x >= 800) and (x < 1000), rand_val))

print("100 unique random values:")
print("{{{}}}".format(", ".join(map(str, rand_val))))
print("\npercentage of not unique random values created by python: {}".format(rand_ratio))
print_bin(bin_200, "bin_200")
print_bin(bin_400, "bin_400")
print_bin(bin_600, "bin_600")
print_bin(bin_800, "bin_800")
print_bin(bin_1000, "bin_1000")

plt.figure().gca().yaxis.set_major_locator(MaxNLocator(integer=True))
plt.xlabel('bins')
plt.ylabel('number of elements')
plt.title('Histogram of 100 unique values')


plt.hist(rand_val, bins=5, rwidth=0.8, color='cyan')

plt.show()

