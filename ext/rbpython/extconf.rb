require 'mkmf'

dir_config("rbpython")
find_library("python2.5",nil)
find_header("python2.5/Python.h")
find_header("ruby.h")
create_makefile("rbpython")