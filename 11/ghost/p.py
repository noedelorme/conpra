from sys import stdin, stdout

"""
Trie implementation from https://www.geeksforgeeks.org/trie-insert-and-search/
"""
class TrieNode:
     
    # Trie node class
    def __init__(self):
        self.children = [None]*26
 
        # isEndOfWord is True if node represent the end of the word
        self.isEndOfWord = False
 
class Trie:
     
    # Trie data structure class
    def __init__(self):
        self.root = self.getNode()
 
    def getNode(self):
     
        # Returns new trie node (initialized to NULLs)
        return TrieNode()
 
    def _charToIndex(self,ch):
         
        # private helper function
        # Converts key current character into index
        # use only 'a' through 'z' and lower case
         
        return ord(ch)-ord('a')
 
 
    def insert(self,key):
         
        # If not present, inserts key into trie
        # If the key is prefix of trie node,
        # just marks leaf node
        pCrawl = self.root
        length = len(key)
        for level in range(length):
            index = self._charToIndex(key[level])
 
            # if current character is not present
            if not pCrawl.children[index]:
                pCrawl.children[index] = self.getNode()
            pCrawl = pCrawl.children[index]
 
        # mark last node as leaf
        pCrawl.isEndOfWord = True
 
    def search(self, key):
         
        # Search key in the trie
        # Returns true if key presents
        # in trie, else false
        pCrawl = self.root
        length = len(key)
        for level in range(length):
            index = self._charToIndex(key[level])
            if not pCrawl.children[index]:
                return False
            pCrawl = pCrawl.children[index]
 
        return pCrawl.isEndOfWord



def firstHaveStrategyToWin(pos):
    if pos.isEndOfWord: return True

    for i in range(26):
        nextPos = pos.children[i]
        if nextPos != None:
            if not firstHaveStrategyToWin(nextPos):
                return True
    return False

def firstHaveStrategyToLoose(pos):
    if pos.isEndOfWord: return False

    for i in range(26):
        nextPos = pos.children[i]
        if nextPos != None:
            if not firstHaveStrategyToLoose(nextPos):
                return True
    return False

def main():
    t = int(stdin.readline())
    for testcase in range(t):
        n,w = stdin.readline().split()
        n = int(n)
        w = int(w)

        words = []
        for i in range(w):
            temp = stdin.readline()
            words.append(temp[:-1].lower())

        t = Trie()
        for w in words:
            t.insert(w)

        leaHaveWinStrategy = firstHaveStrategyToWin(t.root)
        leaHaveLooseStrategy = firstHaveStrategyToLoose(t.root)
        
        #Scenario 1 (Lea begin, winner begin)
        scenario1 = False
        if leaHaveWinStrategy:
            scenario1 = True
        else:
            if leaHaveLooseStrategy:
                scenario1 = n%2==0
            else:
                scenario1 = False
        
        #Scenario 2 (Lea begin, looser begin)
        scenario2 = False
        if not leaHaveWinStrategy:
            scenario2 = False
        else:
            if not leaHaveLooseStrategy:
                scenario2 = not n%2==0
            else:
                scenario2 = True
        
        #Scenario 3 and 4 are deduced from the symetry of the game
        scenario3 = not scenario1
        scenario4 = not scenario2

        print("Case #"+str(testcase+1)+":")
        if scenario1: print("victory")
        else: print("defeat")
        if scenario2: print("victory")
        else: print("defeat")
        if scenario3: print("victory")
        else: print("defeat")
        if scenario4: print("victory")
        else: print("defeat")

        stdin.readline()

if __name__ == "__main__":
    main()