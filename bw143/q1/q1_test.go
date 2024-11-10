package q1_test

import (
	"bw143/q1"
	"testing"
)

func TestExample(t *testing.T) {
	f := func(t *testing.T, name string, n, T, want int) {
		t.Helper()

		t.Run(name, func(t *testing.T) {
			t.Helper()

			if got := q1.SmallestNumber(n, T); got != want {
				t.Errorf("unexpected number: %v", got)
			}
		})
	}

	f(t, "example-1", 10, 2, 10)
	f(t, "example-2", 15, 3, 16)
}
