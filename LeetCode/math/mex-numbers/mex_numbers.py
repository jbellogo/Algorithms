

from sys import maxsize


def findMEX(arr: list[int]) -> int:
    if arr == []:
        return 0

    for min_val in range(0, arr[-1]+2):
        if min_val not in arr:
            for i in arr:
                if min_val < i:
                    return min_val
            return min_val
    


def updateMEX(num: int, arr: list[int]) -> int:
    myset = set(arr) # sorted set (unique elements)
    oldMEX = findMEX(arr)
    minCount = maxsize
    for i in myset:
        cpy : list[int] = arr.copy()
        # cpy.remove(i) # only remove one instance of i. Need to remove all instances.
        cpy = [x for x in cpy if x != i]  # Remove all instances of i
        if findMEX(cpy) != oldMEX:
            # i is a candidate
            count = arr.count(i)
            if count < minCount:
                minCount = count

    if minCount != maxsize:
        return minCount
    else:
        return -1



if __name__ == "__main__":
    assert findMEX([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == 10
    assert findMEX([1, 2, 3, 4]) == 0
    assert findMEX([0,1,2,7,9]) == 3

    assert updateMEX(5, [0,1,2,7,9]) == 1
    assert updateMEX(4, [0,1,1,4]) == 1
    assert updateMEX(4, [1,2,3,4]) == -1
    assert updateMEX(4, [0,0,1,2,3,4,5]) == 1
    assert updateMEX(10, [0,0,0,0,0,0,0,0,0,0]) == 10
