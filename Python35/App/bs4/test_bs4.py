

from bs4 import BeautifulSoup
import requests
import re


def test_bs4_fetch():

    heads = {
        "Accept" : "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
        "User-Agent:": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 Safari/537.36"
    }

    url = "https://wiki.ubuntu.com/Releases"

    res = requests.get(url, heads)
    text = res.text

    doc_root = BeautifulSoup(res.text, 'lxml')

    version_tables = doc_root.find_all('table')

    headers = ['Version', 'Code name', 'Docs', 'Release', ]

    version_extractor = "\d+\.?"

    for tr in version_tables[1].find_all('tr'):

        tds = tr.find_all('td')

        version = tds[0].find('p').get_text()

        code_name = tds[1].find('p').get_text()

        docs = tds[2].find('p').get_text()

        release_date = tds[3].find('p').get_text()

        end_of_support = tds[4].find('p').get_text()

        end_of_life = tds[5].find('p').get_text()

        version_num = re.findall(version_extractor, version)
        if version_num:
            version_num = ''.join(version_num)

        print(f'{version}, {code_name}, {docs}, {release_date}, {end_of_support}, {end_of_life}, {version_num}')


def test_fetch_ubuntu():

    url = "https://wiki.ubuntu.com/Releases"

    res = requests.get(url)
    text = res.text

    doc_root = BeautifulSoup(res.text, 'lxml')


    version = "18.04"
    re_ver = re.compile(r'^(?P<version>' + version + r'\\.\\d)$')

    tds = doc_root.find_all('td')
    for td in tds:
        m = re.search(re_ver, td.get_text())
        if m:
            print(m.groupdict())




def test_bs4_fetch_macos():

    url = "https://developer.apple.com/news/releases/rss/releases.rss"

    res = requests.get(url)

    doc_root = BeautifulSoup(res.text, 'lxml')

    items = doc_root.find_all('item')

    item = doc_root.find('item')

    pass


def test_bs4_fetch_firefox():

    url = 'http://ftp.mozilla.org/pub/firefox/releases/'

    res = requests.get(url)

    doc_root = BeautifulSoup(res.text, 'lxml')

    items = doc_root.find_all(name='a')

    print(items.__dir__)

    re_text = re.compile(r'^(?P<version>[\d]+[\d\.]*)/$')
    nodes = []

    for n in items:

        res = re.search(re_text, n.get_text())

        if res:
            d = res.groupdict()
            d['node'] = n
            nodes.append(d)

    print(nodes)
    pass


if __name__ == '__main__':

    # test_bs4_fetch()

    test_fetch_ubuntu()

    test_bs4_fetch_firefox()

    # test_bs4_fetch_macos()