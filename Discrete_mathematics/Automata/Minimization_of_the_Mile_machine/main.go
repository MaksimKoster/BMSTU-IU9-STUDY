package main

import (
	"fmt"
)

var k = 0

type Graph struct {
	x, depth int
	parent *Graph
}

func (x *Graph) find () *Graph {
	if x.parent == x {
		return x
	} else {
		return x.parent.find()
	}
}

func (x *Graph) union (y *Graph){
	X := x.find()
	Y := y.find()
	if X.depth < Y.depth {
		X.parent = Y
	} else {
		Y.parent = X
		if X.depth == Y.depth && X != Y {
			X.depth++
		}
	}
}

type MiliAutomate struct {
	D [][] int
	F [][] string
	n, m , q int
	renumeration []int
}

func (automat *MiliAutomate) dfs(begin int) {
	automat.renumeration[begin] = k
	k++
	for _, v := range automat.D[begin] {
		if automat.renumeration[v] == -1 {
			automat.dfs(v)
		}
	}
}

func (automat *MiliAutomate) canonicalNumbering() MiliAutomate{
	k = 0
	automat.dfs(automat.q)
	var y = MiliAutomate{ n: k, m: automat.m, q: 0,}
	y.initialization()
	for i := 0; i < automat.n; i++ {
		if automat.renumeration[i] != -1 {
			y.F[automat.renumeration[i]] = automat.F[i]
			for j := 0; j < automat.m; j++ {
				y.D[automat.renumeration[i]][j] = automat.renumeration[automat.D[i][j]]
			}
		}
	}
	return y
}

func (automat *MiliAutomate) print() {
	fmt.Println("digraph {\n\trankdir = LR\n\tdummy [label = \"\", shape = none]")
	for i := 0; i < automat.n; i++ {
		fmt.Printf("\t%d [shape = circle]\n", i)
	}
	fmt.Printf("\tdummy -> %d\n", automat.q)
	for i := 0; i < automat.n; i++ {
		for j := 0; j < automat.m; j++ {
			fmt.Printf("\t%d -> %d [label = \"%s(%s)\"]\n",i , automat.D[i][j], string(rune(j + 'a')), automat.F[i][j])
		}
	}
	fmt.Println("}")
}



func split1 (automat* MiliAutomate) (m int , pi []int){
	pi = make([] int, automat.n)
	m = automat.n
	Q := make([]Graph, automat.n)
	for i := 0; i < automat.n; i++{
		Q[i]= Graph{i, 0, &Q[i]}
	}
	for i := 0; i < automat.n; i++{
		for j := 0; j < automat.n; j++{
			if Q[i].find() != Q[j].find(){
				eq := true
				for k := 0; k < automat.m; k++ {
					if automat.F[i][k] != automat.F[j][k]{
						eq = false
						break
					}
				}
				if eq {
					Q[i].union(&Q[j])
					m--
				}
			}
		}
	}
	for i := 0; i < automat.n; i++{
		pi[i] = Q[i].find().x
	}
	return m, pi
}

func split (automat *MiliAutomate, pi []int) (m int){
	m = automat.n
	Q := make([]Graph, automat.n)
	for i := 0; i < automat.n; i++{
		Q[i]= Graph{i, 0 , &Q[i]}
	}
	for i := 0; i < automat.n; i++{
		for j := 0; j < automat.n; j++{
			if pi[i] == pi[j] && Q[i].find() != Q[j].find(){
				eq := true
				for k := 0; k < automat.m; k++ {
					w1, w2 := automat.D[i][k], automat.D[j][k]
					if pi[w1] != pi[w2] {
						eq = false
						break
					}
				}
				if eq {
					Q[i].union(&Q[j])
					m--
				}
			}
		}
	}
	for i := 0; i < automat.n; i++{
		pi[i] = Q[i].find().x
	}
	return m
}

func (automat *MiliAutomate) initialization() {

	automat.D = make([][] int, automat.n)
	automat.F = make([][] string, automat.n)
	automat.renumeration = make([]int, automat.n)

	for i := 0; i < automat.n; i++ {
		automat.D[i] = make([] int, automat.m)
		automat.F[i] = make([] string, automat.m)
		automat.renumeration[i] = -1
	}
}

func (automat *MiliAutomate) getData() {
	for i := 0; i < automat.n; i++ {
		for j := 0; j < automat.m; j++ {
			fmt.Scan(&automat.D[i][j])
		}
	}
	for i := 0; i < automat.n; i++ {
		for j := 0; j < automat.m; j++ {
			fmt.Scan(&automat.F[i][j])
		}
	}
}

func (automat *MiliAutomate) minimization() MiliAutomate{
	var x = AufenkampHohn(automat)
	return x.canonicalNumbering()
}

func AufenkampHohn(automat* MiliAutomate) MiliAutomate{
	m, pi := split1(automat)
	for {
		ml := split(automat,pi)
		if m == ml{
			break
		}
		m = ml
	}
	used := make([] bool, automat.n)
	var NewMachine = *automat
	for i := 0; i < automat.n; i++ {
		ql := pi[i]
		if !used[ql] {
			used[ql] = true
			for j := 0; j < automat.m; j++ {
				NewMachine.D[ql][j] = pi[automat.D[i][j]]
				NewMachine.F[ql][j] = automat.F[i][j]
			}
		}
	}

	for i := 0; i < automat.n; i++ {
		if !used[i]{
			for j := 0; j < automat.m; j++ {
				NewMachine.D[i][j] = i
			}
		}
	}
	return NewMachine
}

func  main() {

	var n, m, q int
	fmt.Scan(&n, &m, &q)

	var X = MiliAutomate{ n: n, m: m, q: q,}
	X.initialization()

	X.getData()

	var NewX = X.canonicalNumbering()
	var NewAtoma = NewX.minimization()
	NewAtoma.print()
}

