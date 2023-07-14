class Plugin1:
    def setPlatform(self, platform):
        self.platform = platform

    def start(self):
        self.platform.sayHello("plugin1")

    def stop(self):
        self.platform.sayGoodbye("plugin1")


def getPluginClass():
    return Plugin1
