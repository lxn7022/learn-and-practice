class Platform:
    def __init__(self, plugins):
        self.plugins = []
        self.loadPlugins(plugins)

    def sayHello(self, from_):
        print("hello from %s." % from_)

    def sayGoodbye(self, from_):
        print("goodbye from %s." % from_)

    def loadPlugins(self, plugins):
        print("********** loadPlugins **********")
        for pluginName in plugins:
            self.runPlugin(pluginName)

    def runPlugin(self, pluginName):
        print("********** runPlugin **********")
        print('pluginName: ', pluginName)
        plugin = __import__("plugins."+pluginName,
                            fromlist=[pluginName])
        clazz = plugin.getPluginClass()
        o = clazz()
        o.setPlatform(self)
        print('clazz: ', clazz)
        o.start()
        self.plugins.append(o)list

    def shutdown(self):
        for o in self.plugins:
            o.stop()
            o.setPlatform(None)
        self.plugins = []


# my.conf
custom_plugins = ['plugin1', 'plugin2']

if __name__ == "__main__":
    platform = Platform(custom_plugins)
    platform.shutdown()
