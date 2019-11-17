from collections import namedtuple

# *** collections.namedtuple(typename, field_names, *, rename=False, defaults=None, module=None)
# Returns a new tuple subclass named typename. 
# The new subclass is used to create tuple-like objects that have fields accessible by attribute lookup as well as being indexable and iterable. 
# Instances of the subclass also have a helpful docstring (with typename and field_names) and a helpful __repr__() method which lists the tuple contents in a name=value format.

# The field_names are a sequence of strings such as ['x', 'y']. 
# Alternatively, field_names can be a single string with each fieldname separated by whitespace and/or commas, 
# for example 'x y' or 'x, y'.

# Any valid Python identifier may be used for a fieldname except for names starting with an underscore. 
# Valid identifiers consist of letters, digits, and underscores but do not start with a digit or underscore and cannot be a keyword such as class, for, return, global, pass, or raise.

# Any valid Python identifier may be used for a fieldname except for names starting with an underscore. 
# Valid identifiers consist of letters, digits, and underscores but do not start with a digit or underscore and cannot be a keyword such as class, 
# for, return, global, pass, or raise.

# If rename is true, invalid fieldnames are automatically replaced with positional names. For example, ['abc', 'def', 'ghi', 'abc'] is converted to ['abc', '_1', 'ghi', '_3'], 
# eliminating the keyword def and the duplicate fieldname abc.
# defaults can be None or an iterable of default values. Since fields with a default value must come after any fields without a default, 
# the defaults are applied to the rightmost parameters. For example, if the fieldnames are ['x', 'y', 'z'] and the defaults are (1, 2), then x will be a required argument, y will default to 1, and z will default to 2.
# If module is defined, the __module__ attribute of the named tuple is set to that value.


def test_named_tuple():

    # build
    Point = namedtuple('Point', ['x', 'y'], defaults=[0, 0])

    p = Point(11, y=12)

    p1 = Point._make([111, 222])

    p2 = Point(**{'x': 222, 'y':333})

    defaultP = Point()

    print("default point ", defaultP)

    # access
    print("p[0] + p[1] = ", p[0] + p[1])

    x, y = p
    print("x = {}, y = {}".format(x, y))

    print("x = {}, y = {}".format(p.x, p.y))

    print("x = {}, y = {}".format(getattr(p, 'x'), getattr(p, 'y')))

    print(p)

    print(p._asdict())

    # return a new Point
    p1 = p._replace(x=100)
    print(p1)
    print(p)

    # _field_defaults imported by 3.7
    # Dictionary mapping field names to default values.
    # print("_field_defaults : ", p._field_defaults)

    # _fields
    print("_fields : ", p._fields)

    Color = namedtuple('Color', 'red green blue', defaults=[0, 0, 0])
    Pixel = namedtuple('Pixel', Point._fields + Color._fields)
    px = Pixel(10, 10, 128, 128, 128)
    Point3 = namedtuple('Point3', Point._fields + ('z', ), defaults=[100])

    print('color : ', Color())
    print('New pixel is ', px)
    print('Point3 ', Point3(1, 2))

    for p in PixelPoint(3, 4), PixelPoint(5, 5/17):
        print(p)

    # Docstrings can be customized by making direct assignments to the __doc__ fields:
    Book = namedtuple('Book', ['id', 'title', 'authors'])
    Book.__doc__ += ': Hardcover book in active collection'
    Book.id.__doc__ = '13-digit ISBN'
    Book.title.__doc__ = 'Title of first printing'
    Book.authors.__doc__ = 'List of authors sorted by last name'


    # Default values can be implemented by using _replace() to customize a prototype instance:
    Account = namedtuple('Account', 'owner balance transaction_count')
    default_account = Account('<owner name>', 0.0, 0)
    
    johns_account = default_account._replace(owner='John')
    print(johns_account)

    janes_account = default_account._replace(owner='Jane')
    print(janes_account)


# Since a named tuple is a regular Python class, it is easy to add or change functionality with a subclass. 
# Here is how to add a calculated field and a fixed-width print format:
class PixelPoint(namedtuple('Point', ['x', 'y'])):
    
    # The subclass shown above sets __slots__ to an empty tuple. 
    # This helps keep memory requirements low by preventing the creation of instance dictionaries.
    __slots__ = ()
    @property
    def hypot(self):
        return (self.x ** 2 + self.y ** 2) ** 0.5
    
    def __str__(self):
        return 'Point x=%6.3f, y=%6.3f, hypot=%6.3f ' % (self.x, self.y, self.hypot)


def test_named_tuple_():

    EmployeeRecord = namedtuple('EmployeeRecord', 'name, age, title, department, paygrade')

    import csv
    for emp in map(EmployeeRecord._make, csv.reader(open("employees.csv", "rb"))):
        print(emp.name, emp.title)

    import sqlite3
    conn = sqlite3.connect('/companydata')
    cursor = conn.cursor()
    cursor.execute('SELECT name, age, title, department, paygrade FROM employees')
    for emp in map(EmployeeRecord._make, cursor.fetchall()):
        print(emp.name, emp.title)


def main():

    test_named_tuple()

if __name__ == '__main__':

    main()