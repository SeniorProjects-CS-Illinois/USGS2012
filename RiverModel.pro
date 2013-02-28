TEMPLATE = subdirs
SUBDIRS = main/RiverModelGUI.pro \
          main/RiverModel.pro

docs.target = doc
docs.commands = doxygen ../Doxyfile

dox.depends = 


QMAKE_EXTRA_TARGETS += docs
