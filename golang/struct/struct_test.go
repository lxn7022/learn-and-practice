package struct0

import (
	"testing"
)

func TestExample1(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample1:"},
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
