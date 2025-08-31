package q2_test

import (
	"bw164/q2"
	"testing"
)

func Test(t *testing.T) {
	f := func(name string, cards []string, x byte, want int) {
		t.Helper()

		t.Run(name, func(t *testing.T) {
			t.Helper()

			if got := q2.Score(cards, x); got != want {
				t.Errorf("unexpected value: %v", got)
			}
		})
	}

	// ab
	//   \
	//    aa---ba
	//   /
	// ac
	//
	f("example1", []string{"aa", "ab", "ba", "ac"}, 'a', 2)

	f("example2", []string{"aa", "ab", "ba"}, 'a', 1)
	f("example3", []string{"aa", "ab", "ba", "ac"}, 'b', 0)

	// ab---bb---ba
	//      |
	//      ab
	//
	f("wronganswer1", []string{"ab", "ba", "bb", "ab"}, 'b', 1)

	// cb----ca
	//   \  /
	//    cc
	//
	f("wronganswer2", []string{"cb", "ca", "cc"}, 'c', 1)

	// ba___aa____
	// |    |     |
	// |____ca___ba
	//
	f("wronganswer3", []string{"bb", "aa", "ca", "ba", "ba"}, 'a', 2)

	//  _______ba          ab_
	// |   ___/| \___      |  |
	// |  |    |     |     |  |
	// | bc    bc    bc    cb |
	// |  |      \  /      |  |
	// |  |_______\/_______|  |
	// |__________bb__________|
	//
	f("wronganswer4", []string{"bb", "bc", "cc", "cb", "bc", "bc", "aa", "cc", "ab", "ba"}, 'b', 3)
}
