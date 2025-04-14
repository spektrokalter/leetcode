package main

func CountGoodTriplets(arr []int, a, b, c int) int {
	return countGoodTriplets(arr, a, b, c)
}

func countGoodTriplets(arr []int, a, b, c int) int {
	abs := func(n int) int {
		return map[bool]int{
			true:  -n,
			false: n,
		}[n < 0]
	}

	num := 0

	for t := range triplets(arr) {
		if abs(arr[t[0]]-arr[t[1]]) <= a &&
			abs(arr[t[1]]-arr[t[2]]) <= b &&
			abs(arr[t[0]]-arr[t[2]]) <= c {

			num++
		}
	}

	return num
}

func triplets(arr []int) chan [3]int {
	ch := make(chan [3]int)

	go func() {
		for i := 0; i < len(arr); i++ {
			for j := i + 1; j < len(arr); j++ {
				for k := j + 1; k < len(arr); k++ {
					ch <- [3]int{i, j, k}
				}
			}
		}

		close(ch)
	}()

	return ch
}
