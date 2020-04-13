import tkinter as tk
from math import *

def run_calculator():
    def evaluate(event):
        res.configure(text="Result: " + str(eval(entry.get())))

    w = tk.Tk()
    tk.Label(w, text="Your Expression:").pack()
    entry = tk.Entry(w)
    entry.bind("return", evaluate)
    entry.pack()
    res = tk.Label(w)
    res.pack()
    w.mainloop()


if __name__ == '__main__':

    run_calculator()