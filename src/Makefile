########################################################################
# Metodi e Modelli per l'Ottimizzazione Combinatoria - Makefile
# Marco Zanella <marco.zanella.9@studenti.unipd.it>


########################################################################
# Configuration
CC      = g++
CCFLAGS = -Wall -Wextra -pedantic -Wno-long-long -O3 -ansi
LDFLAGS = -lm -pthread -lcplex

CPX_INC = /opt/CPLEX_Studio/cplex/include
CPX_LIB = /opt/CPLEX_Studio/cplex/lib/x86-64_linux/static_pic

CPPLINT = ../bin/cpplint.py
LINTOPT = --root=`pwd`
CHECKER = cppcheck -q

BIN     = ../bin/



########################################################################
# Dependencies
PROJ = instance_generator random_solver cplex_solver ga_solver

OBJS = Stopwatch.o RNG.o Node.o Panel.o \
       costFunction/CostFunction.o costFunction/Euclidean.o \
       costFunction/Manhattan.o costFunction/Minkowski.o \
       costFunction/Unfair.o \
       perturbator/Perturbator.o perturbator/Null.o perturbator/Uniform.o \
       perturbator/Normal.o \
       generator/Generator.o generator/Uniform.o generator/Line.o \
       generator/SuperEllipse.o \
       solver/Solver.o solver/Random.o solver/Greedy.o \
       solver/AGLSA.o solver/Chromosome.o solver/Population.o \
       Solution.o Instance.o \
       solver/CPLEX.o solver/CPLEXManager.o

all: $(PROJ)

instance_generator: $(OBJS) generator.o

random_solver: $(OBJS) random_solver.o

cplex_solver: $(OBJS) cplex_solver.o

ga_solver: $(OBJS) ga_solver.o

install: $(PROJ)

.PHONY: clean doc linter



########################################################################
# Recipes
%.o: %.cpp
	@echo "Compiling $@..."
	@$(CC) $(CCFLAGS) -I$(CPX_INC) -c $^ -o $@

$(PROJ):
	@echo "Linking $@..."
	@$(CC) $(CCFLAGS) -o $@ $^ -L$(CPX_LIB) $(LDFLAGS)
	@echo "done."

install:
	@echo "Copying under $(BIN)"
	@cp $(PROJ) $(BIN)

clean:
	@echo "Cleaning..."
	@rm -fR *.o $(PROJ)
	@rm -fR costFunction/*.o
	@rm -fR generator/*.o
	@rm -fR perturbator/*.o
	@rm -fR solver/*.o

doc:
	@echo "Generating documentation..."
	@doxygen ../doc/Doxyfile

linter:
	@echo "*** Running cpplint..."
	@$(CPPLINT) $(LINTOPT) *.h *.cpp
	@$(CPPLINT) $(LINTOPT) costFunction/*.h costFunction/*.cpp
	@$(CPPLINT) $(LINTOPT) generator/*.h generator/*.cpp
	@$(CPPLINT) $(LINTOPT) perturbator/*.h perturbator/*.cpp
	@$(CPPLINT) $(LINTOPT) solver/*.h solver/*.cpp
	@echo "*** Running cppchecker..."
	@$(CHECKER) ./
