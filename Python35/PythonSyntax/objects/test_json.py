import json


def test_basic():

    # str => json
    content = '{"accessToken": "521de21161b23988173e6f7f48f9ee96e28", "User-Agent": "Apache-HttpClient/4.5.2 (Java/1.8.0_131)"}'
    res = json.loads(content)
    print('res type %s' % type(res))
    print(res)


    # json => str
    json_content = {"accessToken": "521de21161b23988173e6f7f48f9ee96e28", "User-Agent": "Apache-HttpClient/4.5.2 (Java/1.8.0_131)"}
    res_str = json.dumps(json_content)

    print('res_str %s' % type(res_str))
    print(res_str)



if __name__ == '__main__':

    test_basic()