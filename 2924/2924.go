package main

func FindChampion(n int, edges [][]int) int {
	return findChampion(n, edges)
}

func findChampion(n int, edges [][]int) int {
	parents := map[int]int{}
	for _, e := range edges {
		parents[e[1]]++
	}

	champ := 0
	roots := 0
	for i := range n {
		if parents[i] == 0 {
			roots++
			champ = i
		}
		if roots > 1 {
			return -1
		}
	}

	return champ
}
