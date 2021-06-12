strutil: strutil.o
dc: dc.o pila.o calc_helper.o strutil.o
infix:  infix.o calc_helper.o pila.o cola.o  strutil.o
pruebas: strutil.o testing.o pruebas_strutil.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^