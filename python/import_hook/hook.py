import sys
from types import ModuleType
from importlib.machinery import ModuleSpec
from importlib.abc import MetaPathFinder, Loader


class Module(ModuleType):
    def __init__(self, name):
        self.x = 1
        self.name = name


class ExampleLoader(Loader):
    def create_module(self, spec):
        return Module(spec.name)

    def exec_module(self, module):
        module.y = 2


class ExampleFinder(MetaPathFinder):
    def find_spec(self, fullname, path, target=None):
        return ModuleSpec('module', ExampleLoader())


def example_hook(path):
    # some conditions here
    return ExampleFinder()


sys.path_hooks = [example_hook]
# force to use the hook
sys.path_importer_cache.clear()


if __name__ == '__main__':
    import module
    print(module)
