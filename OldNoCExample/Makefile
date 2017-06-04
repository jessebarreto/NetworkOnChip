IDIR	= /usr/local/systemc/include
LDIR	= /usr/local/systemc/lib-linux64
LIBS	= -lsystemc
CC     	= g++
CFLAGS	= -I$(IDIR) -L$(LDIR) $(LIBS) -g -std=c++11
SRCS	= $(wildcard *.cpp)
OBJS	= $(SRCS:.cpp=.o)
DEPS	= $(wildcard *.h)
EXEC	= noc

all:	$(EXEC)
	@echo "*****************************"
	@echo "*****************************"
	@echo "*********** gerando $(EXEC)"

$(EXEC):      $(OBJS)
#	      $(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
	$(CC) -o $@ $^ $(CFLAGS)

%.o:	%.cpp $(DEPS)
	@echo "*********** compilando $<"
#	$(CC) $(CFLAGS) -c $<
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f *~ *.o $(EXEC)
