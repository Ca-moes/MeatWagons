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
___
# Relatório - Projeto de Concepção e Análise de Algoritmos
## Meat Wagons (Tema 8) - Parte 1 - Truma 3 - Grupo 1
### André Gomes    up201806224@fe.up.pt
### Gonçalo Batalhao Alves    up201806451@fe.up.pt
### Pedro Jorge Fonseca Seixas    up201806227@fe.up.pt

## Descrição do Tema
Uma estabelecimento prisional necessita de gerir o transporte dos seus prisioneiros entre diferentes penitenciárias, tribunais ou esquadras, tendo ao seu dispor diferentes veiculos e sendo preciso ter em conta prisioneiros com o mesmo destino, propriedades do destino para escolher o veiculo e planeamento de rotas.
Nesta fase inicial o projeto encontra-se dividido em 3 fases.

### Fase 1 : Um veiculo para todos os prisioneiros
Tendo uma lista dos prisioneiros, e sabendo para cada um o seu destino, o objetivo desta primeira parte é ter uma camioneta com capacidade ilimitada que passe por todos os POI designados para cada prisioneiro, tendo em conta o caminho mais curto que passe em todos os POI e que depois retorne para a origem.

### Fase 2 : Diferentes Veiculos, capacidade ilimitada
Nesta fase cada Vertice do Grafo terá a informação extra sobre a sua Densidade Populacional (Cidade, Periferia ou Campo). Os prisioneiros serão previamente divididos pelos Veiculos tendo em conta o seu destino e cada veiculo estará especializado para uma Densidade Populacional. Começaremos por ter uma camioneta (Campo e Periferia) e um carro (Cidade), ambos com capacidade ilimitada, para testar a divisão dos prisioneiros e a formulação de rotas.

### Fase 3 : Mais veiculos, capacidade Limitada
Na fase final teremos uma frota de veiculos com capacidade limitada e um conjunto de prisioneiros com o seu destino. A leitura de dados inicial será para o dia, ou seja, ao executar o programa fica em memório os prisioneiros com o seu destino e a frota disponivel. Caso toda a frota esteja ocupada e ainda sobrarem prisioneiros, tendo em conta o seu destino, será retornado para a origem os veiculos necessários para refazer rotas e os transportar.

## Formalização do Problema
### Dados de Entrada
Pi - Lista de prisioneiros, sendo P(i) o i-nésimo elemento, cada um é caracterizado por:
  - ID
  - Destino

Fi - Lista de veiculos da frota, sendo F(i) o i-nésimo elemento, cada um é caracterizado por:
  - ID
  - Tipo

Gi - Grafo