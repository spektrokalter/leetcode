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

	var both int
	var left, right ['z' + 1]int

	for _, c := range cards {
		switch {
		case c == string([]byte{x, x}):
			both++
		case c[0] == x:
			left[c[1]]++
		case c[1] == x:
			right[c[0]]++
		}
	}

	var out int

	for i := 'a'; i <= 'z'; i++ {
		for j := i + 1; j <= 'z'; j++ {
			for _, side := range []*['z' + 1]int{&left, &right} {
				if (*side)[i] != 0 && (*side)[j] != 0 {
					(*side)[i]--
					(*side)[j]--
					out++
				}
			}
		}
	}

	for i := 0; i < both; i++ {
	jloop:
		for j := 'a'; j <= 'z'; j++ {
			for _, side := range []*['z' + 1]int{&left, &right} {
				if (*side)[j] != 0 {
					(*side)[j]--
					out++
					break jloop
				}
			}
		}
	}

	return out
}
