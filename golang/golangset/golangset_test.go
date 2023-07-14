package golangset

import (
	"testing"
)

func TestExample(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"golangset:TestExample"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example()
		})
	}
}

func TestExample2(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"golangset:TestExample2"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example2()
		})
	}
}

func TestExampleIterator(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"golangset:TestExampleIterator"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ExampleIterator()
		})
	}
}

func TestExampleIterator2(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"golangset:TestExampleIterator2"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ExampleIterator2()
		})
	}
}
