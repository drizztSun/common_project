import time
import datetime # inherit from time

def main():

    print(datetime.datetime.now())

    print(datetime.datetime.ctime(datetime.datetime.now()))

    print(datetime.datetime.now().time())

    print(datetime.datetime.time(datetime.datetime.now()))

    print("Today : ", datetime.datetime.today)

    print("Year: ", datetime.datetime.year, " Month: " , datetime.datetime.month,
            " DAY: ", datetime.datetime.day,  " HH: ", datetime.datetime.hour,
            " MM: ", datetime.datetime.minute, " SS: ", datetime.datetime.second)


if __name__ == "__main__":

    main()
