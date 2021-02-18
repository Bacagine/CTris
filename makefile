# Make file created by Mitchel Paulin <Mitchel0022@gmail.com>
# and modificated by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
# 
# Date of last modification: 18/02/2021

TARGET          = ctris
BINDIR          = ./bin
SRCDIR          = ./src
INCDIR          = ./include
OBJDIR          = ./obj
ICONDIR         = ./pixmaps
BIN             = $(BINDIR)/$(TARGET)
ICON            = $(ICONDIR)/htop.png
DESKFILE        = ctris.desktop
CXX             = g++
#link the curses directory 
CFLAGS          = -lncursesw

run:
	@$(BIN)
clean:
	rm -rvf $(OBJDIR)
distclean: clean
	rm -rvf $(BINDIR)
install: all
	cp -v $(BIN) /usr/bin/
	cp -v $(ICON) /usr/share/pixmaps/
	desktop-file-install $(DESKFILE)
uninstall:
	rm -rvf  /usr/$(BIN)
	cp -v /usr/share/$(ICON)
	rm -rvf /usr/share/applications/$(DESKFILE)
.PHONY: all run clean distclean install uninstall
