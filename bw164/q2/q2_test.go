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
	//	f("example1", []string{"aa", "ab", "ba", "ac"}, 'a', 2)

	// ab
	// |
	// aa
	// |
	// ba
	//
	//	f("example2", []string{"aa", "ab", "ba"}, 'a', 1)

	// ab   ba
	//
	//	f("example3", []string{"aa", "ab", "ba", "ac"}, 'b', 0)

	// This case proves than nelems/2 is not the right answer.
	//
	//      ba
	//      |
	//      bb
	//     /  \
	//   ab    ab
	//
	//	f("wronganswer1", []string{"ab", "ba", "bb", "ab"}, 'b', 1)

	// This case proves that the longest straight path, beginning
	// from a node with a single link, divided by two, is not the
	// right answer, as could be induced from example1 and
	// wronganswer1.
	//
	// cb----ca
	//   \  /
	//    cc
	//
	//	f("wronganswer2", []string{"cb", "ca", "cc"}, 'c', 1)

	// This case proves that if a node with a single link is not
	// present, beginning with any node indiscriminately is not
	// the right answer.
	//
	//      aa
	//    _/| \_
	//   /  |   \
	// ba---ca---ba
	//
	//	f("wronganswer3", []string{"bb", "aa", "ca", "ba", "ba"}, 'a', 2)

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
	//	f("wronganswer4", []string{"bb", "bc", "cc", "cb", "bc", "bc", "aa", "cc", "ab", "ba"}, 'b', 3)

	// bb → bb bb → bb bb bb - no links
	// ba → ba ba → ba ba ba — no links
	// observation: left[c] connects with left[d], c ≠ d
	//
	// observation: if some left[x] is connected with the single
	// "both" root before all left[] are connected with each
	// other, two remaining left[y] would have no node to connect
	// with.

	// ab---ac
	//   \ /
	//    X
	//   / \
	// ab---ac
	//
	//	f("wronganswer5", []string{"cc", "bc", "ab", "ac", "ab", "ac"}, 'a', 2)

	// 7ba 11bc +7 | 4bc +4 |
	// 7bb         | 7bb    | 2b
	// 3ab 4cb  +3 | cb  +1 |
	//
	// 7ba 11bc +4 | 7ba 7bc +2 | 6ba 6bc
	// 7bb         | 2bb        |
	// 3ab 4cb  +1 | 3ab 3ab    | 3ab 3ab
	//
	f(
		"wronganswer6",
		[]string{
			"ab", "aa", "ab", "bc", "cc", "bc", "bb",
			"ac", "bc", "bc", "aa", "aa", "ba", "bc",
			"cb", "ba", "ac", "bb", "cb", "ac", "cb",
			"cb", "ba", "bc", "ca", "ba", "bb", "cc",
			"cc", "ca", "ab", "bb", "bc", "ba", "ac",
			"bc", "ac", "ac", "bc", "bb", "bc", "ac",
			"bc", "aa", "ba", "cc", "ac", "bb", "ba",
			"bb",
		},
		'b',
		16,
	)
}
