package q2_test

import (
	"bw143/q2"
	"testing"
)

func TestMaxFrequency(t *testing.T) {
	f := func(t *testing.T, name string, nums []int, k, operations, want int) {
		t.Helper()

		t.Run(name, func(t *testing.T) {
			t.Helper()

			if got := q2.MaxFrequency(nums, k, operations); got != want {
				t.Errorf("unexpected frequency: %v", got)
			}
		})
	}

	f(t, "example-1", []int{1, 4, 5}, 1, 2, 2)
	f(t, "example-2", []int{5, 11, 20, 20}, 5, 1, 2)
	f(t, "azat-1", []int{8, 10, 10, 10, 98, 100, 100, 100, 100}, 2, 10, 5)
	f(t, "azat-2", []int{2, 4, 6, 8, 100, 102, 104, 106, 108}, 2, 10, 5)
	f(t, "azat-3", []int{108, 106, 104, 102, 100, 8, 6, 4}, 2, 10, 5)
	f(t, "wronganswer-1", []int{35, 94, 32}, 37, 2, 2)
	f(t, "wronganswer-2", []int{37, 30, 37}, 26, 1, 3)
	f(t, "wronganswer-3", []int{58, 80, 5}, 58, 2, 3) // wrongalgo-1 couldn't handle this
	f(t, "wronganswer-4", []int{2}, 7, 0, 1)
	f(t, "wronganswer-5", []int{1, 90}, 76, 1, 1)
	f(t, "wronganswer-6", []int{94, 10, 92}, 0, 3, 1)      // fixes "integer divide by zero"
	f(t, "wronganswer-7", []int{22, 32, 74, 90}, 39, 4, 4) // focusing on existing numbers couldn't handle this
}
