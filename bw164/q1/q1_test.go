package q1_test

import (
	"bw164/q1"
	"testing"
)

func Test(t *testing.T) {
	f := func(name string, n, want int) {
		t.Helper()

		t.Run(name, func(t *testing.T) {
			t.Helper()

			if got := q1.GetLeastFrequentDigit(n); got != want {
				t.Errorf("unexpected value: %v", got)
			}
		})
	}

	f("example1", 1553322, 1)
	f("example2", 723344511, 2)
}
