# assignment part 2!
#isStringPermutation(...)

def isStringPermutation(s1, s2):
    values_true = {}
    for letter in s1:
        values_true[letter] = 1
    for letter in s2:
        print(values_true.keys())
        if letter in values_true.keys():
            values_true[letter] = 2
        else:
            print("false after keys")
            return False 
    
    if 1 in values_true.values():
        return False
    return True


print(isStringPermutation("asdf", "fsda"))
print(isStringPermutation("asdf", "fsa"))
print(isStringPermutation("asdf", "fsax"))

def pairsThatEqualSum(targetArray, sum):
    sums = []
    for number in targetArray:
        for i in targetArray:
            if number+i == sum:
                if number>i:
                    larger = number
                    smaller = i
                else:
                    smaller = number
                    larger = i
                ordered = []
                ordered.append([smaller, larger])
                if ordered[0] in sums:
                    continue
                sums.append(ordered[0])

    return sums
    
print(pairsThatEqualSum([1, 2, 3, 4, 5],5 ))
print(pairsThatEqualSum([1, 2, 3, 4, 5], 1))
print(pairsThatEqualSum([1, 2, 3, 4, 5], 7))