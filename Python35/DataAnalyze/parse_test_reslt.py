import os
import time
import datetime
import sys
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
            try:
                i = line.find('--PerformanceTesting--:')
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
            except:
                continue

    return data_result


def show_result_graph(data_result):

    x_data_st = []
    y_data_total = []
    y_data_avg = []
    y_cnt = []

    for t in data_result:

        st = t[0]
        x = '%s-%d-%d' % (st.date(), st.hour, st.minute)

        if not x_data_st or x_data_st[-1] != x:
            x_data_st.append(x)
            y_data_total.append(t[2])
            y_data_avg.append(t[3])
            y_cnt.append(1)
        else:
            y_data_total[-1] += t[2]
            y_data_avg[-1] = (y_data_avg[-1] * y_cnt[-1] + t[3]) / (y_cnt[-1] + 1)
            y_cnt[-1] += 1


    # y_data_avg = list(map(lambda x: x * 100, y_data_avg))
    #plt.bar(x=x_data_st, height=y_cnt, label='100times', color='steelblue', alpha=0.8)
    plt.bar(x=x_data_st, height=y_data_avg, label='avg-per-validation', color='indianred', alpha=0.8)

    #for x, y in enumerate(y_cnt):
    #    plt.text(x, y + 100, '%s' % y, ha='center', va='bottom')

    for x, y in enumerate(y_data_avg):
        plt.text(x, y + 100, '{:.4f}'.format(y), ha='center', va='bottom')

    plt.title('avg and total of token validation spent')
    plt.xlabel('time')
    plt.ylabel('seconds')
    
    plt.legend()
    plt.xticks(range(len(x_data_st)), x_data_st)
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
        plt.text(x, y , '%s' % y, ha='center', va='bottom')
    for x, y in enumerate(y_data2):
        plt.text(x, y , '%s' % y, ha='center', va='top')
    
    # title
    plt.title("Java and  android book")
    
    # name of x-axis, y-axis
    plt.xlabel("year")
    plt.ylabel("amount")

    try: 
        # show graph
        plt.legend()
        plt.xticks(range(len(x_data)), x_data)
        plt.show()
    except Exception:
        sys.exc_clear()


if __name__ == '__main__':

    # show()

    data_result = filter_test_result('./DataAnalyze/dps.log')

    show_result_graph(data_result)