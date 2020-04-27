import requests
import hashlib
import random
import time
import json
import tkinter


def send_request():

    url = 'http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule'

    header = {
        'Host': 'fanyi.youdao.com',
        'Connection': 'keep-alive',
        'Content-Length': '255',
        'Pragma': 'no-cache',
        'Cache-Control': 'no-cache',
        'Accept': 'application/json, text/javascript, */*; q=0.01',
        'X-Requested-With': 'XMLHttpRequest',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.122 Safari/537.36',
        'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
        'Origin': 'http://fanyi.youdao.com',
        'Referer': 'http://fanyi.youdao.com/',
        'Accept-Encoding': 'gzip, deflate',
        'Accept-Language': 'en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7',
        'Cookie': 'OUTFOX_SEARCH_USER_ID=-1487446322@10.169.0.84; OUTFOX_SEARCH_USER_ID_NCOO=588458118.9834455; JSESSIONID=aaaThyuAXYjwR7bbZQ7gx; ___rl__test__cookies=1587993104561'
    }

    def new_data(e):
        r = str(int(time.time() * 1000))
        i = r + str(random.randint(0, 9))
        md5 = hashlib.md5()
        str_sign = "fanyideskweb" + e + i + "Nw(nmmbP%A-r6U3EUn]Aj"
        md5.update(str_sign.encode())
        sign = md5.hexdigest()

        body = {
            'i': e,
            "from": "zh - CHS",
            "to": "en",
            'smartresult': 'dict',
            'client': 'fanyideskweb',

            'salt': i,
            'sign': sign,
            'ts': r,
            'bv': '629f80a540369a25a9a1f106dcb432ac',

            'doctype': 'json',
            'version': '2.1',
            'keyfrom': 'fanyi.web',
            'action': 'FY_BY_REALTlME'
        }

        return body

    result = requests.post(url, headers=header, data=new_data('天气')).text

    obj = json.loads(result)

    print(obj['translateResult'][0][0]['tgt'])


def test_ui():

    window = tkinter.Tk()

    window.title("Translater")

    window.wm_geometry("400x600+800+20")

    res = tkinter.StringVar()

    label_content = tkinter.Label(text="Content", foreground="red", font=("GB2312", 20))
    label_content.grid_configure(cnf={'row':0})

    entry_content = tkinter.Entry(font=('GB2312', 20), textvariable=res)
    entry_content.grid_configure(cnf={'row':0, "column":1})

    # entry_content.get

    label_content = tkinter.Label(text="Reuslt", foreground="red", font=("GB2312", 20))
    label_content.grid_configure(cnf={'row':1})

    entry_content = tkinter.Entry(font=('GB2312', 20))
    entry_content.grid_configure(cnf={'row':1, "column":1})

    bnt_res = tkinter.Button(text='Translate', width=10, font=('GN2312', 20), command=send_request)
    bnt_res.grid_configure(cnf={'row':2, "column":0})

    bnt_quit = tkinter.Button(text='Quit', width=10, font=('GN2312', 20), command=quit)
    bnt_quit.grid_configure(cnf={'row':2, "column":1, "sticky":"E"})

    window.mainloop()


if __name__ == '__main__':

    send_request()