package main_test

import (
	main "2924"
	"testing"
)

func TestFindChampion(t *testing.T) {
	f := func(t *testing.T, name string, n int, edges [][]int, wantchamp int) {
		t.Helper()

		t.Run(name, func(t *testing.T) {
			t.Helper()

			if got := main.FindChampion(n, edges); got != wantchamp {
				t.Errorf("unexpected champ: %v", got)
			}
		})
	}

	f(t, "example1", 3, [][]int{{0, 1}, {1, 2}}, 0)
	f(t, "example2", 4, [][]int{{0, 2}, {1, 3}, {1, 2}}, -1)
}
