# MAKEFILE - Floricultura TELL
#
# make test      -> compila as classes e os testes e executa os testes
# make coverage  -> roda os testes e gera o relatorio de cobertura (minimo de 60%)
# make clean     -> apaga os arquivos gerados
#
# O executavel do sistema (interface Qt) e gerado pelo CMakeLists.txt, nao por este Makefile.
 

# Compilação
CC = g++
CFLAGS = -std=c++17 -Wall -g -I include --coverage
 
# Pastas
SRC_DIR = ./src
BUILD_DIR = ./build
TESTS_DIR = ./tests
INCLUDE_DIR = ./include

# Executável dos testes 
TARGET_TEST = ./build/executavel_testes

# Executável do sistema
TARGET_APP = ${BUILD_DIR}/floricultura

# Objetos das classes
OBJS_CLASSES = ${BUILD_DIR}/Pessoa.o ${BUILD_DIR}/Gerente.o ${BUILD_DIR}/Comprador.o ${BUILD_DIR}/Endereco.o ${BUILD_DIR}/Desconto.o ${BUILD_DIR}/Produto.o ${BUILD_DIR}/Venda.o ${BUILD_DIR}/ItemPedido.o ${BUILD_DIR}/Sistema.o ${BUILD_DIR}/PessoaRepositorio.o ${BUILD_DIR}/ProdutoRepositorio.o ${BUILD_DIR}/VendaRepositorio.o ${BUILD_DIR}/DescontoRepositorio.o

# Objetos dos testes
OBJS_TEST = ${BUILD_DIR}/TestePessoa.o ${BUILD_DIR}/TesteGerente.o ${BUILD_DIR}/TesteComprador.o ${BUILD_DIR}/TesteEndereco.o ${BUILD_DIR}/TesteDesconto.o ${BUILD_DIR}/TesteProduto.o ${BUILD_DIR}/TesteVenda.o ${BUILD_DIR}/TesteItemPedido.o ${BUILD_DIR}/TesteSistema.o ${BUILD_DIR}/TestePessoaRepositorio.o ${BUILD_DIR}/TesteProdutoRepositorio.o ${BUILD_DIR}/TesteVendaRepositorio.o ${BUILD_DIR}/TesteDescontoRepositorio.o ${BUILD_DIR}/main_test.o

# Comando make test
test: ${TARGET_TEST}
	./${TARGET_TEST}

# Linkando e gerando executavel dos testes
${TARGET_TEST}: ${OBJS_CLASSES} ${OBJS_TEST}
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -o ${TARGET_TEST} ${OBJS_CLASSES} ${OBJS_TEST}

# Executável do sistema (para a C10 quando existir src/main.cpp)
floricultura: ${TARGET_APP}

${TARGET_APP}: ${OBJS_CLASSES} ${BUILD_DIR}/main.o
	${CC} ${CFLAGS} -o ${TARGET_APP} ${OBJS_CLASSES} ${BUILD_DIR}/main.o


# ============= compilação dos testes =============
 
${BUILD_DIR}/TestePessoa.o: ${TESTS_DIR}/TestePessoa.cpp ${INCLUDE_DIR}/Pessoa.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TestePessoa.cpp -o ${BUILD_DIR}/TestePessoa.o
 
${BUILD_DIR}/TesteGerente.o: ${TESTS_DIR}/TesteGerente.cpp ${INCLUDE_DIR}/Gerente.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteGerente.cpp -o ${BUILD_DIR}/TesteGerente.o
 
${BUILD_DIR}/TesteComprador.o: ${TESTS_DIR}/TesteComprador.cpp ${INCLUDE_DIR}/Comprador.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteComprador.cpp -o ${BUILD_DIR}/TesteComprador.o
 
${BUILD_DIR}/TesteEndereco.o: ${TESTS_DIR}/TesteEndereco.cpp ${INCLUDE_DIR}/Endereco.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteEndereco.cpp -o ${BUILD_DIR}/TesteEndereco.o
 
${BUILD_DIR}/TesteDesconto.o: ${TESTS_DIR}/TesteDesconto.cpp ${INCLUDE_DIR}/Desconto.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteDesconto.cpp -o ${BUILD_DIR}/TesteDesconto.o
 
${BUILD_DIR}/TesteProduto.o: ${TESTS_DIR}/TesteProduto.cpp ${INCLUDE_DIR}/Produto.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteProduto.cpp -o ${BUILD_DIR}/TesteProduto.o
 
${BUILD_DIR}/TesteVenda.o: ${TESTS_DIR}/TesteVenda.cpp ${INCLUDE_DIR}/Venda.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteVenda.cpp -o ${BUILD_DIR}/TesteVenda.o
 
${BUILD_DIR}/TesteItemPedido.o: ${TESTS_DIR}/TesteItemPedido.cpp ${INCLUDE_DIR}/ItemPedido.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteItemPedido.cpp -o ${BUILD_DIR}/TesteItemPedido.o

${BUILD_DIR}/TesteSistema.o: ${TESTS_DIR}/TesteSistema.cpp ${INCLUDE_DIR}/Sistema.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteSistema.cpp -o ${BUILD_DIR}/TesteSistema.o
 
${BUILD_DIR}/TestePessoaRepositorio.o: ${TESTS_DIR}/TestePessoaRepositorio.cpp ${INCLUDE_DIR}/PessoaRepositorio.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TestePessoaRepositorio.cpp -o ${BUILD_DIR}/TestePessoaRepositorio.o
 
${BUILD_DIR}/TesteProdutoRepositorio.o: ${TESTS_DIR}/TesteProdutoRepositorio.cpp ${INCLUDE_DIR}/ProdutoRepositorio.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteProdutoRepositorio.cpp -o ${BUILD_DIR}/TesteProdutoRepositorio.o
 
${BUILD_DIR}/TesteVendaRepositorio.o: ${TESTS_DIR}/TesteVendaRepositorio.cpp ${INCLUDE_DIR}/VendaRepositorio.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteVendaRepositorio.cpp -o ${BUILD_DIR}/TesteVendaRepositorio.o
 
${BUILD_DIR}/TesteDescontoRepositorio.o: ${TESTS_DIR}/TesteDescontoRepositorio.cpp ${INCLUDE_DIR}/DescontoRepositorio.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/TesteDescontoRepositorio.cpp -o ${BUILD_DIR}/TesteDescontoRepositorio.o
 
${BUILD_DIR}/main_test.o: ${TESTS_DIR}/main_test.cpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${TESTS_DIR}/main_test.cpp -o ${BUILD_DIR}/main_test.o

# ============= compilação das classes =============

${BUILD_DIR}/Pessoa.o: ${SRC_DIR}/Pessoa.cpp ${INCLUDE_DIR}/Pessoa.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/Pessoa.cpp -o ${BUILD_DIR}/Pessoa.o

${BUILD_DIR}/Gerente.o: ${SRC_DIR}/Gerente.cpp ${INCLUDE_DIR}/Gerente.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/Gerente.cpp -o ${BUILD_DIR}/Gerente.o

${BUILD_DIR}/Comprador.o: ${SRC_DIR}/Comprador.cpp ${INCLUDE_DIR}/Comprador.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/Comprador.cpp -o ${BUILD_DIR}/Comprador.o

${BUILD_DIR}/Endereco.o: ${SRC_DIR}/Endereco.cpp ${INCLUDE_DIR}/Endereco.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/Endereco.cpp -o ${BUILD_DIR}/Endereco.o

${BUILD_DIR}/Desconto.o: ${SRC_DIR}/Desconto.cpp ${INCLUDE_DIR}/Desconto.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/Desconto.cpp -o ${BUILD_DIR}/Desconto.o

${BUILD_DIR}/Produto.o: ${SRC_DIR}/Produto.cpp ${INCLUDE_DIR}/Produto.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/Produto.cpp -o ${BUILD_DIR}/Produto.o

${BUILD_DIR}/Venda.o: ${SRC_DIR}/Venda.cpp ${INCLUDE_DIR}/Venda.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/Venda.cpp -o ${BUILD_DIR}/Venda.o

${BUILD_DIR}/ItemPedido.o: ${SRC_DIR}/ItemPedido.cpp ${INCLUDE_DIR}/ItemPedido.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/ItemPedido.cpp -o ${BUILD_DIR}/ItemPedido.o

${BUILD_DIR}/Sistema.o: ${SRC_DIR}/Sistema.cpp ${INCLUDE_DIR}/Sistema.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/Sistema.cpp -o ${BUILD_DIR}/Sistema.o
 
${BUILD_DIR}/PessoaRepositorio.o: ${SRC_DIR}/PessoaRepositorio.cpp ${INCLUDE_DIR}/PessoaRepositorio.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/PessoaRepositorio.cpp -o ${BUILD_DIR}/PessoaRepositorio.o
 
${BUILD_DIR}/ProdutoRepositorio.o: ${SRC_DIR}/ProdutoRepositorio.cpp ${INCLUDE_DIR}/ProdutoRepositorio.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/ProdutoRepositorio.cpp -o ${BUILD_DIR}/ProdutoRepositorio.o
 
${BUILD_DIR}/VendaRepositorio.o: ${SRC_DIR}/VendaRepositorio.cpp ${INCLUDE_DIR}/VendaRepositorio.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/VendaRepositorio.cpp -o ${BUILD_DIR}/VendaRepositorio.o
 
${BUILD_DIR}/DescontoRepositorio.o: ${SRC_DIR}/DescontoRepositorio.cpp ${INCLUDE_DIR}/DescontoRepositorio.hpp
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -c ${SRC_DIR}/DescontoRepositorio.cpp -o ${BUILD_DIR}/DescontoRepositorio.o
 

# ============= cobertura (>= 60%) =============

coverage: test
	@mkdir -p coverage
	gcovr -r . --object-directory ${BUILD_DIR} --exclude tests/ --html --html-details -o coverage/index.html
	gcovr -r . --object-directory ${BUILD_DIR} --exclude tests/ --print-summary --fail-under-line 60

clean:
	rm -rf ${BUILD_DIR}/*.o ${BUILD_DIR}/*.gcda ${BUILD_DIR}/*.gcno ${TARGET_TEST} ${TARGET_TEST} coverage

.PHONY: test coverage clean