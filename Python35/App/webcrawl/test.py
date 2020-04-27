import requests
import time
import hashlib
import json
import tkinter
import re
from lxml import etree
import json
import ffmpeg
import random


def send_request():

    url = 'http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule'

    header = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 Safari/537.36',
        'Cookie': 'OUTFOX_SEARCH_USER_ID=-1487446322@10.169.0.84; JSESSIONID=aaaKj46uLP4bG_EG1BZfx; OUTFOX_SEARCH_USER_ID_NCOO=588458118.9834455; ___rl__test__cookies=1586779751357',
        'Origin': 'http://fanyi.youdao.com',
        'Referer': 'http://fanyi.youdao.com/'
    }

    def new_data(e):
        r = str(int(time.time() * 1000))
        i = r + str(random.randint(0, 9))
        md5 = hashlib.md5()
        md5.update("fanyideskweb" + e.encode(encoding='utf-8') + i + "Nw(nmmbP%A-r6U3EUnjAj")
        sign = md5.hexdigest()

        bodys = {
            'i': e.encode(),
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

    result = requests.post(url, headers=header, data=new_data('天气')).text

    obj = json.loads(result)
    print(obj['translateresult'][0][0]['tgt'])


def test_video_website():

    url = ''
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 Safari/537.36'
    }

    mp4 = requests.get(url, header= headers).content

    with open('text.mp4', sb) as file:
        file.write(mp4)

    res = requests.get(url, header=headers).content.decode()

    print(res)

    dom = etree.HTML(res)

    mv_names = dom.xpath('//h4[@class="video-name one-line"]/a[@href]/text()')
    mv_urls = dom.xpath("//h4[]")

    for mv_name, mv_url in zip(mv_names, mv_urls):
        mv_id = requests.get(mv_url).text

        print(mv_id)

        url = re.search(r'source src"(.*?)"',mv_id).group(1)

        res = requests.get(url).content

        with open('%smv.mp4'%mv_id, 'sb') as file:
            file.save(res)


def random_user_agent():
    import random
    return random.choice(['a', 'b', 'c'])


def test_qidian1():

    url = 'https://read.qidian.com/chapter/ozgK2uJ6kuk1/wgaJM00O4OBMs5iq0oQwLQ2'
    # using different user-agent could cheat website
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.122 Safari/537.36',
        'Referer': 'https://read.qidian.com',
        'Cookie': '_csrfToken=kxWmO3qzZE5SQuFFAyJFDumow6z98UBwPlB0M7is; newstatisticUUID=1587816329_240278882; qdrs=0%7C3%7C0%7C0%7C1; showSectionCommentGuide=1; qdgd=1; lrbc=3144877%7C486663811%7C0; rcr=3144877; e1=%7B%22pid%22%3A%22qd_P_all%22%2C%22eid%22%3A%22qd_B58%22%2C%22l1%22%3A5%7D; e2=%7B%22pid%22%3A%22qd_P_all%22%2C%22eid%22%3A%22%22%2C%22l1%22%3A2%7D'
    }
    #
    r = requests.get(url, headers).text
    print(r)

    html = etree.HTML(r)

    chapter = html.xpath("//div[@class='main-text-wrap]")

    for item in chapter:

        title = item.xpath(".//span[@class='content-wrap']/text()")

        print(title)

        content = item.xpath(".//div[@class='read-content j_readContent']/p/text()")

        print(content)

        with open("./results/%s.txt" % title[0], "w", encoding='utf-8') as f:
            f.save(content)


def test_qidian():

    url = 'https://read.qidian.com/ajax/book/category?_csrfToken=kxWmO3qzZE5SQuFFAyJFDumow6z98UBwPlB0M7is&bookId=1018027097'

    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.122 Safari/537.36',
        'Referer': 'https://read.qidian.com/chapter/fh_KGwlSGICIRkU8pnqrJw2/qugVU95v_IG2uJcMpdsVgA2',
        'Accept-Language': 'en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7',
        'Accept': 'application/json, text/javascript, */*; q=0.01',
        'Cookie': '_csrfToken=kxWmO3qzZE5SQuFFAyJFDumow6z98UBwPlB0M7is; newstatisticUUID=1587816329_240278882; qdrs=0%7C3%7C0%7C0%7C1; showSectionCommentGuide=1; qdgd=1; lrbc=3144877%7C486663811%7C0; rcr=3144877; e1=%7B%22pid%22%3A%22qd_P_all%22%2C%22eid%22%3A%22qd_B58%22%2C%22l1%22%3A5%7D; e2=%7B%22pid%22%3A%22qd_P_all%22%2C%22eid%22%3A%22%22%2C%22l1%22%3A2%7D'
    }

    base_url = 'https://read.qidian.com/chapter/'
    response_text = requests.get(url, headers).content.decode()
    content = json.loads(response_text)

    for item in content['data']['vs'][2]['cs']:

        html = etree.HTML(requests.get(base_url + item['cU']).content.decode())
        content = html.xpath('//div[@class="read-content j_readContent"]/p/text()')

        with open('./res/%s.txt' % item['cN'], 'w', encoding='utf-8') as f:
            for c in content:
                f.write(c)

    print("Finish the web crawling on the page qidian")


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

    test_video_website()

    # send_request()

