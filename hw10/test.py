class Fraction:
    def __init__(self, numerator, denominator):
        self.num = numerator
        self.den = denominator

    def __add__(self, other):
        new_num = self.num * other.den + self.den * other.num
        new_den = self.den * other.den
        return Fraction(new_num, new_den)

    def __mul__(self, other):
        new_num = self.num * other.num
        new_den = self.den * other.den
        return Fraction(new_num, new_den)
        

#### main code ####
R  = Fraction(1,2)
S  = Fraction(3,4)
T = R + S
W = R * S
print(T.num,"/",T.den)
print(W.num,"/",W.den)