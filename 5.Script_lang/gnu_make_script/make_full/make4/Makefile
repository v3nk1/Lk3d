#make will endup in searching a directory exists in a given search path or not, if not exists then we require that create a dir of that name

exist:=

SEARCH_PATH=..
SEARCH_DIR=ven

all:
	@if [ ! -d $(SEARCH_PATH)/$(SEARCH_DIR) -o ! -d  $(SEARCH_PATH)/om ] ; then \
	echo $(SEARCH_DIR)":not exists, Creating" && mkdir -p $(SEARCH_PATH)/$(SEARCH_DIR); \
	fi;
