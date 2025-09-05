package q2

import (
	"cmp"
	"slices"
)

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

	var (
		lefttotal  = sum(left[:])
		righttotal = sum(right[:])
	)

	var out int

	for _, side := range []*['z' + 1]int{&left, &right} {
		queue := []byte("abcdefghijklmnopqrstuvwxyz")
		for true {
			slices.SortFunc(queue, func(x, y byte) int { return cmp.Compare((*side)[y], (*side)[x]) })

			var rightmost byte
			for _, c := range queue {
				if (*side)[c] != 0 {
					rightmost = c
				} else {
					break
				}
			}

			if queue[0] == rightmost || (*side)[queue[0]] == 0 || (*side)[rightmost] == 0 {
				break
			}

			(*side)[queue[0]]--
			(*side)[rightmost]--
			out++
		}
	}

	var (
		leftremains  = sum(left[:])
		rightremains = sum(right[:])
	)

	// Suppose leftremains is 12. It does not matter which way to
	// spend bb: either directly on those 12 cards, or on 12 from
	// lefttotal-leftremains, which would, in turn, free 12 cards
	// to match against leftremains.

	w := min(both, leftremains)
	both -= w
	out += w

	v := min(both, rightremains)
	both -= v
	out += v

	if both != 0 {
		restored := min(both/2, (lefttotal-leftremains)/2)
		both -= restored * 2
		out += restored
	}
	if both != 0 {
		restored := min(both/2, (righttotal-rightremains)/2)
		both -= restored * 2
		out += restored
	}

	return out
}

func sum(arr []int) (out int) {
	for _, n := range arr {
		out += n
	}
	return
}
