import sys
import urllib.request as urllib2
from importlib import abc
from importlib.machinery import ModuleSpec


class UrlMetaFinder(abc.MetaPathFinder):
    def __init__(self, baseurl):
        self._baseurl = baseurl

    def find_spec(self, fullname, path=None, target=None):
        if path is None:
            baseurl = self._baseurl
        else:
            # 不是原定义的url就直接返回不存在
            if not path.startswith(self._baseurl):
                return None
            baseurl = path

        try:
            loader = UrlMetaLoader(baseurl)
            return ModuleSpec(fullname, loader,
                              is_package=loader.is_package(fullname))
        except Exception:
            return None


class UrlMetaLoader(abc.SourceLoader):
    def __init__(self, baseurl):
        self.baseurl = baseurl

    def get_code(self, fullname):
        f = urllib2.urlopen(self.get_filename(fullname))
        return f.read()

    def get_data(self):
        pass

    def get_filename(self, fullname):
        return self.baseurl + fullname + '.py'


def install_meta(address):
    finder = UrlMetaFinder(address)
    sys.meta_path.append(finder)
