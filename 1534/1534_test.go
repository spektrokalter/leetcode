package main_test

import (
	main "1534"
	"testing"
)

func Test(t *testing.T) {
	f := func(t *testing.T, name string, arr []int, a, b, c, want int) {
		t.Helper()

		t.Run(name, func(t *testing.T) {
			t.Helper()

			if got := main.CountGoodTriplets(arr, a, b, c); got != want {
				t.Errorf("unexpected result: %v", got)
			}
		})
	}

	f(t, "example1", []int{3, 0, 1, 1, 9, 7}, 7, 2, 3, 4)
	f(t, "example2", []int{1, 1, 2, 2, 3}, 0, 0, 1, 0)
}
