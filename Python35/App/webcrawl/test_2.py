import requests

from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time


def spider(url, keyword):

    chrome = webdriver.Chrome('/Users/yusun/Downloads/chromedriver')

    chrome.get(url)

    chrome.implicitly_wait(3)

    try:
        input_tag = chrome.find_element_by_id("key") # id="key"

        input_tag.send_keys(keyword)

        input_tag.send_keys(Keys.ENTER)

        time.sleep(5)


        get_goods(chrome)

    finally:

        chrome.close()


def get_goods(driver):

    try:

        goods = driver.find_elements_by_class_name('gl-item')

        for good in goods:

            detail_url = good.find_elements_by_tag_name('a').get_attribute('href')

            p_name = good.find_element_by_css_selector('.p-name em').text.replace('\n', ' ')

            p_price = good.find_element_by_css_selector('.p-price i').text  #

            p_commit = good.find_element_by_css_selector('.p-commit a').text

            msg = """
             Name: %s
             link: %s
             price: %s
             commit:%s""" % (p_name, detail_url, p_price, p_commit)


            button = driver.find_elements_by_link_text('下一页')

            button.click()

            time.sleep(10)

            get_goods(driver)

    except Exception:
        pass


if __name__ == '__main__':

    spider('https://www.jd.com', "kouzhao")