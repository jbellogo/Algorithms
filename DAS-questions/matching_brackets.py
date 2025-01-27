#### Create isValidExpression : str - > bool that checks if the order of the parentheses in the string is valid.
# A valid expression has a matching pair of parentheses for every opening parenthesis, including {}, [], and ().


class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()
    
    def isEmpty(self):
        return len(self.items) == 0

def isValidExpression(s: str) -> bool:
    stack = Stack()
    map_right2left = {')': '(', '}': '{', ']': '['}
    for char in s:
        if char in ['(', '{', '[']:
            stack.push(char)
        elif char in [')', '}', ']']:
            if map_right2left[char] != stack.pop():
                return False
    return stack.isEmpty()

if __name__ == "__main__":
    assert isValidExpression("324jdejnde{(((") == False
    assert isValidExpression("3{(((dededewwdedew)))}") == True
    assert isValidExpression("3[(((dedew)))}") == False
    assert isValidExpression("{3[(((dedew)))]eddedede}dee") == True


