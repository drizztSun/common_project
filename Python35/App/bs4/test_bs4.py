from bs4 import BeautifulSoup
import requests
import re
import datetime
import dateutil
import urllib.parse


def get_version(x):
    """

    :param x: version string, such as 1.1.1
    :return: tuple of integer
    """

    if isinstance(x, str):
        s = []
        for a in x.split('.'):
            a = a.strip()
            if a:
                try:
                    s.append(int(a))
                except ValueError:
                    s.append(a)

        # remove all trailing zeros
        if isinstance(s, list):
            while s and not s[-1]:
                s.pop(-1)

        return tuple(s)

    return x


def test_bs4_fetch_ubuntu():

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


def test_bs4_fetch_macos():

    url = "https://developer.apple.com/news/releases/rss/releases.rss"
    version_re =  r'^10.12'
    build_re = r'^16[A-Z]'
    date_re = r'[a-zA-Z]+\s+\d{1,2}\s*,\s*\d{4}'

    res = requests.get(url)
    res.raise_for_status()

    root = BeautifulSoup(res.text, 'lxml')
    versions = []

    for n in root.find_all('table'):
        version = n.find('th', string=re.compile(r'Version'))
        build = n.find(['th', 'span'], string=re.compile(r'Build'))
        tbody = n.find('tbody')
        if version and build and tbody:
            version, build, date = None, None, None
            for tr in tbody.find_all('tr'):
                if version and build:
                    versions.append((version, build, date))

                version_th = tr.find('th', string=re.compile(version_re))
                if version_th:
                    version = version_th.get_text().strip()

                build_th = tr.find('td', string=re.compile(build_re))
                if build_th:
                    build = build_th.get_text().strip()

                for td in tr.find_all('td'):
                    m = re.match(date_re, td.get_text())
                    if m:
                        date = str(datetime.datetime.strptime(m.group(0).strip(), '%B %d, %Y').date())

    print(',\n'.join(str(v) for v in versions))


def test_bs4_fetch_firefox():

    url = 'https://ftp.mozilla.org/pub/firefox/releases/'
    res = requests.get(url)
    res.raise_for_status()

    root = BeautifulSoup(res.text, 'lxml')
    versions = []

    age = datetime.date() - datetime.timedelta(days=365*2)

    url_parsed = urllib.parse.urlparse(url)

    for n in root.find_all('a', string=re.compile(r'^([0-9]+[0-9.]+)/')):

        version = re.match(r'^([0-9]+[0-9.]+)/', n.get_text().strip()).group(1)

        url = '%s://%s/%s' % (url_parsed.scheme, url_parsed.netloc, n.get('href'))

        res = requests.get(url)
        res.raise_for_status()

        node = BeautifulSoup(res.text, 'lxml')

        date_td = node.find('td', string=re.compile(r'\d{1,2}-[a-zA-Z]*-\d{4} \d+:\d+$'))
        if date_td:
            date = datetime.datetime.strptime(date_td.get_text().strip(), '%d-%b-%Y %H:%M').date()
            if date > age:
                if 'win' in node.get_text():
                    versions.append(('windows', version, date.isoformat()))
                    print('windows', version, date)

                if 'mac' in node.get_text():
                    versions.append(('darwin', version, date.isoformat()))
                    print('mac', version, date)

    versions.sort(key=lambda x: get_version(x[1]))
    print(',\n'.join(str(v) for v in versions))


def test_bs4_fetch_windows():

    version, build = 1903, 18362

    res = requests.get('https://winreleaseinfoprod.blob.core.windows.net/winreleaseinfoprod/en-US.html')
    res.raise_for_status()

    doc_root = BeautifulSoup(res.text, 'lxml')

    build_re = re.compile(r'^%d.\d+' % build)
    versions = []

    for table in doc_root.find_all('table'):

        build = table.find('td', string=re.compile(build_re))

        if build and not table.find('td', string=re.compile(version)):

            for tr in table.find_all('tr'):

                build_th = tr.find('td', string=re.compile(build_re))

                if build_th:

                    build = build_th.get_text().strip()

                    date_th = tr.find('td', string=re.compile(r'^\d{4}-\d{2}-\d{2}'))

                    if date_th:
                        date = str(datetime.datetime.strptime(date_th.get_text().strip(), '%Y-%m-%d').date())
                        versions.append((version, build, date))

    print(',\n'.join(str(v) for v in versions))


def test_bs4_fetch_chrome(self, *args, **options):

    url = 'https://chromereleases.googleblog.com/{year}/{month:02d}/stable-channel-update-for-desktop.html' # 'https://chromereleases.googleblog.com'

    today = datetime.date.today().replace(day=1)
    start = today - datetime.timedelta(days=365*2)

    versions = []
    while start <= today:

        url = url.format(year=start.year, month=start.month)
        start += dateutil.relativedelta.relativedelta(months=1)

        res = requests.get(url)
        res.raise_for_status()

        root = BeautifulSoup(res.text, 'lxml')

        for post in root.find_all('div', class_='post'):
            date = post.find('span', class_='publishdate').get_text().strip()
            if date:
                date = str(datetime.datetime.strptime(date, '%A, %B %d, %Y').date())
                body = post.find('div', class_='post-body')
                if body:
                    for span in body.find_all('span'):
                        m = re.search(r'Chrome\s+([0-9]+[0-9.]+)\s+', span.get_text())
                        if m:
                            version = m.group(1)
                            versions.append(('windows', version, date))
                            versions.append(('darwin', version, date))
                            # print(version, date)

    versions.sort(key=lambda x: get_version(x[1]))
    print(',\n'.join(str(v) for v in versions))


def test_bs4_fetch_ubuntu_new():

    url = 'https://wiki.ubuntu.com/Releases'
    ret = {}

    resp = requests.get(url)
    resp.raise_for_status()

    root_doc = BeautifulSoup(resp.text, 'lxml')

    version = "18.04"

    re_exp = r'(?P<version>' + version + r'\.\d)'
    text = re.compile(re_exp)

    all_tds = root_doc.find_all(name='td')

    for c in all_tds:

        m = re.search(text, c.get_text())
        if m and m.groupdict():
            ret.update(m.groupdict())
            node = c
            break

    node = node.parent

    n = node.find(name='a', class_='https')

    re_exp = re.compile(r'(?P<month>[A-Za-z]+)\s+(?P<day>\d{1,2}), (?P<year>\d{4})')
    m = re.search(re_exp, n.get_text())
    ret.update(m.groupdict())

    print(ret)





if __name__ == '__main__':

    test_bs4_fetch_ubuntu_new()

    test_bs4_fetch_ubuntu()

    test_bs4_fetch_firefox()

    # test_bs4_fetch_macos()