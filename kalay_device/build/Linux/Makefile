
# Target folder
RELEASE_TARGET := Release
DEBUG_TARGET := Debug

all: release debug

release:
	mkdir -p $(RELEASE_TARGET); \
	cd $(RELEASE_TARGET); \
	$(CC) $(CFLAG) $(SRC) $(INCLUDE) -L$(TARGETDIR) $(SHAREFLAG) -o ../$(TARGETDIR)/$(SHARELIB); \
	$(CC) -c $(CFLAG) $(INCLUDE) $(SRC); \
	$(AR) $(ARFLAG) ../$(TARGETDIR)/$(STATICLIB) $(OBJ)

debug:
	mkdir -p $(DEBUG_TARGET); \
	cd $(DEBUG_TARGET); \
	$(CC) $(CFLAG) $(SRC) $(INCLUDE) -L$(TARGETDIR) $(SHAREFLAG) -o ../$(TARGETDIR)/$(SHARELIB_WITH_TRACE) -DTUTK_TRACELOG; \
	$(CC) -c $(CFLAG) -DTUTK_TRACELOG $(INCLUDE) $(SRC); \
	$(AR) $(ARFLAG) ../$(TARGETDIR)/$(STATICLIB_WITH_TRACE) $(OBJ)	

clean:
	rm -rf $(RELEASE_TARGET) $(DEBUG_TARGET)

.PHONY : all release debug clean
