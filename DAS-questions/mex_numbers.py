# MEX is the smallest natural number that is not in the array.
# write updateMEX : list[int], int -> int
# takes arr and len(arr) and removes the minimum number of elements from it 
# so that the MEX value of the modified arrray is different from the original MEX value.

# code just returns minimum number of elements to remove. -1 if not possible.

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
    sorted_arr = sorted(arr)
    oldMEX = findMEX(sorted_arr)
    count = 0
    while len(sorted_arr) > 0:
        sorted_arr.remove(sorted_arr[0])
        newMEX = findMEX(sorted_arr)
        count += 1
        if newMEX != oldMEX:
            return count
    return -1



if __name__ == "__main__":
    assert findMEX([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == 10
    assert findMEX([1, 2, 3, 4]) == 0
    assert findMEX([0,1,2,7,9]) == 3

    assert updateMEX(5, [0,1,2,7,9]) == 1
    assert updateMEX(4, [0,1,1,4]) == 1
    assert updateMEX(4, [1,2,3,4]) == -1
    ## Ah but this one is wrong now.
    assert updateMEX(4, [0,0,1,2,3,4,5]) == 1
