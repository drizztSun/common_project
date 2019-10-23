import os
import time
import datetime

import numpy as np
import matplotlib.pyplot as plt

# Verify matplotlib code
# import matplotlib.pyplot as plt
# plt.stackplot(range(4), [2, 2, 2, 2], [1, 2, 3, 4], labels=['a', 'b'])
# plt.show()

def filter_test_result(test_file):

    data_result = []

    with open(test_file, 'r') as fh:
        for line in fh:
            i = line.index('--PerformanceTesting--:')
            if i == -1:
                continue
        
            data = line[i + len('--PerformanceTesting--:'):]
            times = data.split(',')
            if len(times) != 4:
                continue
            
            # start time
            st_datetm = datetime.datetime.fromtimestamp( float(times[0].strip()[3:]))
            # st_datetm = float(times[0].strip()[len('st')+1:])

            # end time
            # st_endtime = datetime.datetime.fromtimestamp( float(times[1].strip()[3:]) / 1e3)
            st_endtime = float(times[1].strip()[len('en')+1:])

            # during
            st_during = float(times[2].strip()[len('during') + 1:])

            # avg
            st_avg = float(times[3].strip()[len('avg') + 1:])

            data_result.append((st_datetm, st_endtime, st_during, st_avg))

    return data_result


def show_result_graph(data_result):
    
    # x_data = [t[0] for t in data_result]
    x_data = []
    y_data1 = []
    y_data2 = []
    y_cnt = []

    for t in data_result:

        st = t[0]
        x = '%s-%d-%d' % (st.date(), st.hour, st.minute)

        if not x_data or x_data[-1] != x:
            x_data.append(x)
            y_data1.append(t[2])
            y_data2.append(t[3])
            y_cnt.append(1)
        else:
            y_data1[-1] += t[2]
            y_cnt[-1] += 1
            y_data2[-1] = y_data1[-1] / y_cnt[-1]


    plt.bar(x=x_data, height=y_data1, label='100times', color='steelblue', alpha=0.8)
    plt.bar(x=x_data, height=y_data2, label='avg-per-validation', color='indianred', alpha=0.8)

    for x, y in enumerate(y_data1):
        plt.text(x, y + 100, '%s' % y, ha='center', va='bottom')

    for x, y in enumerate(y_data2):
        plt.text(x, y + 100, '%s' % y, ha='center', va='bottom')

    plt.title('avg and total of token validation spent')
    plt.xlabel('time')
    plt.ylabel('millisecond')
    plt.xticks(range(len(x_data)), x_data)

    plt.legend()
    plt.show()

def show() :

    # data
    x_data = ['2012', '2013', '2014', '2015', '2016', '2017', '2018']
    y_data = [58000, 60200, 63000, 71000, 84000, 90500, 107000]
    y_data2 = [52000, 54200, 51500,58300, 56800, 59500, 62700]
   
    # draw
    plt.bar(x=x_data, height=y_data, label='C language ', color='steelblue', alpha=0.8)
    plt.bar(x=x_data, height=y_data2, label='Java language', color='indianred', alpha=0.8)
   
    # show data, v-align h-align
    for x, y in enumerate(y_data):
        plt.text(x, y + 100, '%s' % y, ha='center', va='bottom')
    for x, y in enumerate(y_data2):
        plt.text(x, y + 100, '%s' % y, ha='center', va='top')
    
    # title
    plt.title("Java and  android book")
    
    # name of x-axis, y-axis
    plt.xlabel("year")
    plt.ylabel("amount")

    # show graph
    plt.legend()
    plt.xticks(range(len(x_data)), x_data)
    plt.show()



if __name__ == '__main__':

    # show()

    data_result = filter_test_result('./DataAnalyze/dps_test_res.txt')

    show_result_graph(data_result)