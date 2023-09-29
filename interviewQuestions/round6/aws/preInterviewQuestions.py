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

# use cases:
# empty array
# array with one interval
# array with 3 time intervals:
# 1. all distinct                               [[1, 3] , [5, 7], [8, 10]]
# 2. the 2nd  is within the first entierly      [[1, 4] , [2, 3], [5, 7]]
# 3. the 2nd is within the 1st and the 3rd      [[1, 4] , [2, 6], [5, 7]]
# 4. the 2nd is within the 3rd entierly         [[1, 4] , [6, 7], [5, 8]]
# 5. the 2nd is ends AFTER the 3rd              [[1, 4] , [2, 8], [5, 7]]

# 6. the 1st ends AFTER the 3rd                 [[1, 10] , [2, 8], [5, 7]]

def merge_intervals(intervals: list) -> list:
    func_name = "merge_intervals - "
    if intervals is None:
        return None
    
    print(func_name + "got the original intervals array" + str(intervals))
    intervals.sort()
    print(func_name + "after sorting the original intervals array it is now:" + str(intervals))
    
    returned_list_of_merged_intervals = []
    # the intervals array is sorted, this MUST be the start of the first interval
    # (cause its start time is the minimal)
    prev_start_interval = intervals[0][0]
    
    # for start assume it also for the end time of the first interval
    prev_end_interval = intervals[0][1]
    
    for interval in intervals[1:]:
        # 1. lower bound IN
        if interval[0] < prev_end_interval:
            
            # 1.1 upper bound IN ([[1, 4] , [2, 3])
            if interval[1] < prev_end_interval:
                # The current iterated interval is enteirly within its predecessor, leave it out of the return list of intervals
                continue
        
            # 1.2 upper bound OUT ([[1, 4] , [2, 6]) 
            else:
                # take the END interval as a new candidate
                prev_end_interval = interval[1]
                continue
        
        # 2. lower bound OUT 
        else:
            # take the entire prev_start and prev_end as an interval in the resulting list
            returned_list_of_merged_intervals.append([prev_start_interval, prev_end_interval])
            
            # set the current interval as the "new prev"
            prev_start_interval = interval[0]
            prev_end_interval = interval[1]
            continue
    
    returned_list_of_merged_intervals.append([prev_start_interval, prev_end_interval])
    return returned_list_of_merged_intervals
   
def merge_intervals_usage_example():
    func_name = "merge_intervals_usage_example - "
    intervals1 = [[1, 4] , [2, 3]]
    print(func_name + "about to call the merge interval function for:" + str(intervals1))
    ret_list = merge_intervals(intervals1)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals2 = [[1, 4] , [5, 6]]
    print(func_name + "about to call the merge interval function for:" + str(intervals2))
    ret_list = merge_intervals(intervals2)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals3 = [[1, 4] , [2, 6]]
    print(func_name + "about to call the merge interval function for:" + str(intervals3))
    ret_list = merge_intervals(intervals3)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals4 = [[2, 3]]
    print(func_name + "about to call the merge interval function for:" + str(intervals4))
    ret_list = merge_intervals(intervals4)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals5 = [[1, 3] , [5, 7], [8, 10]]
    print(func_name + "about to call the merge interval function for:" + str(intervals5))
    ret_list = merge_intervals(intervals5)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals = [[1, 4] , [2, 3], [5, 7]]
    print(func_name + "about to call the merge interval function for:" + str(intervals))
    ret_list = merge_intervals(intervals)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals = [[1, 4] , [2, 6], [5, 7]]
    print(func_name + "about to call the merge interval function for:" + str(intervals))
    ret_list = merge_intervals(intervals)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals = [[1, 4] , [6, 7], [5, 8]]
    print(func_name + "about to call the merge interval function for:" + str(intervals))
    ret_list = merge_intervals(intervals)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals = [[1, 4] , [2, 8], [5, 7]]
    print(func_name + "about to call the merge interval function for:" + str(intervals))
    ret_list = merge_intervals(intervals)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
    intervals = [[1, 10] , [2, 8], [5, 7]]
    print(func_name + "about to call the merge interval function for:" + str(intervals))
    ret_list = merge_intervals(intervals)
    print(func_name + "the returned intervals merged list is:" + str(ret_list))
    
if __name__ == "__main__":
    print("main - start")
    
    find_max_range_of_power_of_two_usage_example()
    print("main - end")
