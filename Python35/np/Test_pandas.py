

import pandas as pd



if __name__=="__main__":

    countries = ['China', 'USA', 'Austras']
    countries_s = pd.Series(countries)
    print(type(countries_s))
    print(countries_s)

    numbers = [4, 5, 6]
    print(pd.Series(numbers))


    country_dicts = {'CH': '??',
                'US': '??',
                'AU': '????'}

    country_dict_s = pd.Series(country_dicts)
    # name the 'index'
    country_dict_s.index.name = 'Code'

    # name the 'data'
    country_dict_s.name = 'Country'

    print(country_dict_s)
    print(country_dict_s.values)
    print(country_dict_s.index)


    pass