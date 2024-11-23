package main

func RotateTheBox(box [][]byte) [][]byte {
	return rotateTheBox(box)
}

func rotateTheBox(box [][]byte) [][]byte {
	gravity(box)
	return transpose(box)
}

func gravity(x [][]byte) {
	for row := range x {
		for i := len(x[row])-1; i >= 0; i-- {
			if x[row][i] != '.' {
				continue
			}

			stone := i
			for stone >= 0 && x[row][stone] == '.' {
				stone--
			}

			if stone >= 0 && x[row][stone] == '#' {
				x[row][stone], x[row][i] = '.', '#'
			}
		}
	}
}

func transpose(x [][]byte) [][]byte {
	y := make([][]byte, len(x[0]))
	for i := range y {
		y[i] = make([]byte, len(x))
	}

	for row := range x {
		for col := range x[row] {
			y[col][row] = x[len(x)-1-row][col]
		}
	}

	return y
}
