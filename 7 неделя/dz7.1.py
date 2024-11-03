class Vector:
    def __init__(self,x,y,z):

        self.x=x
        self.y=y
        self.z=z
    def __abs__(self):
        return (self.x**2+self.y**2+self.z**2)**0.5
    def __add__(self,other):
        assert isinstance(other, Vector)
        return Vector(self.x+other.x,self.y+other.y,self.z+other.z)
    def __sub__(self,other):
        assert isinstance(other, Vector)
        return Vector(self.x-other.x,self.y-other.y,self.z-other.z)
    def __mul__(self,other):
        if isinstance(other,Vector):
            return self.x*other.x+self.y*other.y+self.z*other.z
        if isinstance(other,float):
            return Vector(self.x*other,self.y*other,self.z*other)
        else:
            raise AssertionError
    def mass_center(l):
        start=Vector(0,0,0)
        for i in l:
            start+=i
        return start*(1/len(l))
    def __truediv__(self,other):
        assert isinstance(other(int,float))
        return vector(self.x/other,self.y/other,self.z/other)
    def vector_mul(self,other):
        assert isinstance(other,Vector)
        return Vector(self.y*other.z-self.z*other.y,self.z*other.x-self.x*other.z,self.x*other.y-self.y*other.x)
    def __str__(self):
        return f'x = {self.x} y = {self.y} z = {self.z}'
    def area(x,y,z):
        return(abs((x-y).vector_mul(x-z))/2)
    def max_area(l):
        max=0
        res=()
        for i in l:
            for j in l:
                for k in l:
                    t=Vector.area(i,j,k)
                    if t>max:
                        max=t
                        res=(i,j,k)
        return max