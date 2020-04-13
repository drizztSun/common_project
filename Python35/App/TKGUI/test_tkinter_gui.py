import tkinter as tk



def test_tkinter_gui_basic():

    def show_entry_fields():
        print("First name: %s\n Last name: %s" % (e1.get(), e2.get())) # get entry content
        e1.delete(0, tk.END) # delete entry content
        e2.delete(0, tk.END)

    master = tk.Tk()

    tk.Label(master, text='First Name').grid(row=0)
    tk.Label(master, text='Last Name').grid(row=1)

    e1 = tk.Entry(master)
    e2 = tk.Entry(master)
    e1.insert(10, "Miller") # insert content to entry
    e2.insert(10, "Jill")

    e1.grid(row=0, column=1)
    e2.grid(row=1, column=1)

    tk.Button(master, text='Quit', command=master.quit).grid(
        row=3, column=0, sticky=tk.W, pady=4)
    tk.Button(master, text='Show', command=show_entry_fields).grid(
        row=3, column=1, sticky=tk.W, pady=4)

    master.mainloop()


def test_tkinter_gui_more():
    fields = 'Last Name', 'First Name', 'Job', 'Country'

    def fetch(entries):
        for entry in entries:
            field = entry[0]
            text = entry[1].get()
            print('%s: "%s"' % (field, text))

    def makeform(root, fields):
        entries = []
        for field in fields:
            row = tk.Frame(root)
            lab = tk.Label(row, width=15, text=field, anchor='w')
            ent = tk.Entry(row)
            row.pack(side=tk.TOP, fill=tk.X, padx=5, pady=5)
            lab.pack(side=tk.LEFT)
            ent.pack(side=tk.RIGHT, expand=tk.YES, fill=tk.X)
            entries.append((field, ent))
        return entries

    root = tk.Tk()
    ents = makeform(root, fields)
    root.bind("<Return>", (lambda event, e=ents: fetch(e)))
    b1 = tk.Button(root, text='Show', command=lambda e=ents: fetch(e))
    b1.pack(side=tk.LEFT, padx=5, pady=5)
    b2 = tk.Button(root, text='Quit', command=root.quit)
    b2.pack(side=tk.LEFT, padx=5, pady=5)
    root.mainloop()




if __name__ == '__main__':

    test_tkinter_gui_basic()

    test_tkinter_gui_more()