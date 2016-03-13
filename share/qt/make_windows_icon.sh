#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/oxen.ico

convert ../../src/qt/res/icons/oxen-16.png ../../src/qt/res/icons/oxen-32.png ../../src/qt/res/icons/oxen-48.png ${ICON_DST}
