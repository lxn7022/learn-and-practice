package control

import (
	"testing"
)

func TestExample1(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample1: "},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example1()
		})
	}
}

func TestExample2(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample2:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example2()
		})
	}
}

func TestExample3(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample3:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example3()
		})
	}
}

func TestExample4(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample4:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example4()
		})
	}
}

func Test_continueLabel(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"Test_continueLabel:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			continueLabel()
		})
	}
}

func Test_gotoLabel(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"Test_gotoLabel:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			gotoLabel()
		})
	}
}

func Test_breakLabel(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"Test_breakLabel:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			breakLabel()
		})
	}
}

func TestExample6(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample6:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example6()
		})
	}
}

func TestExample7(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample7:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example7()
		})
	}
}

func TestExample8(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample8:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example8()
		})
	}
}
