####### kdevelop will overwrite this part!!! (begin)##########
kde_module_LTLIBRARIES = libkcm_knetswitch.la


INCLUDES = $(all_includes)


LDFLAGS = 

libkcm_knetswitch_la_METASOURCES=AUTO

libkcm_knetswitch_la_SOURCES = ipvalidator.cpp profilewidget.cpp profiletab.ui knetswitch.cpp 
libkcm_knetswitch_la_LIBADD = $(X_LDFLAGS) $(KDE_LDFLAGS) $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT)

libkcm_knetswitch_la_LDFLAGS = -module $(KDE_PLUGIN)  



EXTRA_DIST = knetswitch.cpp knetswitch.h profiletab.ui profilewidget.cpp profilewidget.h knetswitch.desktop ipvalidator.cpp ipvalidator.h profiletab.h 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Settings/Network/
	$(INSTALL_DATA) $(srcdir)/knetswitch.desktop $(kde_appsdir)/Settings/Network/

uninstall-local:
	-rm -f $(kde_appsdir)/Settings/Network/

####### kdevelop will overwrite this part!!! (end)############
messages:
	$(XGETTEXT) $(libkcm_knetswitch_la_SOURCES) -o $(podir)/kcmknetswitch.pot

