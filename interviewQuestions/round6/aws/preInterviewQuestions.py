# utility function: if num is a power of two, it has exactly one bit set
# so n - 1 has this one bit flipped to zero, and all of the bits after it 
# set to one --> so "and"-ing them will give zero
def is_power_of_two(num: int) -> bool:
    if (num & (num - 1)) == 0 and num != 0:
        return True
        
    return False

# This function recives an array (list) of numbers and it returns
# the maximum range of numbers in the array that are a power of two.
# for example:
# 1. given the array [4, 2, 16] --> the return value is 3 [4, 2, 16]
# 2. given the array [4, 5, 8, 16] --> the return value is 2 [8, 16]
def find_max_range_of_power_of_two(arr: list) -> int:
    # iterate over the array till you reach the first power of two
    # number. This is assumed to be the start index of the "interval"
    # of numbers that are a power of two
    func_name = "find_max_range_of_power_of_two - "
    max_range_count = 0
    curr_range_count = 0
    
    # examples:
    # | 4 | 2 | 5 | 8 | --> return 2
    # | 4 | 2 | 8 |     --> return 3
    arr_len = len(arr)
    print (func_name + "got the array:" + str(arr) + " which has:" + str(arr_len) + " elements in it")
    for i in range(arr_len):
        print(func_name + "arr[" + str(i) + "]:" + str(arr[i]))
        if is_power_of_two(arr[i]):
            curr_range_count += 1
        else:
            if curr_range_count > max_range_count:
                max_range_count = curr_range_count
                curr_range_count = 0
                
    # edge case that the array ended with a number that facilitate the condition
    # so do the check here to make sure we don't miss this scenario
    if curr_range_count > max_range_count:
        max_range_count = curr_range_count
        
    return max_range_count
    
def find_max_range_of_power_of_two_usage_example():
    func_name = "find_max_range_of_power_of_two_usage_example - "
    arr1 = [4, 2, 6, 8]
    print(func_name + "sending the array:" + str(arr1))
    ret_val = find_max_range_of_power_of_two(arr1)
    print(func_name + "ret val is:" + str(ret_val))
    arr2 = [4, 5, 6, 8]
    print(func_name + "sending the array:" + str(arr2))
    ret_val = find_max_range_of_power_of_two(arr2)
    print(func_name + "ret val is:" + str(ret_val))
    arr3 = [4, 5, 6, 7]
    print(func_name + "sending the array:" + str(arr3))
    ret_val = find_max_range_of_power_of_two(arr3)
    print(func_name + "ret val is:" + str(ret_val))
    arr4 = [4, 2, 8, 7, 16, 32]
    print(func_name + "sending the array:" + str(arr4))
    ret_val = find_max_range_of_power_of_two(arr4)
    print(func_name + "ret val is:" + str(ret_val))

if __name__ == "__main__":
    print("main - start")
    
    find_max_range_of_power_of_two_usage_example()
    print("main - end")
