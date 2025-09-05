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

	var middle int
	var (
		top    = map[byte]int{}
		bottom = map[byte]int{}
	)

	for _, c := range cards {
		switch {
		case c == string([]byte{x, x}):
			middle++
		case c[0] == x:
			top[c[1]]++
		case c[1] == x:
			bottom[c[0]]++
		}
	}

	var (
		toptotal    = sum(top)
		bottomtotal = sum(bottom)
	)

	var out int

	for _, side := range []map[byte]int{top, bottom} {
		queue := []byte("abcdefghijklmnopqrstuvwxyz")
		for true {
			slices.SortFunc(queue, func(x, y byte) int { return cmp.Compare(side[y], side[x]) })

			var rightmost byte
			for _, c := range queue {
				if side[c] != 0 {
					rightmost = c
				} else {
					break
				}
			}

			if queue[0] == rightmost || side[queue[0]] == 0 || side[rightmost] == 0 {
				break
			}

			side[queue[0]]--
			side[rightmost]--
			out++
		}
	}

	var (
		toporphans    = sum(top)
		bottomorphans = sum(bottom)
	)

	pairedorphans := min(middle, toporphans)
	middle -= pairedorphans
	out += pairedorphans

	pairedorphans = min(middle, bottomorphans)
	middle -= pairedorphans
	out += pairedorphans

	pairs := min(middle/2, (toptotal-toporphans)/2)
	middle -= pairs * 2
	out += pairs

	pairs = min(middle/2, (bottomtotal-bottomorphans)/2)
	middle -= pairs * 2
	out += pairs

	return out
}

func sum(arr map[byte]int) (out int) {
	for _, n := range arr {
		out += n
	}
	return
}
