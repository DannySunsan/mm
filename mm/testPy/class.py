class Fish(object):

    def __init__(self,location) -> None:
        super().__init__()
        self._location = location

    @property
    def location(self):
        return self._location
    
    @location.setter
    def location(self,location):
        self._location = location

if __name__ == '__main__':
    f = Fish('china')
    print('fish is from %s' % f.location)
    try:
        n = 10
        i = 0
        n = n%i
    except ZeroDivisionError:
        print ('zero division!')
    else:
        print('other error!')
    finally:
        print('proccess is finally!')


