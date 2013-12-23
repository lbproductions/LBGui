TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS = src \ #examples
    test

src.subdir      = src
examples.subdir     = examples
examples.depends    = src
