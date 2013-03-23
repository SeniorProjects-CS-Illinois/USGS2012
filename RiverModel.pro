TEMPLATE = subdirs
SUBDIRS = main/RiverModelGUI.pro \
          main/RiverModel.pro \
          test/test.pro 

#custom target 'doc'
dox.target = doc
dox.commands = doxygen "../Doxyfile" \
    test -d doxydoc/html/images || mkdir doxydox/html/images; \
    cp documentation/images* doxydoc/html/images

dox.depends = 

QMAKE_EXTRA_TARGETS += dox
