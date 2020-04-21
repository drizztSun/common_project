

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




    pass




if __name__ == '__main__':

    test_bs4_fetch()