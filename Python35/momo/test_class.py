
class TDP:

    
    
    def __init__(self, x, y, z):
        if type(x)!= int or type(y) != int or type(z) != int:
            raise ValueError
        self._xco = x
        self._yco = y
        self._zco = z
    
    def __str__(self):
        return f'x:{self._xco}, y:{self._yco}, z:{self._zco}'  

    def __add__(self, p1):
        x = p1._xco + self._xco
        y = p1._yco + self._yco
        z = p1._zco + self._zco
        return TDP(x, y, z)

    def __sub__(self, p1):
        x = p1._xco - self._xco
        y = p1._yco - self._yco
        z = p1._zco - self._zco
        return TDP(x, y, z)

class Car:

    maker = 'Subaru'
    brand = 'forester' 
    model = '2016'

    def __init__(self, owner, engine, wheel_style, insurance):
        self._owner = owner
        self._engine = engine
        self._wheel = wheel_style
        self._insurance = insurance

    def car_info(self):
        return f'owner:{self._owner} ,egine:{self._engine}, insurance:{self._insurance}'

    @classmethod
    def model_info(cls):
        return f'maker:{cls.maker}, brand:{cls.brand}, model:{cls.model}'

    @staticmethod
    def print_status(egine, owner):
        pass





if __name__ == '__main__':

    p1 = TDP(1, 1, 1)
    print (p1)

    p2 = TDP(1, 1, 2)
    print(p1+p2)


    car1 = Car('Jonn', 'v8 tubro','hexa_leaf' , 'inserance_method_1')

    print(car1.model_info())

    print(car1.car_info())