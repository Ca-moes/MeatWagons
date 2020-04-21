Notes

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

Info sobre Dijkstra e Traveling Salesman Problem : http://www.gitta.info/Accessibiliti/en/html/unit_Dijkstra.html

```
BiDirectional Dijkstra:
1. Qi.Insert(x1) and mark xi as visited
2. Qg.Insert(xg) and mark xg as visited
3. **while** Qi not empty **and** Qg not empty **do**
4.   **if** Qi not empty
5.     x <- Qi.GetFirst()
6.     **if** x = xg **or** x ∈ Qg
```

| DIJKSTRA(G, s): // G=(V,E), s in V  | BIDIRECTIONAL DIJKSTRA(G, s): <br> |
|--------------|-----------------|
|     1. **for** each v **in** V do<br>    2. &emsp;dist(v) <- INF<br>    3. &emsp;path(v) <- nil<br>    4. dist(s) <- 0<br>    5. Q <- 0 // min-priority queue<br>    6. INSERT(Q, (s, 0)) // inserts s with key 0<br>    7. **while** Q != 0 do<br>    8. &emsp;v <- EXTRACT-MIN(Q) <br>    9. &emsp;**for** each w **in** Adj(v) do<br>    10.&emsp;&emsp;**if** dist(w) > dist(v) + weight(v,w) **then**<br>    11.&emsp;&emsp;&emsp;dist(w) <- dist(v)+ weight(v,w)<br>    12.&emsp;&emsp;&emsp;path(w) <- v<br>    13.&emsp;&emsp;&emsp;**if** w not in Q **then** <br>    14.&emsp;&emsp;&emsp;&emsp;INSERT(Q, (w, dist(w)))<br>    15.&emsp;&emsp;&emsp;**else**<br>    16.&emsp;&emsp;&emsp;&emsp;DECREASE-KEY(Q, (w, dist(w))) | 1. Qi.Insert(x1) and mark xi as visited<br> 2. Qg.Insert(xg) and mark xg as visited<br> 3. **while** Qi not empty **and** Qg not empt **do** <br> 4.&emsp;**if** Qi not empty <br> 5.&emsp;&emsp;x <- Qi.GetFirst() <br> 6.&emsp;&emsp;**if** x = xg **or** x ∈ Qg <br> 7.&emsp;&emsp;&emsp;&emsp;**return** SUCCESS <br> 8.&emsp;&emsp;**forall** u ∈ U(x) <br> 9. &emsp; &emsp;&emsp;x' <- f(x,u) <br> 10.&emsp;&emsp;&emsp;**if** x' not visited <br> 11.&emsp;&emsp;&emsp;&emsp;Mark x' as visited <br> 12.&emsp;&emsp;&emsp;&emsp;Qi.Insert(x') <br> 13.&emsp;&emsp;&emsp;**else** <br> 14.&emsp;&emsp;&emsp;&emsp;Resolve duplicate x' <br> 15.&emsp;**if** Qg not empty <br> 16.&emsp;&emsp;x' <- Q.GetFirst() <br> 17.&emsp;&emsp;**if** x' = xi **or** x' ∈ Qi <br> 18.&emsp;&emsp;&emsp;&emsp;**return** SUCCESS <br> 19.&emsp;&emsp;**forall** u^(-1) ∈ U^(-1)(x') <br> 20. &emsp; &emsp;&emsp;x <- f^(-1)(x',u^(-1)) <br> 21.&emsp;&emsp;&emsp;**if** x not visited <br> 22.&emsp;&emsp;&emsp;&emsp;Mark x as visited <br> 23.&emsp;&emsp;&emsp;&emsp;Qg.Insert(x) <br> 24.&emsp;&emsp;&emsp;**else** <br> 25.&emsp;&emsp;&emsp;&emsp;Resolve duplicate x <br> 26. **return** FAILURE