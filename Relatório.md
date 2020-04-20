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
Tendo uma lista dos prisioneiros, e sabendo para cada um o seu destino, o objetivo desta primeira parte é ter um autocarro com capacidade ilimitada que passe por todos os POI designados para cada prisioneiro, tendo em conta o caminho mais curto que passe em todos os POI e que depois retorne para a origem.
Certas vias podem ser inacessíveis por razões diversas (obras, cortes de estrada, largura de rua não ser suficiente). Assim, durante o processamento do grafo será necessário desprezar certas arestas.

### Fase 2 : Diferentes Veiculos, capacidade ilimitada
Nesta fase cada Vértice do Grafo terá a informação extra sobre a sua Densidade Populacional (Cidade, Periferia ou Campo). Os prisioneiros serão previamente divididos pelos Veiculos tendo em conta o seu destino e cada veiculo estará especializado para uma Densidade Populacional. Começaremos por ter uma camioneta (Campo e Periferia) e um carro (Cidade), ambos com capacidade ilimitada, para testar a divisão dos prisioneiros e a formulação de rotas.

### Fase 3 : Mais veiculos, capacidade Limitada
Na fase final teremos uma frota de veiculos com capacidade limitada e um conjunto de prisioneiros com o seu destino. A leitura de dados inicial será para o dia, ou seja, ao executar o programa fica em memório os prisioneiros com o seu destino e a frota disponivel. Caso toda a frota esteja ocupada e ainda sobrarem prisioneiros, tendo em conta o seu destino, será retornado para a origem os veiculos necessários para refazer rotas e os transportar.

## Possiveis Problemas a Encontrar
- Leitura dos mapas proveninentes do Open Street Maps
- Peso das arestas do grafo
- Conversão dos dados de modo a possibilitar a utilização do GraphViewer
- Cruzamento de ruas com o mesmo nome
- Acentuação nos nomes das ruas
- Nos ficheiros de mapas não são disponibilizadas tags referentes a tribunais ou estabelecimentos prisionais
- distribuição de tag densidade populacional pelos vertices do grafo 

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

#### Função Objetivo
Diminuir a distância total percorrida pela frota que será a soma dos valores das arestas percorridas por cada veículo.

## Perspetiva de solução
### Fase 1
Esta primeira fase terá varios passos referentes á preparação do ambiente de trabalho, começando pela:

#### 1. Preparação dos ficheiros de entrada
Serão utilizados os ficheiros de nodes e edges fornecidos pelos professores. A informação lida dos ficheiros será guardada num grafo G. Será criada uma tag para cada tipo de edifício de interesse (prisões, esquadras e tribunais) de forma a facilitar a identificação dos pontos de interesse.
#### 2. Analise da Conectividade do Grafo
Para verificar as ruas que estão inacessiveis
#### 3. Criação de POI's
Após a leitura dos ficheiros com os nodes e edges, serão lidos os ficheiros das tags de forma a identificar os pontos de interesse, alterando, para esse node, a sua variável type, inicializada a 0, para o seu valor correspondente ao tipo de ponto de interesse.

Assim que a preparação estiver pronta é possivel seguir para a implementação de código. Nesta fase será necessário que o programa consiga criar 2 rotas, uma de ida e outra de volta.

Para a Rota de ida será usado o algoritmo de Dijkstra:

| DIJKSTRA(G, s): // G=(V,E), s in V  | BIDIRECTIONAL DIJKSTRA(G, s): <br> |
|--------------|-----------------|
|     1. for each v in V do<br>    2. &emsp;dist(v) <- INF<br>    3. &emsp;path(v) <- nil<br>    4. dist(s) <- 0<br>    5. Q <- 0 // min-priority queue<br>    6. INSERT(Q, (s, 0)) // inserts s with key 0<br>    7. while Q != 0 do<br>    8. &emsp;v <- EXTRACT-MIN(Q) <br>    9. &emsp;for each w in Adj(v) do<br>    10.&emsp;&emsp;if dist(w) > dist(v) + weight(v,w) then<br>    11.&emsp;&emsp;&emsp;dist(w) <- dist(v)+ weight(v,w)<br>    12.&emsp;&emsp;&emsp;path(w) <- v<br>    13.&emsp;&emsp;&emsp;if w not in Q then <br>    14.&emsp;&emsp;&emsp;&emsp;INSERT(Q, (w, dist(w)))<br>    15.&emsp;&emsp;&emsp;else<br>    16.&emsp;&emsp;&emsp;&emsp;DECREASE-KEY(Q, (w, dist(w))) | A COMPLETAR                                          |

da seguinte forma: Começando no estabelecimento prisional onde se encontram os prisioneiros é usado o algoritmo até encontrar um vértice que é uma paragem de um dos prisioneiros. Neste ponto é usado outra vez o algoritmo de Dijkstra mas com o vértice encontrado a ser usado como vértice de inicio para encontrar a próxima paragem. Assim que todos os prisioneiros estiverem distribuidos será necessário encontrar o caminho de volta. Para isso é aplicado o algoritmo de Dijkstra Bi-Direcional para encontrar o caminho mais curto entre o Vértice final do passo anterior e o estabelecimento prisional inicial.

## ALGORITMO A*
```
function reconstruct_path(cameFrom, current)
    total_path := {current}
    while current in cameFrom.Keys:
        current := cameFrom[current]
        total_path.prepend(current)
    return total_path

// A* finds a path from start to goal.
// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
function A_Star(start, goal, h)
    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    openSet := {start}

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    // to n currently known.
    cameFrom := an empty map

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    gScore := map with default value of Infinity
    gScore[start] := 0

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how short a path from start to finish can be if it goes through n.
    fScore := map with default value of Infinity
    fScore[start] := h(start)

    while openSet is not empty
        // This operation can occur in O(1) time if openSet is a min-heap or a priority queue
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        for each neighbor of current
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := gScore[neighbor] + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)

    // Open set is empty but goal was never reached
    return failure
```
### Fase 2
Na segunda fase teremos em conta o valor de densidade populacional (DP) dos vértices e 2 veículos, cada um especializado para os seus valores de DP. Iso leva-nos a 3 formas de encontrar o caminho mais curto, tendo em conta uma divisão prévia dos prisioneiros:

#### Hipótese 1 - Não tendo em conta o caminho
Como primeira hipótese considera-se apenas a DP dos destinos de cada um dos prisioneiros. Tendo isso em conta é feita uma divisão em dois grupos baseado no DP do destino de cada prisioneiro. Um grupo será levado por um carro (com capacidade infinita) para destinos com DP de *cidade* enquanto que o outro grupo será levado por um autocarro (também com capacidade infinita) para destinos com DP de *periferia* ou *campo*.
Feita a divisão o problema simplifica-se a aplicar o método da fase 1 para cada veículo.

#### Hipótese 2 - Tendo em conta o caminho
Nesta Hipótese, que à primeira vista parece mais precisa, será feito no inicio o cálculo de uma rota como na fase 1 para todos os prisioneiros. A partir do processamento da rota, cada prisioneiro ficará com o valor de cada DP dos vértices pela qual passou. Tendo em conta o DP máximo de cada prisioneiro fazem-se as divisões em 2 grupos e segue-se como na hipótese anterior para a divisão nos veiculos e calculo de rotas.
A contagem dos DP para cada prisioneiro terá em conta apenas a rota inicial e não as rotas criadas pelos veiculos a qual ficaram designados, isto poderá não trazer os melhores resultados quanto á divisão dos prisioneiros entre veiculos mas é uma melhoria face à hipótese anterior.

#### Hipótese 3 - Apenas considerando os vértices onde o veículo pode transportar
Nesta hipótese consideram-se diferentes tipos de veículo para transportar em *cidade* ou nao. Quando são selecionados veículos que não estão aptos para transportar prisioneiros em cidades, o grafo será filtrado, removendo temporariamente todos os vértices em que a densidade populacional corresponde a uma cidade, de forma a que encontre o caminho mais curto apenas passando por vértices com DP de *campo* ou *periferia*. Desta forma, será descoberto o caminho mais curto para cada tipo de veículo.

### Fase 3

A diferença principal desta fase para a anterior é o limite em cada veiculo, com isso em conta, para esta fase adotamos os mesmos passos da hipótese 2 da fase 2 até à divisão dos prisioneiros pelos veiculos, mas neste caso teremos que fazer um cálculo do resto de prisioneiros caso não haja transporte para todos. Caso haja transporte para todos o problema torna-se igual á fase 2. Em caso contrário faz-se um cálculo dos veiculos que terão de retornar ao estabelecimento prisional inicial tendo em conta a sua capacidade, o número de prisioneiros e o grupo à qual os prisioneiros restantes estão designados.
Assim que este cálculo for realizado repete-se este método a partir do ponto em que se calcula o resto dos prisioneiros.

## Casos de utilização
Será implementado um pequeno menu, muito intuitivo, para indicar os prisioneiros a ser transportados nesse dia, bem como o ponto de origem e, para cada um, o destino, dentro de uma lista previamente extraída do conjunto de pontos de interesse, constituida pelos tribunais, prisões e esquadras. Será também possivél visualizar o grafo com o percurso através do GraphViewer para cada um dos prisioneiros.

## Funcionalidade a implementar
Uma possível funcionalidade a implementar seria diferenciar os veículos, não só pela capacidade mas também pela sua segurança, podendo selecionar a importância do prisioneiro e escolher o tipo de veículo.

## Conclusão
Temos um plano traçado e bem dividido, esperamos que na altura da implementação consigamos tratar de forma eficiente de todas as partes, principalmente do uso da parte gráfica de criação de grafos, visto que será a primeira vez neste curso que faremos uso de algo semelhante.

<img src="https://media.giphy.com/media/3owyphXV8TcO2muXGU/giphy.gif" width="550" height="300" />
