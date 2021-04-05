package main

import (
"fmt"
)

var k = 0

type MiliAutomate struct {
	D [][] int
	F [][] string
	n, m , q int
	renumeration []int
}

func (a *MiliAutomate) dfs(begin int) {
	a.renumeration[begin] = k
	k++
	for _, v := range a.D[begin] {
		if a.renumeration[v] == -1 {
			a.dfs(v)
		}
	}
}

func (x *MiliAutomate) canonical_numbering() MiliAutomate{

	var y = MiliAutomate{ n: k, m: x.m, q: x.q,}
	y.initialization()

	for i := 0; i < x.n; i++ {
		if x.renumeration[i] != -1 {
			y.F[x.renumeration[i]] = x.F[i]
			for j := 0; j < x.m; j++ {
				y.D[x.renumeration[i]][j] = x.renumeration[x.D[i][j]]
			}
		}
	}
	return y
}

func (a *MiliAutomate) initialization() {

	a.D = make([][] int, a.n)
	a.F = make([][] string, a.n)
	a.renumeration = make([]int, a.n)

	for i := 0; i < a.n; i++ {
		a.D[i] = make([] int, a.m)
		a.F[i] = make([] string, a.m)
		a.renumeration[i] = -1
	}
}

func (a *MiliAutomate) creation() {
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

func (a *MiliAutomate) print() {
	fmt.Print(k, "\n", a.m, "\n", 0, "\n")
	for i := 0; i < a.n; i++ {
		for j := 0; j < a.m; j++ {
			fmt.Print(a.D[i][j], " ")
		}
		fmt.Println()
	}
	for i := 0; i < a.n; i++ {
		for j := 0; j < a.m; j++ {
			fmt.Print(a.F[i][j], " ")
		}
		fmt.Println()
	}
}

func  main() {

	var n, m, q int

	fmt.Scan(&n, &m, &q)

	var X = MiliAutomate{ n: n, m: m, q: q,}
	X.initialization()

	X.creation()

	X.dfs(X.q)

	var ans = X.canonical_numbering()
	ans.print()
}
