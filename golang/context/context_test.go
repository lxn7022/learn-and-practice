package context

import "testing"

func TestExample1(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"TestExample1"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example1()
		})
	}
}
