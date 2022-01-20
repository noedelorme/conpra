from sys import stdin, stdout

#This is the python translation of my previous attempts using C++
#I guess the problem with C++ was the memory allocation that I
#don't really know how to deal with (especially when dealing with
#destructors).


"""
Trie implementation from https://www.geeksforgeeks.org/trie-insert-and-search/
"""
class TrieNode:
    def __init__(self):
        self.children = [None]*26
        self.isEndOfWord = False
        self.counted = False

class Trie:
    def __init__(self):
        self.root = self.getNode()

    def getNode(self):
        return TrieNode()

    def _charToIndex(self,ch):
        return ord(ch)-ord('a')

    def insert(self,key):
        pCrawl = self.root
        length = len(key)
        flag = False
        count = 0
        for level in range(length):
            index = self._charToIndex(key[level])
 
            if not pCrawl.children[index]:
                pCrawl.children[index] = self.getNode()
                flag = True

            #If during the adding of key we visite a final node that we didn't counter yet
            if pCrawl.isEndOfWord and not pCrawl.counted:
                count += 1
                pCrawl.counted = True
            
            pCrawl = pCrawl.children[index]
 
        #If a longer name with prefix key as already been added
        if not flag and not pCrawl.counted:
            count += 1
            pCrawl.counted = True

        pCrawl.isEndOfWord = True
        return count


def main():
    t = int(stdin.readline())
    for testcase in range(t):
        n = int(stdin.readline())
        
        names = []
        for i in range(n):
            temp = stdin.readline()
            names.append(temp[:-1].lower())

        total = 0
        t = Trie()
        for s in names:
            total += t.insert(s)

        print("Case #"+str(testcase+1)+":", total)
        stdin.readline()

if __name__ == "__main__":
    main()