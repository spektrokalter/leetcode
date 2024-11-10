package q1

func SmallestNumber(n, t int) int {
	return smallestNumber(n, t)
}

func product(n int) int {
	p := 1
	for n != 0 {
		p *= n % 10
		n /= 10
	}
	return p
}

func smallestNumber(n, t int) int {
	for i := n; true; i++ {
		if p := product(i); p % t == 0 {
			return i
		}
	}

	panic(0)
}
