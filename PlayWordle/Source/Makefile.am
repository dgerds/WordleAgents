SUBDIRS = 

bin_PROGRAMS = PlayWordle
PlayWordle_SOURCES = PlayWordle.cpp
PlayWordledir = playwordle
PlayWordle_HEADERS = $(top_srcdir)/PlayWordle/Source/framework.h
PlayWordle_CXXFLAGS = -I$(top_srcdir)/WordleAgent/Include
PlayWordle_LDFLAGS = -L$(top_builddir)/WordleAgent/Source/.libs -lagent
