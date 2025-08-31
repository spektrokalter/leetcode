package q2

func Score(cards []string, x byte) int { return score(cards, x) }

func score(cards []string, x byte) int {
	filtered := cards[:0]
	for _, c := range cards {
		if c[0] == x || c[1] == x {
			filtered = append(filtered, c)
		}
	}
	cards = filtered

	children := map[int][]int{}
	for i := 0; i < len(cards); i++ {
		for j := i + 1; j < len(cards); j++ {
			if compatible(cards[i], cards[j]) {
				children[i] = append(children[i], j)
				children[j] = append(children[j], i)
			}
		}
	}

	seen := make(map[int]bool, len(cards))
	seenlink := make(map[[2]int]bool, len(cards))

	var dfs func(int) int
	dfs = func(i int) int {
		seen[i] = true

		nlinks := 0
		for _, child := range children[i] {
			if !seenlink[[2]int{i, child}] {
				seenlink[[2]int{i, child}] = true
				seenlink[[2]int{child, i}] = true
				nlinks++
			}
			if !seen[child] {
				nlinks += dfs(child)
			}
		}

		return nlinks
	}

	out := 0
	for i := range cards {
		out += dfs(i) / 2
	}

	return out
}

func compatible(x, y string) bool {
	return x[0] == y[0] && x[1] != y[1] || x[1] == y[1] && x[0] != y[0]
}
