include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

#CONFIG		+= console
QT			+= widgets charts

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter02/ks02_12


#INCLUDEPATH += $$TRAIN_INCLUDE_PATH
		
FORMS		+= dialogbase.ui

HEADERS		+= $$TRAIN_SRC_PATH/gui_base.pri \
				ks02_12.pro \
				dialog.h \
				tip.h \
				chartview.h  \
				customchart.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp \
				tip.cpp \
				chartview.cpp \
				customchart.cpp
				
				debug_and_release {
	CONFIG(debug, debug|release) {	
	
                TARGET = ks02_12_d
	}
	CONFIG(release, debug|release) {			   
				   
                TARGET	= ks02_12
	}
} else {
	debug {
	
                TARGET	= ks02_12_d
	}
	release {
		
                TARGET 	= ks02_12
	}
}

DESTDIR     = $$TRAIN_BIN_PATH
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui
