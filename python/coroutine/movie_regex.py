import requests
from time import time
import re

url = 'https://movie.douban.com/top250'
headers = {
    b'User-Agent': b'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36'}


def fetch_page(url):
    response = requests.get(url, headers=headers)
    return response


def parse(url):
    response = fetch_page(url)
    page = response.content

    fetch_list = set()
    result = []

    for title in re.findall(rb'<a href=.*\s.*<span class="title">(.*)</span>', page):
        result.append(title)

    for postfix in re.findall(rb'<a href="(\?start=.*?)"', page):
        fetch_list.add(url + postfix.decode())

    for url in fetch_list:
        response = fetch_page(url)
        page = response.content
        for title in re.findall(rb'<a href=.*\s.*<span class="title">(.*)</span>', page):
            result.append(title)

    for i, title in enumerate(result, 1):
        title = title.decode()
        print(i, title)


def main():
    from time import time
    start = time()
    for i in range(5):
        parse(url)
    end = time()
    print('Cost {} seconds'.format((end - start) / 5))


if __name__ == "__main__":
    main()
