
def list_of_words_with_same_letters(orig_list: list) -> list:
    print("list_of_words_with_same_letters - got the list:" + str(orig_list))
    words_dict = dict()
    ret_list = []
    # for each word, do the following:
    # 1. sort it in a lexicographical order
    # 2. insert it, if applicable, into a map --> if the map already has this string
    #    mapped --> ignore it
    for word in orig_list:
        print("checking whether the word:" + str(word) + " should be added to the map")
        word_sorted = ''.join(sorted(word))   
        print("the sorted string of the word:" + str(word) + " is:" + str(word_sorted))
        
        # if this is the first time the sorted word is encountered, add it to the ret_list 
        # when the loop is done, there will be a second loop to remove all words that did not
        # have one (or more) "similar words"
        if word_sorted not in words_dict:
            print("the word_sorted:" + str(word_sorted) + " is encountered for the first time, add it to the resulting list"
                 + " and to the dictionary")
            ret_list.append(word)
            words_dict[word_sorted] = 1
            continue
        
        else:   #if word_sorted is in words_dict:
            print("adding the original word:" + str(word) + " to the returning list to presreve the order from the original list")
            ret_list.append(word)
            words_dict[word_sorted] += 1
    
    # iterate over the ret_list and remove all words from it if they appear only once in the words_dict
    for word in ret_list:
        if words_dict[''.join(sorted(word))] == 1:
            print("the original word:" + str(word) + " did NOT have any additional similar word(s), remove it from the resulting list")
            ret_list.remove(word)
    
    # finally, return the ret_list
    return ret_list


if __name__ == "__main__":
    print("main - start")
    orig_list = ["pool", "hey", "why", "polo", "pol", "lopo", "apolo", "hye"]
    resulting_list = ["pool", "hey", "polo", "lopo", "hye"]
    ret_list = list_of_words_with_same_letters(orig_list)
    print("main - the resulting list is:" + str(ret_list))
    print("main - end")
