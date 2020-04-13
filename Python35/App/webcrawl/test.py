import requests
import time
import random
import hashlib
import json
import tkinter


def send_request(e):
    url = 'http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule'

    header = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 Safari/537.36',
        'Cookie': 'OUTFOX_SEARCH_USER_ID=-1487446322@10.169.0.84; JSESSIONID=aaaKj46uLP4bG_EG1BZfx; OUTFOX_SEARCH_USER_ID_NCOO=588458118.9834455; ___rl__test__cookies=1586779751357',
        'Origin': 'http://fanyi.youdao.com',
        'Referer': 'http://fanyi.youdao.com/'
    }

    def new_data(e):
        r = str(int(time.time() * 1000))
        i = r + str(random.randomint(0, 9))
        md5 = hashlib.md5()
        md5.update("fanyideskweb" + e + i + "Nw(nmmbP%A-r6U3EUnjAj")
        sign = md5.hexdigest()

        bodys = {
            'i': e,
            "from": "zh - CHS",
            "to": "en",
            'smartresult': 'dict',
            'client': 'fanyideskweb',
            'salt': i,
            'sign': sign,
            'ts': r,
            'bv': '6afc34680b90df447b4d9133dfcae8e2',
            'doctype': 'json',
            'version': '2.1',
            'keyfrom': 'fanyi.web',
            'action': 'FY_BY_REALTlME'
        }
        return bodys

    #result = requests.post(url, headers=header, data=new_data('天气')).text

    #obj = josn.load(result)
    #print(obj['translateresult'][0][0]['tgt'])

if __name__ == '__main__':

    window = tkinter.Tk()

    window.title("Translater")

    window.wm_geometry("400x600+800+20")

    res = tkinter.StringVar()

    label_content = tkinter.Label(text="Content", foreground="red", font=("GB2312", 20))
    label_content.grid_configure(cnf={'row':0})

    entry_content = tkinter.Entry(font=('GB2312', 20), textvariable=res)
    entry_content.grid_configure(cnf={'row':0, "column":1})

    entry_content.get

    label_content = tkinter.Label(text="Reuslt", foreground="red", font=("GB2312", 20))
    label_content.grid_configure(cnf={'row':1})

    entry_content = tkinter.Entry(font=('GB2312', 20))
    entry_content.grid_configure(cnf={'row':1, "column":1})

    bnt_res = tkinter.Button(text='Translate', width=10, font=('GN2312', 20), command=send_request)
    bnt_res.grid_configure(cnf={'row':2, "column":0})

    bnt_quit = tkinter.Button(text='Quit', width=10, font=('GN2312', 20), command=quit)
    bnt_quit.grid_configure(cnf={'row':2, "column":1, "sticky":"E"})

    window.mainloop()