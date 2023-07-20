from lxml import etree
import ssl
import urllib.request

url = 'https://movie.douban.com/top250'
# context = ssl.SSLContext(ssl.PROTOCOL_TLSv1_1)
context = ssl._create_unverified_context()
headers = {
    b'User-Agent': b'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36'}

req = urllib.request.Request(url, headers=headers)


def fetch_page(url):
    response = urllib.request.urlopen(req, context=context)
    return response


def parse(url):
    response = fetch_page(url)
    page = response.read()
    print(page)
    html = etree.HTML(page)

    xpath_movie = '//*[@id="content"]/div/div[1]/ol/li'
    xpath_title = './/span[@class="title"]'
    xpath_pages = '//*[@id="content"]/div/div[1]/div[2]/a'

    pages = html.xpath(xpath_pages)
    fetch_list = []
    result = []

    for element_movie in html.xpath(xpath_movie):
        result.append(element_movie)

    for p in pages:
        fetch_list.append(url + p.get('href'))

    for url in fetch_list:
        response = fetch_page(url)
        page = response.read()
        html = etree.HTML(page)
        for element_movie in html.xpath(xpath_movie):
            result.append(element_movie)

    for i, movie in enumerate(result, 1):
        title = movie.find(xpath_title).text
        print(i, title)


def main():
    parse(url)


if __name__ == '__main__':
    main()
