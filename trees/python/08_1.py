import bst


# the solution in my view can be made by focusing on the fact that a single
# leaf node can be considered as a DLL, then using it as basic building block
# for constructing the lest part of the problem
def constructDLL(root):
    # I want to first get the DLL from LST
    if root.left:
        lstDLL = constructDLL(root.left)
        # now we wanna reach to the tail of the DLL, so we go to extreme right
        # in other words we can also say that we're finding inorder predecessor
        # (but only if we consider the tree as BST)
        while lstDLL.right:
            lstDLL = lstDLL.right
        # once you get the rightmost element then we have to make the right
        # pointer of it point to the root
        lstDLL.right = root
        # again as its a DLL, so root's left pointer must point back to leftDLL
        root.left = lstDLL

    if root.right:
        rstDLL = constructDLL(root.right)
        # in this case we need to go the extreme left
        while rstDLL.left:
            rstDLL = rstDLL.left
        # in this case we want the leftmost node to point to the root
        # so basically the next two lines are doing function of linking lists
        rstDLL.left = root
        root.right = rstDLL

    return root


def printDLL(head):
    temp = head
    while temp:
        print temp.data,
        temp = temp.right


if __name__ == '__main__':
    root = None
    BSTree = bst.BST()
    inp = input('enter the elements of tree separated by ,\n')
    for i in inp:
        root = BSTree.insert(root, i)

    root = constructDLL(root)

    # root now points to the actual root, which would be somewhere at center,
    # but for printing the DLL we want the left most node, so we go there
    while root.left is not None:
        root = root.left

    printDLL(root)

# time complexity = O(n^2)
# its like T(n) = 2T(n/2) + O(n)
# O(n) is time taken to merge the different lists as we are traversing the DLL
# and going to end (or front) of it
# space complexity = O(1)
