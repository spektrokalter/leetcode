package q2

import (
//	"fmt"
	"sort"
)

func MaxFrequency(nums []int, k int, operations int) int {
	return maxFrequency(nums, k, operations)
}

func abs(x int) int {
	if x < 0 {
		return -x
	} else {
		return x
	}
}

func maxduplicates(nums []int) int {
	dict := map[int]int{}
	for _, n := range nums {
		dict[n]++
	}
	out := 0
	for _, qty := range dict {
		out = max(out, qty)
	}
	return out
}

func maxFrequency(nums []int, k int, operations int) int {
	if k == 0 {
		return maxduplicates(nums)
	}

	sort.Ints(nums)

//	fmt.Println(nums)

	freq := 0

	for middle := 0; middle < len(nums); middle++ {
		left, right := middle-1, middle+1

		o := operations
		for {
			if left == -1 && right == len(nums) {
				break
			}
			var t int
			if left == -1 {
				goto moveright
			}
			if right == len(nums) {
				goto moveleft
			}

			if abs(nums[left]-nums[middle]) < abs(nums[right]-nums[middle]) {
				goto moveleft
			} else {
				goto moveright
			}

		moveleft:
			t = abs(nums[left]-nums[middle]) / k
			if m := abs(nums[left]-nums[middle]) % k; m != 0 {
				t++
			}
			o -= t
			if o < 0 {
				break
			}
			left--
			continue

		moveright:
			t = abs(nums[right]-nums[middle]) / k
			if m := abs(nums[right]-nums[middle]) % k; m != 0 {
				t++
			}
			o -= t
			if o < 0 {
				break
			}
			right++
			continue
		}

//		fmt.Printf("%d..%d..%d\n", left, middle, right)
		freq = max(freq, right-left)
	}

	return freq - 1
}
