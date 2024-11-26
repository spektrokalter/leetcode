package main

func FindChampion(n int, edges [][]int) int {
	return findChampion(n, edges)
}

func findChampion(n int, edges [][]int) int {
	parent := map[int][]int{}
	for _, e := range edges {
		parent[e[1]] = append(parent[e[1]], e[0])
	}

	var roots []int
	for i := range n {
		if parent[i] == nil {
			roots = append(roots, i)
		}
	}

	if len(roots) > 1 {
		return -1
	}

	return roots[0]
}
