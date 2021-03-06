## Компоненты связности
Дан неориентированный граф. Требуется выделить компоненты связности в нем.

#### Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количество вершин и ребер графа соответственно (1≤n≤100000, 0≤m≤200000).

Следующие m строк содержат описание ребер по одному на строке. Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1≤bi,ei≤n). Допускаются петли и параллельные ребра.

#### Выходные данные
В первой строке выходного файла выведите целое число k — количество компонент связности графа. Во второй строке выведите n натуральных чисел a1,a1,…,an, не превосходящих k, где ai — номер компоненты связности, которой принадлежит i-я вершина.

## Репосты

Однажды Поликарп опубликовал в социальной сети смешную картинку с опросом про цвет своего хэндла. Многие из его друзей стали репостить шутку Поликарпа себе в ленту. Некоторые из них репостили репосты и так далее.

Эти события заданы в виде последовательности строк «name1 reposted name2» где name1 — это имя того, кто репостнул, а name2 — имя того, с чей ленты репостнули шутку. Гарантируется, что для каждой строки «name1 reposted name2» пользователь «name1» еще не имел эту шутку в свой ленте, а «name2» уже имел ее в своей ленте к моменту репоста. Поликарп зарегистрирован под именем «Polycarp», и изначально шутка есть только в его ленте.

## Топологическая сортировка
Дан ориентированный невзвешенный граф. Необходимо построить его топологическую сортирвоку.

#### Входные данные
В первой строке входного файла даны два натуральных числа n и m (1≤n≤100000, 0≤m≤100000) — число вершин и рёбер в графе соответственно. Далее в m строках перечислены рёбра графа. Каждое ребро задаётся парой чисел — номерами начальной и конечной вершин соответственно.

#### Выходные данные
Выведите любую топологическую сортировку графа в виде последовательности номеров вершин. Если граф невозможно топологически отсортировать, выведите −1.

## Очень простой поток
Дан неориентированный граф, состоящий из N вершин и M ребер.

У каждого ребра которого есть маленькая пропускная способность. Между любой парой вершин может быть больше одного ребра.

Исток находится в вершине 1, а сток в вершине N. Требуется найти максимальный поток между истоком и стоком.

#### Входные данные
В первой строке записано натуральное число N — число вершин (2 ≤ N ≤ 100).

Во второй строке записано натуральное число M — число ребер (1 ≤ M ≤ 5000).

Далее в M строках идет описание ребер. Каждое ребро задается тройкой целых чисел Ai, Bi, Ci, где Ai, Bi — номера вершин, которые соединяет ребро (), а Ci (0 ≤ Ci ≤ 20) — пропускная способность этого ребра.

#### Выходные данные
Выведите максимальный поток между вершинами с номерами 1 и N.

##  Разрез

Найдите минимальный разрез между вершинами 1 и n в заданном неориентированном графе.

#### Входные данные
На первой строке входного файла содержится n (2≤n≤100) — число вершин в графе и m (0≤m≤400) — количество ребер. На следующих m строках входного файла содержится описание ребер. Ребро описывается номерами вершин, которые оно соединяет, и его пропускной способностью (положительное целое число, не превосходящее 10000000), при этом никакие две вершины не соединяются более чем одним ребром.

#### Выходные данные
На первой строке выходного файла должны содержаться количество ребер в минимальном разрезе и их суммарная пропускная способность. На следующей строке выведите возрастающую последовательность номеров ребер (ребра нумеруются в том порядке, в каком они были заданы во входном файле).
