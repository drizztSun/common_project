import requests
import bs4
import json
from lxml import etree



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


