package main

import (
	"fmt"
)

type MealyAutomate struct {
	D [][] int
	F [][] string
	k, n, m , q int
	In, Out [] string
}

type pair struct {
	x      int
	result string
}

type pair_status struct {
	x, y int
	state bool
}

func (a *MealyAutomate) getAlphabet(){
	fmt.Scan(&a.m)

	a.In = make([]string, a.m)
	for i := 0; i < a.m; i++ {
		fmt.Scan(&a.In[i])
	}

	fmt.Scan(&a.k)

	a.Out = make([]string, a.k)
	for i := 0; i < a.k; i++ {
		fmt.Scan(&a.Out[i])
	}

}

func (a *MealyAutomate) initialization() {

	a.getAlphabet()

	fmt.Scan(&a.n)

	a.D = make([][] int, a.n)
	a.F = make([][] string, a.n)

	for i := 0; i < a.n; i++ {
		a.D[i] = make([] int, a.m)
		a.F[i] = make([] string, a.m)
	}
}

func (a *MealyAutomate) creation() {
	for i := 0; i < a.n; i++ {
		for j := 0; j < a.m; j++ {
			fmt.Scan(&a.D[i][j])
		}
	}

	for i := 0; i < a.n; i++ {
		for j := 0; j < a.m; j++ {
			fmt.Scan(&a.F[i][j])
		}
	}
}

func (a *MealyAutomate) convertToMoore() {
	map_pairs := make(map[pair]pair_status)

	fmt.Printf("digraph {\n\trankdir = LR\n")
	k := 0
	for i := 0; i < a.n; i++ {
		for j := range a.In {
			var x = pair{ a.D[i][j],  a.F[i][j]}
			if _, condition := map_pairs[x]
				!condition{
				fmt.Printf("\t%d [label = \"(%d,%s)\"]\n", k, a.D[i][j], a.F[i][j])
				map_pairs[x] = pair_status{ k, 1 ,true}
				k++
			}
		}
	}

	for i := 0; i < a.n; i++ {
		for j := range a.Out {
			var x = pair{x: i, result: a.Out[j]}
			if (map_pairs[x].state) || (map_pairs[x].y == 1){
				for pos := range a.In {
					fmt.Printf("\t%d -> %d [label = \"%s\"]\n", map_pairs[x].x, map_pairs[pair{x: a.D[i][pos],result: a.F[i][pos]}].x, a.In[pos])
				}
				map_pairs[x] = pair_status{map_pairs[x].x, 0,  false}
			}
		}
	}
	fmt.Println("}")
}

func  main() {

	var X = MealyAutomate{}

	X.initialization()

	X.creation()

	X.convertToMoore()
}