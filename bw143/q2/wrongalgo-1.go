package q2

import "sort"

func wrongalgo(nums []int, k int, operations int) int {
	freq := 0

	for left := 0; left < len(nums); left++ {

		// right is the first nums[right] at which it is impossible to substract, or len(nums)
		right := left + 1

		// go as far as the definition of "right" permits
		o := operations
		for right < len(nums) {

			// times we need to substract from nums[right] to get to nums[left]
			t := abs(nums[right]-nums[left]) / k
			if m := abs(nums[right]-nums[left]) % k; m != 0 {
				t++
			}

			o -= t

			if o < 0 {
				break
			}

			right++
		}

		freq = max(freq, right-left)
	}

	return freq
}

func maxFrequencyWrongalgo(nums []int, k int, operations int) int {
	sort.Ints(nums)
	a := wrongalgo(nums, k, operations)
	sort.Sort(sort.Reverse(sort.IntSlice(nums)))
	b := wrongalgo(nums, k, operations)
	return max(a, b)
}
