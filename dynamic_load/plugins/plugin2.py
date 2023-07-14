def sayGoodbye(self, from_):
    print("goodbye from %s." % from_)


class Plugin2:
    def setPlatform(self, platform):
        self.platform = platform

    def start(self):
        self.platform.sayHello("plugin2")

    def stop(self):
        self.platform.sayGoodbye("plugin2")


def getPluginClass():
    return Plugin2
