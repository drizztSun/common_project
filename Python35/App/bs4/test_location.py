

import re
import calendar
import logging
import datetime
import json

import urllib.parse
import urllib.robotparser
from bs4 import BeautifulSoup
import requests


class Command:
    """
    Django CLI with manage.py
    """

    help = 'DPS Latest Version Crawler'
    USER_AGENT = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36' #'AkamaiZeroTrustBot/1.0'

    def locate(self, locator, cache=None):
        """

        :param locator:
        :param cache:
        :return:
        """

        node, root = None, None
        ret = {}
        for loc in locator:
            if 'url' in loc:
                url = loc['url']
                if 'link' in ret and '{{ link }}' in url:
                    url = url.replace('{{ link }}', ret['link'])

                if 'version' in ret and '{{ version }}' in url:
                    url = url.replace('{{ version }}', ret['version'])

                ret['link'] = url

                if cache and url in cache:
                    node = root = cache[url]
                    continue
                
                url_parsed = urllib.parse.urlparse(url)
                robots_url = '%s://%s/robots.txt' % (url_parsed.scheme, url_parsed.netloc)


                #rp = urllib.robotparser.RobotFileParser()
                #rp.set_url(robots_url)
                #rp.set_url('https://chromereleases.googleblog.com/robots.txt')
                #rp.read()

                #if not rp.can_fetch(self.USER_AGENT, url):
                #if 'link' in ret and ret['link'] == url:
                #    ret.pop('link')
                # logger.error('%s: no robots allowed for %s', url, self.USER_AGENT)
                #continue

                res = requests.get(url, headers={'User-Agent': self.USER_AGENT})
                res.raise_for_status()

                node = root = BeautifulSoup(res.text, 'lxml')
                if cache is not None:
                    cache[url] = node

                continue

            method = loc['method']
            if method == 'return':
                if 'version' in ret and ('date' in ret or ('day' in ret and 'month' in ret and 'year' in ret)):
                    break

            if not node:
                continue

            args, kwargs = loc.get('args', []), loc.get('kwargs', {})
            if method == 'find_parent':
                node = node.find_parent(*args, **kwargs)
            elif method == 'find':
                if 're' in loc:
                    if 'version' in ret and '{{ version }}' in loc['re']:
                        loc['re'] = loc['re'].replace('{{ version }}', ret['version'])

                    if 'build' in ret and '{{ build }}' in loc['re']:
                        loc['re'] = loc['re'].replace('{{ build }}', ret['build'])

                    text = re.compile(loc['re'])
                    for n in node.find_all(*args, **kwargs):
                        m = re.search(text, n.get_text())
                        if m:
                            node = n
                            if m.groupdict():
                                ret.update(m.groupdict())
                            break

                else:
                    if 'text' in kwargs and 'version' in ret and '{{ version }}' in kwargs['text']:
                        kwargs['text'] = kwargs['text'].replace('{{ version }}', ret['version'])

                    if 'text' in kwargs and 'build' in ret and '{{ build }}' in kwargs['text']:
                        kwargs['text'] = kwargs['text'].replace('{{ build }}', ret['build'])

                    # print(node)
                    node = node.find(*args, **kwargs)
                    # print('******************------ find ---- %s' % node.text)



            elif method == 'find_all':
                if 're' in loc:
                    if 'version' in ret and '{{ version }}' in loc['re']:
                        loc['re'] = loc['re'].replace('{{ version }}', ret['version'])

                    text = re.compile(loc['re'])
                    nodes = []
                    for n in node.find_all(*args, **kwargs):
                        m = re.search(text, n.get_text())
                        if m:
                            d = m.groupdict()
                            d['node'] = n
                            nodes.append(d)

                    node = nodes
                else:
                    if 'text' in kwargs and 'version' in ret and '{{ version }}' in kwargs['text']:
                        kwargs['text'] = kwargs['text'].replace('{{ version }}', ret['version'])

                    node = node.find_all(*args, **kwargs)


            elif method == 'max_version':
                versions = sorted(node, key=lambda x: tuple(map(int, x.get('version').split('.'))))
                next_node = versions[loc.get('slice', -1)]
                node = next_node.pop('node')
                href = node.get('href')
                if href:
                    if href.startswith('http'):
                        ret['link'] = node['href']
                    else:
                        ret['link'] = urllib.parse.urljoin(ret['link'], href)

                ret.update(next_node)
            elif method == 'root':
                node = root
            elif method == 'store':
                if node:
                    href = node.get('href')
                    if href:
                        if href.startswith('http'):
                            ret['link'] = node['href']
                        else:
                            ret['link'] = urllib.parse.urljoin(ret['link'], href)
            elif 'parent' in method:
                for _ in method.split('.'):
                    node = node.parent

                # print('---- parent -- %s\n%s\n\n', method, node)
                #logger.debug('---- parent -- %s\n%s\n\n', method, node)

            elif 'next_sibling' in method:
                for _ in method.split('.'):
                    node = node.find_next_sibling(loc.get('name', node.name))

                # print('---- next sibling node: %s' % node.text)
                #logger.debug('---- next sibling --- %s\n%s\n\n', method, node)

            elif method == 'split':
                sep = kwargs.get('sep', '\n')
                node = node.get_text().strip().split(sep)
            elif method == 'join':
                sep = kwargs.get('sep', ',')
                if 'indexes' in kwargs:
                    s = []
                    for i in kwargs['indexes']:
                        s.append(node[i])
                    node = sep.join(s)
                else:
                    node = sep.join(node)
            elif method in ['re.match', 're.search']:
                if isinstance(node, str):
                    text = node
                else:
                    text = node.get_text()

                regexp = loc['re']
                if 'version' in ret and '{{ version }}' in regexp:
                    regexp = regexp.replace('{{ version }}', ret['version'])

                if method == 're.match':
                    m = re.match(regexp, text, re.IGNORECASE | re.DOTALL)
                else:
                    m = re.search(regexp, text, re.MULTILINE | re.DOTALL | re.IGNORECASE)



                if m:
                    ret.update({k: v.strip() for k, v in m.groupdict().items()})
                    if 'version' in ret and ret['version'].endswith('.'):
                        ret['version'] = ret['version'][0:-1]

        if 'month' in ret and 'year' in ret:
            if 'day' not in ret:
                ret['day'] = '1'

            month = ret['month']
            for i, m in enumerate(calendar.month_abbr):
                if m == month:
                    ret['month'] = '%02d' % i
                    break

            for i, m in enumerate(calendar.month_name):
                if m == month:
                    ret['month'] = '%02d' % i
                    break

            ret['date'] = datetime.datetime.strptime('%s-%s-%s' % (ret.pop('year'),
                                                                   ret.pop('month'),
                                                                   ret.pop('day')),
                                                     '%Y-%m-%d').date()
        elif 'date' in ret:
            ret['date'] = datetime.datetime.strptime('%s' % ret['date'], '%Y-%m-%d').date()

        return ret


def test_crawl():


    osversion = '12'

    loc = [
        [
            {'url': 'http://ftp.mozilla.org/pub/firefox/releases/'},
            {'method': 'find_all', 're': r'^(?P<version>[\d]+[\d\.]*)/$', 'kwargs': {'name': 'a'}},
            {'method': 'max_version'},
            {'url': '{{ link }}'},
            {'method': 're.search', 're': r'^(?P<day>[\d]{1,2})-(?P<month>[a-zA-Z]+)-(?P<year>\d\d\d\d)'}
        ],
        [
            # {'url': 'https://chromereleases.googleblog.com/search/label/Stable%20updates'},
            {'url': 'https://chromereleases.googleblog.com'},
            {'method': 'find', 're': r'Stable Channel Update for Desktop', 'kwargs': {'name': 'a'}},
            {'method': 'store'},
            {'method': 'find_parent', 'kwargs': {'name': 'div', 'class_': 'post'}},
            {'method': 'find', 'kwargs': {'name': 'span', 'class_': 'publishdate'}},
            {'method': 're.search', 're': r'[A-Za-z]+, (?P<month>[A-Za-z]+)\s+(?P<day>\d{1,2}), (?P<year>\d{4})'},
            {'method': 'find_parent', 'kwargs': {'name': 'div', 'class_': 'post'}},
            {'method': 'find', 'kwargs': {'name': 'div', 'class_': 'post-body'}},
            {'method': 're.search', 're': r'(?P<version>[0-9]+.[0-9]+.[0-9]+.[0-9]+)'}
        ],
        [
            {'url': 'https://developer.apple.com/news/releases/rss/releases.rss'},
            {'method': 'find', 're': r'^\s*iOS (?P<version>' + '13' + r'.[\d\.]+)\s+\((?P<build>.+)\)\s*$', 'kwargs': {'name': 'title'}},
            {'method': 'parent'},
            {'method': 'find', 're': r'(?P<day>\d{1,2})\s+(?P<month>[A-Za-z]+)\s+(?P<year>\d{4})', 'kwargs': {'name': 'pubdate'}},
        ],
        [
            {'url': 'https://en.wikipedia.org/wiki/Microsoft_Edge'},
            {'method': 'find', 'kwargs': {'name': 'a', 'text': 'Stable release(s)'}},
            {'method': 'find_parent', 'kwargs': {'name': 'tbody'}},
            {'method': 'find', 'kwargs': {'name': 'th', 'text': 'Windows'}},
            {'method': 'parent'},
            {'method': 'find', 'kwargs': {'name': 'td'}},
            {'method': 're.search', 're': r'(?P<version>[0-9\.]+)'},
            {'method': 're.search', 're': r'(?P<date>\d\d\d\d-\d+-\d+)'}
        ]
    ]


    for c in loc:
        ret = Command().locate(c)
        print(ret)

    print("res")


def test_robotic(url):
    USER_AGENT = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36'

    url_parsed = urllib.parse.urlparse(url)
    robots_url = '%s://%s/robots.txt' % (url_parsed.scheme, url_parsed.netloc)

    rp = urllib.robotparser.RobotFileParser()
    rp.set_url(robots_url)
    # rp.set_url('https://chromereleases.googleblog.com/robots.txt')
    rp.read()

    if not rp.can_fetch(USER_AGENT, url):
        print('%s: no robots %s allowed for %s', url, robots_url, USER_AGENT)


if __name__ == '__main__':

    test_crawl()

    #test_robotic('http://ftp.mozilla.org/pub/firefox/releases/')

    #test_robotic('https://chromereleases.googleblog.com/search/label/Stable%20updates')





