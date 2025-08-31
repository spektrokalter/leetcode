package q1

func GetLeastFrequentDigit(n int) int {
	return getLeastFrequentDigit(n)
}

func getLeastFrequentDigit(n int) int {
	dict := [10]int{}
	for n != 0 {
		dict[n%10]++
		n /= 10
	}

	digit := 10
	maxfreq := 1000
	for i := 9; i >= 0; i-- {
		if dict[i] == 0 {
			continue
		}

		if dict[i] <= maxfreq {
			maxfreq = dict[i]
			digit = i
		}
	}

	return digit
}
