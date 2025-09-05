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
	//	fmt.Println("example3")
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
	f("wronganswer5", []string{"cc", "bc", "ab", "ac", "ab", "ac"}, 'a', 2)

	// 7ba 11bc +7 | 4bc +4 |
	// 7bb         | 7bb    | 2b
	// 3ab 4cb  +3 | cb  +1 |
	//
	// 7ba 11bc +4 | 7ba 7bc +2 | 6ba 6bc
	// 7bb         | 2bb        |
	// 3ab 4cb  +1 | 3ab 3ab    | 3ab 3ab
	//
	// Find (ncards[i]; ncards[i-1]) such that
	// 1. ncards[i] > ncards[i-1]
	// 2. ncards[i]-min(ncards[i], both) = ncards[i-1]
	//
	// Problem: 6bb 9ab 5cb 23wb 20vb 23xb 20yb. If we choose 9ab
	// and 5cb, 4bb would be spent and the rest 2bb would be
	// impossible to spend. It is more optimal to spend 6bb by 3bb
	// on each 23wb 20vb.
	//
	// And the reverse: 6bb 1ab 2cb 6xb 12yb. If we choose 1ab and
	// 2cb, 1bb would be spend and the rest 5bb would be
	// impossible to spend. It is more optimal to spend 6bb on 6xb
	// 12yb.
	//
	// In other words: the gap size, whether smaller (23-20 < 9-5)
	// or larger (12-6 > 2-1), is irrelevant.
	//
	// ---
	//
	// What if we simplify 9ab 5cb 23wb 20vb 23xb 20yb somehow?
	// 23wb can be paired with 20vb, but it can as well be paired
	// with 5cb. Any items can be paired. 23wb can even be paired
	// with 20vb, and the rest 3wb can be paired with 5cb, and the
	// rest 2cb can be paured with 9ab, etc.
	//
	// IDEA: a side can be simplified to two numbers: remaining
	// cards and removed cards. 9ab 5cb 23wb 20vb 23xb 20yb is
	// simplified to 4 and 96. 4 is any group of 4 incompatible
	// cards, 96 is an even number cards, each having a compatible
	// pair within the same 96.
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

	// 2ea 2eb 6ec ed
	// 4ee
	// 2ae 2be ce 2de
	//
	f(
		"wronganswer7",
		[]string{
			"cb", "ec", "ad", "ee", "be", "ee", "eb",
			"ea", "ee", "cc", "ac", "de", "bb", "aa",
			"db", "cd", "be", "ac", "bc", "dc", "bb",
			"bc", "db", "ca", "ec", "ac", "ae", "ac",
			"ea", "de", "ec", "ba", "ce", "bd", "ca",
			"ad", "ec", "db", "ab", "ac", "ba", "ee",
			"dc", "eb", "ae", "ec", "ec", "dd", "ed",
			"bc",
		},
		'e',
		11,
	)
}
