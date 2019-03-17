# classical probability problem
# 3 doors, one-car and two-goats
# choose one door
# then destroy another door, which must not be car-door or the opened-door
# the probability of the-rest-door is car-door
# 1 / 2 is the incorrect answer
# 2 / 3 is the amazing corret answer

import numpy as np

f = lambda : np.random.randint(0, 3)


times = 10000
cnt_nc = 0.0
cnt_ch = 0.0

for i in range(0, times):
    doors = [0, 1, 2]
    res = f()
    choose = f()

    oid = -1
    d = [0, 1, 2]
    d.remove(res)
    # oid, the destroy_door id
    if choose == res:
        temp = np.random.randint(2)
        oid = d[temp]
    else:
        d.remove(choose)
        oid = d[0]
    del d

    # the beginning opened door
    if res == choose:
        cnt_nc += 1.0

    # the rest door
    d = [0, 1, 2]
    d.remove(oid)
    d.remove(choose)
    if res == d[0]:
        cnt_ch += 1.0
    del d


print('not change', cnt_nc / times)
print('do changed', cnt_ch / times)
