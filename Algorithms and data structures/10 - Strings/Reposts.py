class Lexer:
    
    SIGNS = "+-*/%^=()."

    def __init__(self, expression):
        self.expression = expression
        self.counter = 0
        self.lexems = self.prepareLexems()

    def prepareLexems(self):
        tokens = []
        token = ''
        i = 0
        while self.expression[i] != '.':
            if self.expression[i].isspace():
                i += 1
                continue
            
            if self.expression[i] in Lexer.SIGNS:
                tokens.append(self.expression[i])
                i += 1
                
            elif self.expression[i].isdigit():
                while self.expression[i] not in Lexer.SIGNS:
                    token += self.expression[i]    
                    i += 1
                tokens.append(token)
            token = ''
        return tokens

    def getLexemsCount(self):
        return len(self.lexems)
    
    def nextLexem(self):
        current_index = self.counter
        self.counter += 1
        return self.lexems[current_index]

expression = input()    
lexer = Lexer(expression)
for _ in range(lexer.getLexemsCount()):
    print(lexer.nextLexem())