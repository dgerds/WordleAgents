SUBDIRS = 

lib_LTLIBRARIES = librandomagent.la
librandomagent_la_SOURCES = \
	./dllmain.cpp \
	./MyAgent.cpp
librandomagent_ladir = randomagent
librandomagent_la_HEADERS = $(top_srcdir)/RandomAgent/Source/framework.h $(top_srcdir)/RandomAgent/Source/MyAgent.h $(top_srcdir)/RandomAgent/Source/MyAgentFactory.h
librandomagent_la_CXXFLAGS = -I$(top_srcdir)/WordleAgent/Include
librandomagent_la_LDFLAGS = -L$(top_builddir)/WordleAgent/Source/.libs -lagent

