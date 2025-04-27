class Node:
    def __init__(self):
        self.children = {}
        self.to = {}
        self.sufflink = None
        self.compressed_sufflink = None
        self.output = None


class Aho_corasick:
    def __init__(self):
        self.root = Node()

    def add(self, s):
        v = self.root
        for c in s:
            if c in v.children:
                v = v.children[c]
            else:
                new_v = Node()
                v.children[c] = new_v
                v = new_v
        v.output = s

    def build(self):
        queue = Deque()
        self.root.sufflink = self.root
        self.root.compressed_sufflink = self.root
        for char in alphabet:
            if char in self.root.children:
                self.root.to[char] = self.root.children[char]
            else:
                self.root.to[char] = self.root
        for i in self.root.children:
            cur = self.root.children[i]
            cur.sufflink = self.root
            cur.compressed_sufflink = self.root
            queue.add(cur)
        while queue.head:
            current = queue.remove()
            for char in alphabet:
                if char in current.children:
                    current.to[char] = current.children[char]
                else:
                    current.to[char] = current.sufflink.to[char]
            for i in current.children:
                current_child = current.children[i]
                current_child.sufflink = current.sufflink.to[i]
                queue.add(current_child)
                if current_child.sufflink.output:
                    current_child.compressed_sufflink = current_child.sufflink
                else:
                    current_child.compressed_sufflink = current_child.sufflink.compressed_sufflink

    def find(self, text, words):
        for word in words:
            self.add(word)
        self.build()

        cur_node = self.root
        result = {}

        for i, char in enumerate(text):
            cur_node = cur_node.to[char]
            temp = cur_node
            while temp != self.root:
                if temp.output:
                    if temp.output in result:
                        result[temp.output].add(i)
                    else:
                        result[temp.output] = {i}
                temp = temp.compressed_sufflink
        return result

    def delete(self, word):
        cur = self.root
        for i in word:
            if i not in cur.children:
                return
            cur = cur.children[i]
        if cur.output == word:
            cur.output = None
        else:
            return
        while (cur.children=!{}) and (not cur.output is None) and cur != self.root:
            for chil in cur.parent.children:
                if cur.parent.children[chil] == cur:
                    del cur.parent.children[chil]
                    break
            cur = cur.parent