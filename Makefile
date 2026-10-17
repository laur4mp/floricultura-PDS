# MAKEFILE - Floricultura

# copilação
CC = g++
CFLAGS = -std=c++11 -Wall -g -I include --coverage
 
# pastas
SRC_DIR = ./src
BUILD_DIR = ./build
TESTS_DIR = ./tests
INCLUDE_DIR = ./include

# exexutavel dos testes 
TARGET_TEST = ./build/executavel_testes

# executável do sistema
#TARGET_APP = ${BUILD_DIR}/floricultura

#all: ${TARGET_APP} ${TARGET_TEST}

# objetos das classes
OBJS_CLASSES = ${BUILD_DIR}/Pessoa.o ${BUILD_DIR}/Gerente.o ${BUILD_DIR}/Comprador.o ${BUILD_DIR}/Endereco.o ${BUILD_DIR}/Desconto.o ${BUILD_DIR}/Produto.o ${BUILD_DIR}/Venda.o ${BUILD_DIR}/ItemPedido.o 

#objetos dos testes
OBJS_TEST = ${BUILD_DIR}/TestePessoa.o ${BUILD_DIR}/TesteGerente.o ${BUILD_DIR}/TesteComprador.o ${BUILD_DIR}/TesteEndereco.o ${BUILD_DIR}/TesteDesconto.o ${BUILD_DIR}/TesteProduto.o ${BUILD_DIR}/TesteVenda.o ${BUILD_DIR}/TesteItemPedido.o ${BUILD_DIR}/main_test.o

# comando make test
test: ${TARGET_TEST}
	./${TARGET_TEST}

# linkando e gerando executavel dos testes
${TARGET_TEST}: ${OBJS_CLASSES} ${OBJS_TEST}
	${CC} ${CFLAGS} -o ${TARGET_TEST} ${OBJS_CLASSES} ${OBJS_TEST}

# executável do sistema (descomentar quando existir src/main.cpp)
#floricultura: ${TARGET_APP}

#${TARGET_APP}: ${OBJS_CLASSES} ${BUILD_DIR}/main.o
#	${CC} ${CFLAGS} -o ${TARGET_APP} ${OBJS_CLASSES} ${BUILD_DIR}/main.o


# ============= compilação dos testes =============
 
${BUILD_DIR}/TestePessoa.o: ${TESTS_DIR}/TestePessoa.cpp ${INCLUDE_DIR}/Pessoa.hpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TestePessoa.cpp -o ${BUILD_DIR}/TestePessoa.o
 
${BUILD_DIR}/TesteGerente.o: ${TESTS_DIR}/TesteGerente.cpp ${INCLUDE_DIR}/Gerente.hpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteGerente.cpp -o ${BUILD_DIR}/TesteGerente.o
 
${BUILD_DIR}/TesteComprador.o: ${TESTS_DIR}/TesteComprador.cpp ${INCLUDE_DIR}/Comprador.hpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteComprador.cpp -o ${BUILD_DIR}/TesteComprador.o
 
${BUILD_DIR}/TesteEndereco.o: ${TESTS_DIR}/TesteEndereco.cpp ${INCLUDE_DIR}/Endereco.hpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteEndereco.cpp -o ${BUILD_DIR}/TesteEndereco.o
 
${BUILD_DIR}/TesteDesconto.o: ${TESTS_DIR}/TesteDesconto.cpp ${INCLUDE_DIR}/Desconto.hpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteDesconto.cpp -o ${BUILD_DIR}/TesteDesconto.o
 
${BUILD_DIR}/TesteProduto.o: ${TESTS_DIR}/TesteProduto.cpp ${INCLUDE_DIR}/Produto.hpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteProduto.cpp -o ${BUILD_DIR}/TesteProduto.o
 
${BUILD_DIR}/TesteVenda.o: ${TESTS_DIR}/TesteVenda.cpp ${INCLUDE_DIR}/Venda.hpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteVenda.cpp -o ${BUILD_DIR}/TesteVenda.o
 
${BUILD_DIR}/TesteItemPedido.o: ${TESTS_DIR}/TesteItemPedido.cpp ${INCLUDE_DIR}/ItemPedido.hpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteItemPedido.cpp -o ${BUILD_DIR}/TesteItemPedido.o

${BUILD_DIR}/main_test.o: ${TESTS_DIR}/main_test.cpp
	${CC} ${CFLAGS} -c ${TESTS_DIR}/main_test.cpp -o ${BUILD_DIR}/main_test.o


# ============= compilação das classes =============

# ${BUILD_DIR}/Pessoa.o: ${SRC_DIR}/Pessoa.cpp ${INCLUDE_DIR}/Pessoa.hpp
# 	${CC} ${CFLAGS} -c ${SRC_DIR}/Pessoa.cpp -o ${BUILD_DIR}/Pessoa.o

# ${BUILD_DIR}/Gerente.o: ${SRC_DIR}/Gerente.cpp ${INCLUDE_DIR}/Gerente.hpp
# 	${CC} ${CFLAGS} -c ${SRC_DIR}/Gerente.cpp -o ${BUILD_DIR}/Gerente.o

# ${BUILD_DIR}/Comprador.o: ${SRC_DIR}/Comprador.cpp ${INCLUDE_DIR}/Comprador.hpp
# 	${CC} ${CFLAGS} -c ${SRC_DIR}/Comprador.cpp -o ${BUILD_DIR}/Comprador.o

# ${BUILD_DIR}/Endereco.o: ${SRC_DIR}/Endereco.cpp ${INCLUDE_DIR}/Endereco.hpp
# 	${CC} ${CFLAGS} -c ${SRC_DIR}/Endereco.cpp -o ${BUILD_DIR}/Endereco.o

# ${BUILD_DIR}/Desconto.o: ${SRC_DIR}/Desconto.cpp ${INCLUDE_DIR}/Desconto.hpp
# 	${CC} ${CFLAGS} -c ${SRC_DIR}/Desconto.cpp -o ${BUILD_DIR}/Desconto.o

# ${BUILD_DIR}/Produto.o: ${SRC_DIR}/Produto.cpp ${INCLUDE_DIR}/Produto.hpp
# 	${CC} ${CFLAGS} -c ${SRC_DIR}/Produto.cpp -o ${BUILD_DIR}/Produto.o

# ${BUILD_DIR}/Venda.o: ${SRC_DIR}/Venda.cpp ${INCLUDE_DIR}/Venda.hpp
# 	${CC} ${CFLAGS} -c ${SRC_DIR}/Venda.cpp -o ${BUILD_DIR}/Venda.o

# ${BUILD_DIR}/ItemPedido.o: ${SRC_DIR}/ItemPedido.cpp ${INCLUDE_DIR}/ItemPedido.hpp
# 	${CC} ${CFLAGS} -c ${SRC_DIR}/ItemPedido.cpp -o ${BUILD_DIR}/ItemPedido.o

#${BUILD_DIR}/main.o: ${SRC_DIR}/main.cpp
#	${CC} ${CFLAGS} -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o


# ============= cobertura (>= 60%) - rodar depois de make test 
coverage: test
	mkdir -p coverage
	gcovr -r . --object-directory ${BUILD_DIR} --exclude tests/ --html --html-details -o coverage/index.html
	gcovr -r . --object-directory ${BUILD_DIR} --exclude tests/ --print-summary --fail-under-line 60



clean:
	rm -rf ${BUILD_DIR}/*.o ${BUILD_DIR}/*.gcda ${BUILD_DIR}/*.gcno ${TARGET_TEST} coverage


.PHONY: test coverage clean
 
