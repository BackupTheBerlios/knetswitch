####### kdevelop will overwrite this part!!! (begin)##########
kde_module_LTLIBRARIES = libkcm_knetswitch.la


INCLUDES = $(all_includes)


LDFLAGS =  

libkcm_knetswitch_la_METASOURCES=AUTO

libkcm_knetswitch_la_SOURCES = profilewidget.cpp profiletab.ui knetswitch.cpp 
libkcm_knetswitch_la_LIBADD =  -lXext -lX11 $(LIB_QT) $(LIB_KDECORE) $(LIB_KDEUI) 

libkcm_knetswitch_la_LDFLAGS = -module $(KDE_PLUGIN)   



EXTRA_DIST = knetswitch.cpp knetswitch.h profiletab.ui profilewidget.cpp profilewidget.h 

####### kdevelop will overwrite this part!!! (end)############
messages:
	$(XGETTEXT) $(libkcm_knetswitch_la_SOURCES) -o $(podir)/kcmknetswitch.pot

