package main

func RotateTheBox(box [][]byte) [][]byte {
	return rotateTheBox(box)
}

func rotateTheBox(x [][]byte) [][]byte {
	y := make([][]byte, len(x[0]))
	for i := range y {
		y[i] = make([]byte, len(x))
	}

	for row := range x {
		for i := len(x[row])-1; i >= 0; i-- {
			if x[row][i] == '.' {
				stone := i
				for stone >= 0 && x[row][stone] == '.' {
					stone--
				}

				if stone >= 0 && x[row][stone] == '#' {
					x[row][stone], x[row][i] = '.', '#'
					y[stone][len(x)-1-row] = x[row][stone]
				}
			}

			y[i][len(x)-1-row] = x[row][i]
		}
	}

	return y
}
