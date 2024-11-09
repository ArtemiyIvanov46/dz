class Node:
    def __init__ (self, val= None):
        self.val=val
        self.next=None
        self.prev=None

class LinkedList:
    def __init__(self):
        self.head=None
        self.len=0
    def contains(self,val):
        cur=self.head
        while(cur):
            if cur.val==val:
                return True
            else:
                cur=cur.next
        return False
    def get(self,index):
        if index>=self.len():
            print('Incorrect index')
            return
        cur=self.head
        for i in range(index):
            cur=cur.next
        return cur.val
    def add(self,index,val):
        new_node=Node(val)
        if index>self.len:
            print('incorrect index')
            return
        cur=self.head
        if index==0:
            if cur is None:
                self.head=new_node
                self.len+=1
                return
            cur.prev=new_node
            new_node.next=cur
            self.head=new_node
            self.len+=1
            return
        if index==self.len:
            for i in range(index-1):
                cur=cur.next
            cur.next=new_node
            new_node.prev=cur
            self.len+=1
            return
        for i in range(index):
            cur=cur.next
        cur.prev.next=new_node
        new_node.prev=cur.prev
        cur.prev=new_node
        new_node.next=cur
        self.len+=1
    def __len__(self):
        return(self.len)
#удаление по индексу, как в задании
    def remove(self,index):
        if index>=self.len():
            print('Incorrect index')
            return
        cur=self.head
        for i in range(index):
            cur=cur.next
        cur.prev.next=cur.next
        cur.next.prev=cur.prev