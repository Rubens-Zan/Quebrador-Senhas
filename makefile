MODULOS = biblioteca \
	quebrador-senha

OBJETOS = teste.o $(addsuffix .o,$(MODULOS))

.PHONY : all clean

all : teste
	./$<

teste : $(OBJETOS)

clean : 
	$(RM) $(OBJETOS)
