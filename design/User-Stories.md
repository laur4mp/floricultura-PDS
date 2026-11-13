**Gerente**



**Descrição 1:** Como gerente, quero cadastrar um novo produto no catálogo para disponibilizá-lo aos clientes.

**Critérios de aceitação:**

* Permitir inserir **nome, descrição, preço** e **categoria** do produto;
* Permitir anexar fotos do produto;
* Permitir definir a quantidade disponível em estoque.



**Descrição 2:** Como gerente, quero controlar o estoque dos produtos para evitar vender itens indisponíveis.

**Critérios de aceitação:**

* Reduzir a quantidade em estoque a cada pedido confirmado;
* Impedir a finalização de um pedido com estoque zerado;
* Alertar o gerente quando o estoque de um produto ficar abaixo de um valor mínimo.
> *Observação: o alerta aparece como destaque em vermelho na tabela de produtos.*




**Comprador(visitante)**



**Descrição 1:** Como visitante, quero pesquisar produtos pelo nome, categoria ou preço.

**Critérios de aceitação:**

* Permitir buscar produtos por palavras-chave;
* Permitir filtrar resultados por categoria (arranjos, presentes, ocasiões);
* Permitir ordenar a busca por relevância ou preço.
> *Observação: implementada apenas a busca por nome. O filtro por categoria e a ordenação por preço foram retirados do escopo; os produtos encontrados ficam destacados no catálogo.*


**Descrição 2:** Como visitante, quero visualizar os detalhes dos produtos.

**Critérios de aceitação:**

* Mostrar nome, descrição, preço e fotos do produto;
* Mostrar a disponibilidade de entrega (datas);
* Permitir calcular o frete;
> *Observação: a data prevista de entrega é definida automaticamente (dois dias após o pedido) e o frete é calculado pela região do estado (UF) na etapa de pagamento.*

**Descrição 3:** Como visitante, quero inserir os dados necessários para finalizar a compra

**Critérios de aceitação:**

* Permitir selecionar a data de entrega;
* Permitir aplicar cupom de desconto;
* Permitir criar um cadastro (informar nome, e-mail, telefone, endereço de entrega e destinatário);
* Validar o preenchimento dos dados antes do pagamento;
* Permitir escolher um método de pagamento;
> *Observações:*
> - *A data de entrega não é escolhida pelo comprador: é definida automaticamente, dois dias após o pedido, entre 08:00 e 18:00.*
> - *O cadastro guarda nome, CPF, e-mail, telefone e senha. O endereço e o destinatário são informados no momento de cada pedido, o que permite enviar presentes para endereços diferentes.*
> - *O método de pagamento foi retirado: o pagamento é feito na entrega e o pedido passa a "pago" quando é marcado como entregue.*
> - *É preciso estar logado para comprar; o visitante cria a conta antes de entrar na loja.*




**Comprador(com login)**



**Descrição 1:** Como comprador, quero acompanhar o status dos meus pedidos.

**Critérios de aceitação:**

* Permitir visualizar as etapas de envio (processando, enviado, a caminho, entregue);
* Permitir cancelar um pedido que ainda não foi enviado ou está atrasado;
* Mostrar a data prevista para entrega.
> *Observações:*
> - *As etapas implementadas são Em processamento, Enviado e Entregue, além de Cancelado. A etapa "a caminho" foi unificada com "Enviado".*
> - *O comprador pode cancelar apenas pedidos em processamento; os itens voltam ao estoque. O gerente também pode cancelar pelo painel.*
> - *Depois da entrega, o comprador pode avaliar o pedido de 1 a 5 estrelas.*


**Descrição 2:** Como comprador, quero acessar meus dados de acessos anteriores

**Critérios de aceitação:**

* Permitir acessar o histórico de compras;
* Permitir favoritar produtos;
* Permitir o preenchimento automático dos dados para entrega.
> *Observações:*
> - *Os favoritos ficam marcados nos cards do catálogo; não há tela própria de favoritos.*
> - *O preenchimento automático dos dados de entrega foi retirado, pela decisão de informar o endereço a cada pedido.*
> - *O carrinho é salvo e recuperado no próximo login.*


