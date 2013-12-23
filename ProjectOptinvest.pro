TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS = QPersistence LBGui src

QPersistence.subdir = lib/QPersistence
LBGui.subdir = lib/LBGui
src.subdir = src
src.depends = QPersistence
src.depens = LBGui




