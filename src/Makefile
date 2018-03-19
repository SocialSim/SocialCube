WARNINGS := -Wall -Wextra 
CFLAGS ?= -O2 -std=c++11 $(WARNINGS)
 
OBJDIR := obj
SRCDIR := src
 
ifeq ($(DEBUG_BUILD),1)
    CFLAGS +=-DDEBUG -g
endif
     
CFLAGS += -MMD -MP 
DEPS := $(patsubst %,$(OBJDIR)/%,$(_SRCS:c=d))

all: main
	 
createdir:
	$(SILENCER)mkdir -p $(OBJDIR)
		 
main: $(OBJS) 
	$(SILENCER)$(CC) $(CFLAGS) -o $@ $^ 
	$(SILENCER)$(CC) $(CFLAGS) -c -o $@ $< 
				  
clean:
	$(SILENCER)$(RM) -f *~ core main
	$(SILENCER)$(RM) -r $(OBJDIR)
			 
.PHONY: clean all
	 
