package k8sset

import (
	"testing"
)

func TestExamSets(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"TestExamSets"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ExamSets()
		})
	}
}

func TestExamSets2(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExamSets2"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ExamSets2()
		})
	}
}
