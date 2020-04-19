# Notes

- Objetivo : Otimizar percursos dos veiculos.
- Tipos de veiculos :
  - Camioneta - para levar mais prisioneiros de cada vez 
  - Carro - Para usar em zonas de maior densidade populacional
- Nota : 
  - Pode ocorrer obras na via pública, necessário mudar percurso;
  - Usar mapas reais.
- Prisioneiro : Nome, ID, local de origem, local de destino
- Veiculo : Quantidade que consegue levar, apto para zonas urbanas (bool)

Quais são os pontos (vértices) de interesse aka POI?
  - prisões
  - esquadras
  - tribunais

## Iterações/Estados

Estado inicial:
  - Uma Camioneta para todos os serviços

Estado 2:
  - Diferentes veiculos, capacidades diferentes
  - (Ideia: Destino é mais importante, caso destino seja em cidade, usar carro, else usar camioneta)

Estado 3:
  - Obras na via pública


♦ **Estabelecimento prisional** é uma unidade estrutural-funcional instalada em edificação, dirigida por polícia prisional e respetiva cadeia de comando do Estado, onde cidadãos são colocados e mantidos privados de liberdade, seja por força de ordem de prisão preventiva, em fase de pré-julgamento, seja em cumprimento de pena de prisão a que foram condenados por sentença dum tribunal criminal;

♦ **Penitenciária** é um estabelecimento prisional onde cidadãos cumprem penas de prisão a que foram condenados por sentença dum tribunal criminal;

♦ **Cárcere** é uma cela individual ou coletiva dentro dum estabelecimento prisional. 

♦ **Cárcere privado** é a privação dolosa da liberdade de um cidadão por outro fora de estabelecimento prisional por iniciativa privada, além de certo número de horas – constitui crime punível.

♦ **Prisão** é qualquer uma destas coisas.

in Ciberdúvidas da Língua Portuguesa, https://ciberduvidas.iscte-iul.pt/consultorio/perguntas/estabelecimento-prisional-penitenciaria-carcere-e-prisao/34536 [consultado em 19-04-2020]
___
# Relatório - Projeto de Concepção e Análise de Algoritmos
## Meat Wagons (Tema 8) - Parte 1
### Turma 3 - Grupo 1
### André Gomes - up201806224@fe.up.pt
### Gonçalo de Batalhão Alves - up201806451@fe.up.pt
### Pedro Jorge Fonseca Seixas - up201806227@fe.up.pt

## Descrição do Tema
Uma estabelecimento prisional necessita de gerir o transporte dos seus prisioneiros entre diferentes penitenciárias, tribunais, estabelecimentos prisionais ou esquadras policiais, tendo ao seu dispor diferentes veiculos e sendo preciso ter em conta prisioneiros com o mesmo destino, propriedades do destino para escolher o veiculo e planeamento de rotas.

O objetivo é desenvolver um programa que calcule para o dia as rotas a tomar para cada veículo da frota tendo em conta os destinos do dia para a lista de prisioneiros.

Nesta fase inicial o projeto encontra-se dividido em 3 fases.

### Fase 1 : Um veiculo para todos os prisioneiros
Tendo uma lista dos prisioneiros, e sabendo para cada um o seu destino, o objetivo desta primeira parte é ter um autocarro com capacidade ilimitada que passe por todos os POI designados para cada prisioneiro (Travelling salesman problem), tendo em conta o caminho mais curto que passe em todos os POI e que depois retorne para a origem.
Certas vias podem ser inacessíveis por razões diversas (obras, cortes de estrada, largura de rua não ser suficiente). Assim, durante o processamento do grafo será necessário desprezar certas arestas.

### Fase 2 : Diferentes Veiculos, capacidade ilimitada
Nesta fase cada Vértice do Grafo terá a informação extra sobre a sua Densidade Populacional (Cidade, Periferia ou Campo). Os prisioneiros serão previamente divididos pelos Veiculos tendo em conta o seu destino e cada veiculo estará especializado para uma Densidade Populacional. Começaremos por ter uma camioneta (Campo e Periferia) e um carro (Cidade), ambos com capacidade ilimitada, para testar a divisão dos prisioneiros e a formulação de rotas.

### Fase 3 : Mais veiculos, capacidade Limitada
Na fase final teremos uma frota de veiculos com capacidade limitada e um conjunto de prisioneiros com o seu destino. A leitura de dados inicial será para o dia, ou seja, ao executar o programa fica em memório os prisioneiros com o seu destino e a frota disponivel. Caso toda a frota esteja ocupada e ainda sobrarem prisioneiros, tendo em conta o seu destino, será retornado para a origem os veiculos necessários para refazer rotas e os transportar.

## Formalização do Problema
### Dados de Entrada
Pi - Lista de prisioneiros com destinos para o dia, sendo P(i) o i-nésimo elemento, cada um é caracterizado por:
- ID - número identificador de prisioneiro
- Destino - número identificador de destino

O número identificador de destino terá duas partes, a primeira parte de 1 digito é correspondente ao tipo de destino e a segunda parte de 3 digitos é correspondente ao destino concreto de um certo tipo. Como exemplo: Um tribunal poderá ter um Destino de 1001 enquanto que um estabelecimento prisional poderá ter um Destino de 2001.

Fi - Lista de veiculos da frota, sendo F(i) o i-nésimo elemento, cada um é caracterizado por:
- ID - número identificador do veículo (tal como em Destino, será um numero que terá implicito o tipo de veiculo)
- cap - número de assentos destinados a prisioneiros

Gi = (Vi, Ei) - Grafo Dirigido Pesado (Dirigido -> sentido da rua|Pesado -> Distância entre vértices)
- V - vértices representativos de pontos da cidade com:
  - type - Penitenciária, tribunal, esquadra policial ou estabelecimento prisional (cada um terá um ID igual a Destino)(Caso não seja nenhum desses, ID = 0)
  - dens - Informação sobre densidade populacional (Cidade, Periferia ou Campo)
  - Adj ⊆ E ‐ conjunto de arestas que partem do vérce
- E - arestas representativas das vias de comunicação
  - w - peso da aresta a (representa a distância entre os dois vérces que a delimitam)
  - ID - identificador único da aresta
  - dest ∈ Vi ‐ vértice de destino
  
S ∈ Vi ‐ vértice inicial (Estabelecimento prisional)

T ⊆ Vi ‐ vértices finais (Destinos)


### Dados de Saída

Gf = (Vf,Ef) grafo dirigido pesado, tendo Vf e Ef os mesmos atributos que Vi e Ei.

Ff‐ Lista ordenada de todos os veiculos usados, sendo Ff(i) o seu i‐ésimo elemento.
Cada um tem os seguintes valores:
- cap ‐ número de assentos utilizados
- P = {e ∈ Ei | 1 ≤ j ≤ |P|} ‐ sequência ordenada (com repetidos) de arestas a visitar, sendo ej o seu j‐ésimo elemento.

### Restrições
#### Sobre os Dados de entrada
- ∀ i ∈ [1 ; |Cf| ], cap(Cf[i]) >= 0, dado que uma capacidade representa os assentos usadas, caso um veiculo não seja usado, cap = 0;
- ∀ v ∈ Vi, type ≥ 0;
- ∀ e ∈ Ei, w > 0, dado que o peso de uma aresta representa uma distância entre
pontos de um mapa.
- ∀ e ∈ Ei, e deve ser utilizável pelo elemento da frota. Senão, não é incluída no grafo Gi.

#### Sobre os Dados de Saída
No grafo Gf:
- ∀ vf ∈ Vf, ∃ vi ∈ Vi tal que vi e vf têm os mesmos valores para todos os atributos
- ∀ ef ∈ Ef, ∃ ei ∈ Ei tal que ei e ef têm os mesmos valores para todos os atributos.


#### Na Sequência P

### Funções Objetivo

### Perspetiva de solução