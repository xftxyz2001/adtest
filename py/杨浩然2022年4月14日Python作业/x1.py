import math

i = 1
while True:
    i100 = i + 100
    i168 = i + 168
    if math.pow(math.floor(math.sqrt(i100)), 2) == i100 and math.pow(math.floor(math.sqrt(i168)), 2) == i168:
        print(i)
        break
    i += 1
