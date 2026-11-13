# TELL Flores — Floricultura Virtual
Integrantes: Emanuelle Santos Gonçalves, Laura Maria dos Santos Pereira, Luiza Mendes Barros Amaral, Tomás Freitas Hallack

## Problema e motivação
Pequenas e médias floriculturas costumam ter dificuldades para vender online e organizar suas vendas, dependendo muito do atendimento presencial ou de mensagens informais. Isso dificulta a exibição do catálogo de produtos, a montagem de arranjos e o controle de estoque e pedidos em tempo real.

O objetivo deste projeto é desenvolver um sistema para uma floricultura virtual que automatize o processo de vendas. O sistema permitirá que os clientes naveguem pelo catálogo, façam pedidos e personalizem os destinatários de forma simples, além de oferecer um painel administrativo para controle de estoque, pedidos e usuários.

A motivação para a escolha surgiu a partir de um trabalho prévio de planejamento de marketing que um dos integrantes realizou sobre o mercado de flores online para presentear. Durante a pesquisa, houve grande dificuldade em encontrar informações transparentes e plataformas bem estruturadas nesse segmento. Essa falta de dados e de soluções acessíveis no mercado motivou o grupo a desenvolver um sistema funcional focado nesse modelo de negócio, unindo o e-commerce tradicional à venda online.

## Solução
Sistema digital com dois tipos de usuário:
- Comprador: cadastro e login, busca de produtos, favoritos, carrinho, finalização do pedido com endereço e cupom, histórico, cancelamento e avaliação.
- Gerente: cadastro e edição de produtos, controle de estoque, atualização do status dos pedidos e criação de cupons.

## Funcionalidades
- Cadastro (apenas comprador) e login (comprador e gerente);
- Busca de produtos por nome;
- Carrinho com controle de quantidade;
- Cálculo do frete de acordo com a região do estado (UF);
- Cupom de desconto com validade;
- Finalização do pedido com redução no estoque;
- Status do pedido: Em processamento → Enviado → Entregue / Cancelado;
- Cancelamento com devolução do estoque;
- Painel do gerente: produtos, pedidos e cupons;
- Alerta de estoque abaixo do mínimo no painel do gerente;
- Cadastro de imagem do produto pelo gerente;
- Persistência em arquivos .txt;

### Funcionalidades extras
- Avaliar produtos de 1 a 5 estrelas (habilitado após a entrega);
- Favoritar produtos (sem tela própria. Fica visível como favorito na seção de produtos);
- Cards como widgets à parte da interface principal (reutilizáveis; Deixam as operações para a interface e só sinalizam);
- Interface desenvolvida com Qt Designer, com identidade visual planejada no Figma e implementada no Qt Creator.

## Tecnologias Utilizadas
- Linguagem: C++17;
- Interface: Qt Widgets e Qt Designer;
- Build: CMake e Make;
- Testes: doctest;
- Cobertura de testes: gcovr;
- Documentação: Doxygen.

## Requisitos Mínimos
- g++ 13;
- Qt 6 (módulos QtWidgets e QtSvg);
- CMake 3.16 ou superior;
- make, gcovr e doxygen

### Instalação no Linux (Ubuntu, testado no WSL)
    sudo apt update
    sudo apt install -y build-essential cmake git gcovr qt6-base-dev qt6-svg-dev libgl1-mesa-dev

### Windows
Use o Git Bash com o MinGW do Qt no PATH e `mingw32-make` no lugar de `make`,
ou abra o `CMakeLists.txt` no Qt Creator.

## Como compilar e executar
    make              # roda os testes e compila a interface
    make run          # compila a interface e abre o programa
    make test         # compila e roda os testes de unidade
    make coverage     # roda os testes e gera o relatório em coverage/index.html
    make clean        # apaga arquivos gerados
    doxygen Doxyfile  # gera a documentação em docs/html/index.html

## Estrutura
- `include/` e `src/`: classes e interface;
- `tests/`: testes de unidade (doctest);
- `data/`: dados salvos e imagens cadastradas;
- `design/`: user stories e cartões CRC;
- `docs/`: documentação gerada pelo Doxygen;
- `Resources/`: imagens e fonte da interface.

## Acesso do administrador
Login do gerente: admin@tell.com / admin

## Arquitetura
- Interface: telas e componentes gráficos;
- Sistema: coordena as operações e integra as classes;
- Modelagem do sistema: classes que representam os elementos da floricultura e suas regras;
- Persistência: leitura e gravação dos dados em arquivos `.txt`.

## Conceitos de OO aplicados
- Herança e polimorfismo: Gerente e Comprador herdam de Pessoa; o Sistema guarda `std::vector<Pessoa*>` e usa `dynamic_cast`;
- Encapsulamento: atributos privados; validação nos construtores; total da venda calculado internamente;
- Composição: Venda contém ItemPedido, Endereco e Desconto;
- Tratamento de exceções: as classes validam os dados e lançam `invalid_argument`, `out_of_range`, `logic_error` ou `runtime_error` conforme o caso; a interface captura e mostra a mensagem.