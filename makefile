OBJS = main.o parsing.o isbuiltin.o runcommand.o
SRCS = $(OBJS:.o=.c)

#$(CC) = gcc

minishell: $(OBJS)
	$(CC) -o $@ $(OBJS)

.c.o: $(SRCS)
	$(CC) -c $<

clean:
	rm $(OBJS) minishell
