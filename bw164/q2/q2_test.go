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

	// ab----ac
	//   \  /
	//    aa
	//    |
	//    ba
	//
	f("example1", []string{"aa", "ab", "ba", "ac"}, 'a', 2)

	// ab
	// |
	// aa
	// |
	// ba
	//
	f("example2", []string{"aa", "ab", "ba"}, 'a', 1)

	// ab   ba
	//
	f("example3", []string{"aa", "ab", "ba", "ac"}, 'b', 0)

	// This case proves than nelems/2 is not the right answer.
	//
	//      ba
	//      |
	//      bb
	//     /  \
	//   ab    ab
	//
	f("wronganswer1", []string{"ab", "ba", "bb", "ab"}, 'b', 1)

	// This case proves that the longest straight path, beginning
	// from a node with a single link, divided by two, is not the
	// right answer, as could be induced from example1 and
	// wronganswer1.
	//
	// cb----ca
	//   \  /
	//    cc
	//
	f("wronganswer2", []string{"cb", "ca", "cc"}, 'c', 1)

	// This case proves that if a node with a single link is not
	// present, beginning with any node indiscriminately is not
	// the right answer.
	//
	//      aa
	//    _/| \_
	//   /  |   \
	// ba---ca---ba
	//
	f("wronganswer3", []string{"bb", "aa", "ca", "ba", "ba"}, 'a', 2)

	// This case proves that the longest straight path, beginning
	// from a node with the least links, divided by two, is not
	// the right answer, as could be induced from wronganswer3.
	//
	// It also proves that nlinks/2 is not the right answer, as
	// could be induced from all examples and wrong answers so
	// far.
	//
	//     ___ba__
	//    /  /|   \
	//   /  / |    \
	// bc  /  bc    bc
	//   \ \_ |  __/
	//    \  \| /
	//     \__bb
	//        /\
	//       /  \
	//     cb----ab
	//
	f("wronganswer4", []string{"bb", "bc", "cc", "cb", "bc", "bc", "aa", "cc", "ab", "ba"}, 'b', 3)
}
