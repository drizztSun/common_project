"""
    # stream protocol

    # Apple(hls)  Adobe(rtmp)

    # ffmpeg vlc

    # cut video in MPEG-TS and m3u8(record list of TS files)
    # use 'm3u8' file find all .ts files, download and link them at local
    # cat *.ts ? hecheng.mp4
    # ffmpeg -i '{url - m3u8}' -vcodec copy -acodec copy 'xxxxx.mkv'

    # typocal m3u8 file
    (1)
    # #EXTM3U
    # #EXT-X-VERSION:3
    # #EXT-X-MEDIA-SEQUENCE:0
    # #EXT-X-TARGETDURATION:12
    # #EXT-X-PLAYLIST-TYPE:VOD
    # #EXTINF:9.480,
    # 00_q02065e81vt.321002.1.ts?index=0&start=0&end=9480&brs=0&bre=921763&ver=4
    # #EXTINF:5.581,
    # 01_q02065e81vt.321002.1.ts?index=1&start=9480&end=15061&brs=921764&bre=1214667&ver=4
    # #EXT-X-ENDLIST

    (2)
    # #EXTM3U
    # #EXT-X-VERSION:6
    # #EXT-X-TARGETDURATION:12
    # #EXT-X-PLAYLIST-TYPE:VOD
    # #EXT-X-MAP:URI="00_u00315w81xn.321012.1.mp4?index=0&start=0&end=0&brs=0&bre=1145&ver=5&sig=0100804015"
    # #EXT-X-KEY:METHOD=SAMPLE-AES-CTR,URI="data:text/plain;base64,AAAANnBzc2gAAAAA7e+LqXnWSs6jyCfc1R0h7QAAABYaB3RlbmNlbnQiC3UwMDMxNXc4MXhu",KEYID=0x5B57E4F775D84DD9EB1409BF74C7DC42,KEYFORMATVERSIONS="1",KEYFORMAT="urn:uuid:edef8ba9-79d6-4ace-a3c8-27dcd51d21ed"
    # #EXTINF:6.00000,
    # 01_u00315w81xn.321012.1.mp4?index=1&start=0&end=6000&brs=22070&bre=227825&ver=5
    # #EXTINF:8.12000,
    # 02_u00315w81xn.321012.1.mp4?index=2&start=6000&end=14120&brs=227826&bre=320984&ver=5
    # #EXTINF:6.00000,
    # 03_u00315w81xn.321012.1.mp4?index=3&start=14120&end=20120&brs=320985&bre=731839&ver=5
    # #EXTINF:9.52000,
    # 04_u00315w81xn.321012.1.mp4?index=4&start=20120&end=29640&brs=731840&bre=1488374&ver=5
    # #EXTINF:0.36000,
    # 05_u00315w81xn.321012.1.mp4?index=5&start=29640&end=30000&brs=1488375&bre=1531252&ver=5
    # #EXTINF:10.44000,
    # 06_u00315w81xn.321012.1.mp4?index=6&start=30000&end=40440&brs=1531253&bre=2127876&ver=5
    # #EXTINF:6.60000,
    # 07_u00315w81xn.321012.1.mp4?index=7&start=40440&end=47040&brs=2127877&bre=2889339&ver=5
    # #EXTINF:3.72000,
    # 08_u00315w81xn.321012.1.mp4?index=8&start=47040&end=50760&brs=2889340&bre=3133532&ver=5
    # #EXTINF:4.60000,
    # 09_u00315w81xn.321012.1.mp4?index=9&start=50760&end=55360&brs=3133533&bre=3384959&ver=5
    # #EXTINF:4.64000,
    # 010_u00315w81xn.321012.1.mp4?index=10&start=55360&end=60000&brs=3384960&bre=3817024&ver=5
    # #EXTINF:6.16000,
    # 011_u00315w81xn.321012.1.mp4?index=11&start=60000&end=66160&brs=3817025&bre=4365138&ver=5
    # #EXTINF:6.00000,
    # 012_u00315w81xn.321012.1.mp4?index=12&start=66160&end=72160&brs=4365139&bre=4707047&ver=5
    # #EXTINF:6.00000,
    # 013_u00315w81xn.321012.1.mp4?index=13&start=72160&end=78160&brs=4707048&bre=5049755&ver=5
    # #EXTINF:6.00000,
    # 014_u00315w81xn.321012.1.mp4?index=14&start=78160&end=84160&brs=5049756&bre=5756907&ver=5
    # #EXTINF:5.84000,
    # 015_u00315w81xn.321012.1.mp4?index=15&start=84160&end=90000&brs=5756908&bre=6179893&ver=5
    # #EXTINF:8.00000,
    # 016_u00315w81xn.321012.1.mp4?index=16&start=90000&end=98000&brs=6179894&bre=6730522&ver=5
    # #EXTINF:6.00000,
    # 017_u00315w81xn.321012.1.mp4?index=17&start=98000&end=104000&brs=6730523&bre=7276413&ver=5
    # #EXTINF:6.00000,
    # 018_u00315w81xn.321012.1.mp4?index=18&start=104000&end=110000&brs=7276414&bre=8116912&ver=5
    # #EXTINF:4.32000,
    # 019_u00315w81xn.321012.1.mp4?index=19&start=110000&end=114320&brs=8116913&bre=8480986&ver=5
    # #EXTINF:5.68000,
    # 020_u00315w81xn.321012.1.mp4?index=20&start=114320&end=120000&brs=8480987&bre=9224842&ver=5
    # #EXTINF:6.00000,
    # 021_u00315w81xn.321012.1.mp4?index=21&start=120000&end=126000&brs=9224843&bre=10925065&ver=5
    # #EXTINF:6.00000,
    # 022_u00315w81xn.321012.1.mp4?index=22&start=126000&end=132000&brs=10925066&bre=12004973&ver=5
    # #EXTINF:11.96000,
    # 023_u00315w81xn.321012.1.mp4?index=23&start=132000&end=143960&brs=12004974&bre=13971001&ver=5
    # #EXTINF:6.00000,
    # 024_u00315w81xn.321012.1.mp4?index=24&start=143960&end=149960&brs=13971002&bre=14053061&ver=5
    # #EXTINF:0.04000,
    # 025_u00315w81xn.321012.1.mp4?index=25&start=149960&end=150000&brs=14053062&bre=14055747&ver=5
    # #EXTINF:7.52000,
    # 026_u00315w81xn.321012.1.mp4?index=26&start=150000&end=157520&brs=14055748&bre=14375728&ver=5
    # #EXTINF:7.32000,
    # 027_u00315w81xn.321012.1.mp4?index=27&start=157520&end=164840&brs=14375729&bre=14677932&ver=5
    # #EXTINF:4.08000,
    # 028_u00315w81xn.321012.1.mp4?index=28&start=164840&end=168920&brs=14677933&bre=14840191&ver=5
    # #EXTINF:8.24000,
    # 029_u00315w81xn.321012.1.mp4?index=29&start=168920&end=177160&brs=14840192&bre=15249419&ver=5
    # #EXTINF:2.84000,
    # 030_u00315w81xn.321012.1.mp4?index=30&start=177160&end=180000&brs=15249420&bre=15373688&ver=5
    # #EXTINF:6.00000,
    # 031_u00315w81xn.321012.1.mp4?index=31&start=180000&end=186000&brs=15373689&bre=15686606&ver=5
    # #EXTINF:11.20000,
    # 032_u00315w81xn.321012.1.mp4?index=32&start=186000&end=197200&brs=15686607&bre=15922525&ver=5
    # #EXTINF:6.00000,
    # 033_u00315w81xn.321012.1.mp4?index=33&start=197200&end=203200&brs=15922526&bre=16105890&ver=5
    # #EXTINF:5.80000,
    # 034_u00315w81xn.321012.1.mp4?index=34&start=203200&end=209000&brs=16105891&bre=16256395&ver=5
    # #EXTINF:1.00000,
    # 035_u00315w81xn.321012.1.mp4?index=35&start=209000&end=210000&brs=16256396&bre=16324880&ver=5
    # #EXTINF:6.00000,
    # 036_u00315w81xn.321012.1.mp4?index=36&start=210000&end=216000&brs=16324881&bre=16522136&ver=5
    # #EXTINF:9.60000,
    # 037_u00315w81xn.321012.1.mp4?index=37&start=216000&end=225600&brs=16522137&bre=16890781&ver=5
    # #EXTINF:6.00000,
    # 038_u00315w81xn.321012.1.mp4?index=38&start=225600&end=231600&brs=16890782&bre=17072126&ver=5
    # #EXTINF:6.00000,
    # 039_u00315w81xn.321012.1.mp4?index=39&start=231600&end=237600&brs=17072127&bre=17179345&ver=5
    # #EXTINF:2.40000,
    # 040_u00315w81xn.321012.1.mp4?index=40&start=237600&end=240000&brs=17179346&bre=17218480&ver=5
    # #EXTINF:6.00000,
    # 041_u00315w81xn.321012.1.mp4?index=41&start=240000&end=246000&brs=17218481&bre=17311739&ver=5
    # #EXTINF:6.00000,
    # 042_u00315w81xn.321012.1.mp4?index=42&start=246000&end=252000&brs=17311740&bre=17485905&ver=5
    # #EXTINF:6.00000,
    # 043_u00315w81xn.321012.1.mp4?index=43&start=252000&end=258000&brs=17485906&bre=17650679&ver=5
    # #EXTINF:7.08000,
    # 044_u00315w81xn.321012.1.mp4?index=44&start=258000&end=265080&brs=17650680&bre=18151644&ver=5
    # #EXTINF:4.92000,
    # 045_u00315w81xn.321012.1.mp4?index=45&start=265080&end=270000&brs=18151645&bre=18501364&ver=5
    # #EXTINF:6.00000,
    # 046_u00315w81xn.321012.1.mp4?index=46&start=270000&end=276000&brs=18501365&bre=18630593&ver=5
    # #EXTINF:6.00000,
    # 047_u00315w81xn.321012.1.mp4?index=47&start=276000&end=282000&brs=18630594&bre=18814572&ver=5
    # #EXTINF:9.52000,
    # 048_u00315w81xn.321012.1.mp4?index=48&start=282000&end=291520&brs=18814573&bre=19126830&ver=5
    # #EXTINF:6.00000,
    # 049_u00315w81xn.321012.1.mp4?index=49&start=291520&end=297520&brs=19126831&bre=19253920&ver=5
    # #EXTINF:2.48000,
    # 050_u00315w81xn.321012.1.mp4?index=50&start=297520&end=300000&brs=19253921&bre=19335805&ver=5
    # #EXTINF:6.00000,
    # 051_u00315w81xn.321012.2.mp4?index=51&start=300000&end=306000&brs=0&bre=163417&ver=5
    # #EXTINF:6.00000,
    # 052_u00315w81xn.321012.2.mp4?index=52&start=306000&end=312000&brs=163418&bre=279574&ver=5
    # #EXT-X-ENDLIST

"""

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


def test_vip_video():

    pass


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


if __name__ == '__main__':

    test_vip_video()