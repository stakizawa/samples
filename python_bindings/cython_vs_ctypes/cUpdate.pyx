cimport update

class Updater(object):
    def __init__(self):
        super(Updater, self).__init__()

    def version(self):
        return update.version()
