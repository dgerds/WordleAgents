SUBDIRS = 

AM_CXXFLAGS = -I$(top_srcdir)/WordleAgent/Include

lib_LTLIBRARIES = libagent.la
libagent_la_SOURCES = \
	Game.cpp \
	Timer.cpp \
	Random.cpp \
	OutputHelper.cpp \
	CsvReader.cpp \
	AgentFactoryDll.cpp
libagent_ladir = wordleagent
libagent_la_HEADERS = \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/Agent.h \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/AgentFactoryDll.h \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/AgentFactory.h \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/CsvReader.h \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/framework.h \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/Timer.h \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/Random.h \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/Game.h \
	$(top_srcdir)/WordleAgent/Include/WordleAgent/OutputHelper.h
libagent_la_CXXFLAGS = $(AM_CXXFLAGS)

